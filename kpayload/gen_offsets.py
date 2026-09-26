#!/usr/bin/env python3
import argparse, re
from pathlib import Path

def parse_fields(hdr):
    fields, in_struct = [], False
    for line in open(hdr):
        if 'struct kpayload_offsets {' in line: in_struct = True
        elif in_struct and '};' in line: break
        elif in_struct:
            m = re.match(r'\s+uint32_t\s+(\w+)\s*;', line)
            if m: fields.append(m.group(1))
    return fields

def parse_c(path):
    vals = {}
    for m in re.finditer(r'\.([\w]+)\s*=\s*(0x[0-9A-Fa-f]+|\d+)', open(path).read()):
        vals[m.group(1)] = int(m.group(2), 0)
    return vals

def sleb128(v):
    v, out = int(v), []
    while True:
        b = v & 0x7F; v >>= 7
        if (v == 0 and not (b & 0x40)) or (v == -1 and (b & 0x40)):
            out.append(b); break
        out.append(b | 0x80)
    return bytes(out)

def build(fields, fws, data):
    bm = (len(fields) + 7) // 8
    base = [data[fws[0]].get(f, 0) for f in fields]
    blob, prev = bytearray(), base[:]
    for fw in fws[1:]:
        cur = [data[fw].get(f, 0) for f in fields]
        mask = bytearray(bm)
        for i, (p, c) in enumerate(zip(prev, cur)):
            if p != c: mask[i >> 3] |= 1 << (i & 7)
        blob += mask
        for p, c in zip(prev, cur):
            if p != c:
                d = (c - p) & 0xFFFFFFFF
                if d >= 0x80000000: d -= 0x100000000
                blob += sleb128(d)
        prev = cur
    return base, bytes(blob)

def fmt_bytes(d, w=16):
    return ',\n'.join('  ' + ', '.join(f'0x{b:02X}' for b in d[i:i+w]) for i in range(0, len(d), w))

def fmt_u16(vs, w=16):
    return ',\n'.join('  ' + ', '.join(str(v) for v in vs[i:i+w]) for i in range(0, len(vs), w))

def fmt_u32(vs, w=7):
    return ',\n'.join('  ' + ', '.join(f'0x{v:08X}u' for v in vs[i:i+w]) for i in range(0, len(vs), w))

ap = argparse.ArgumentParser()
ap.add_argument('--header'); ap.add_argument('--srcdir'); ap.add_argument('--output')
args = ap.parse_args()

fields = parse_fields(args.header)
data = {}
for fn in Path(args.srcdir).glob('*.c'):
    data[int(fn.stem)] = parse_c(str(fn))

fws = sorted(data)
nf, nv, bm = len(fields), len(fws), (len(fields) + 7) // 8
base, blob = build(fields, fws, data)

out = f'''\
#include "offsets.h"
#include "sections.h"

#define FIELD_COUNT   {nf}u
#define FW_COUNT      {nv}u
#define BITMASK_BYTES {bm}u

_Static_assert(sizeof(struct kpayload_offsets) == FIELD_COUNT * sizeof(uint32_t), "struct size mismatch - regenerate offsets_file.c");

static const uint16_t _fw_versions[FW_COUNT] PAYLOAD_RDATA = {{
{fmt_u16(fws)}
}};

static const uint32_t _base_values[FIELD_COUNT] PAYLOAD_RDATA = {{
{fmt_u32(base)}
}};

static const uint8_t _delta_data[] PAYLOAD_RDATA = {{
{fmt_bytes(blob)}
}};

static struct kpayload_offsets _decoded PAYLOAD_BSS;

PAYLOAD_CODE const struct kpayload_offsets *get_offsets_for_fw(uint16_t fw_version) {{
  int lo = 0;
  int hi = (int)FW_COUNT - 1;
  int idx = -1;

  while (lo <= hi) {{
    int mid = (lo + hi) >> 1;
    uint16_t v = _fw_versions[mid];

    if (v == fw_version) {{
      idx = mid;
      break;
    }}

    if (v < fw_version) {{
      lo = mid + 1;
    }} else {{
      hi = mid - 1;
    }}
  }}

  if (idx < 0) {{
    return NULL;
  }}

  uint32_t *dst = (uint32_t *)(void *)&_decoded;

  for (unsigned i = 0; i < FIELD_COUNT; i++) {{
    dst[i] = _base_values[i];
  }}

  const uint8_t *dp = _delta_data;

  for (int vi = 1; vi <= idx; vi++) {{
    const uint8_t *mask = dp;

    dp += BITMASK_BYTES;

    for (unsigned f = 0; f < FIELD_COUNT; f++) {{
      if (mask[f >> 3] & (1u << (f & 7u))) {{
        int32_t delta = 0;
        int32_t shift = 0;
        uint8_t b;

        do {{
          b = *dp++;
          delta |= (int32_t)(b & 0x7Fu) << shift;
          shift += 7;
        }} while (b & 0x80u);

        if (shift < 32 && (b & 0x40u)) {{
          delta |= (int32_t)((uint32_t)-1u << shift);
        }}

        dst[f] = (uint32_t)((int32_t)dst[f] + delta);
      }}
    }}
  }}

  return &_decoded;
}}
'''

open(args.output, 'w').write(out)
