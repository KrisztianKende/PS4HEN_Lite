#include "elf.h"
#include "file.h"
#include "fw_defines.h"
#include "kernel.h"
#include "libc.h"
#include "payload_utils.h"

uint16_t g_firmware;

int is_jailbroken() {
  if (getuid() == 0 && is_in_sandbox() == 0) {
    return 1;
  }
  return 0;
}

int kpayload_jailbreak(struct thread *td, struct kpayload_firmware_args *args) {
  struct filedesc *fd;
  struct ucred *cred;
  fd = td->td_proc->p_fd;
  cred = td->td_proc->p_ucred;

  void *kernel_base;
  uint8_t *kernel_ptr;
  void **prison0;
  void **rootvnode;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, jailbreak_macro);

  cred->cr_uid = 0;
  cred->cr_ruid = 0;
  cred->cr_rgid = 0;
  cred->cr_groups[0] = 0;

  cred->cr_prison = *prison0;
  fd->fd_rdir = fd->fd_jdir = *rootvnode;

  void *td_ucred = *(void **)(((char *)td) + 304);

  uint64_t *sonyCred = (uint64_t *)(((char *)td_ucred) + 96);
  *sonyCred = 0xffffffffffffffff;

  uint64_t *sceProcessAuthorityId = (uint64_t *)(((char *)td_ucred) + 88);
  *sceProcessAuthorityId = 0x3801000000000013;

  uint64_t *sceProcCap = (uint64_t *)(((char *)td_ucred) + 104);
  *sceProcCap = 0xffffffffffffffff;

  return 0;
}

uint16_t get_firmware() {
  // Return early if this has already been run
  if (g_firmware) {
    return g_firmware;
  }

  char sandbox_path[33]; // `/XXXXXXXXXX/common/lib/libc.sprx` [Char count of 32 + nullterm]
  snprintf_s(sandbox_path, sizeof(sandbox_path), "/%s/common/lib/libc.sprx", sceKernelGetFsSandboxRandomWord());
  int fd = open(sandbox_path, O_RDONLY, 0);
  if (fd < 0) {
    // Assume it's currently jailbroken
    fd = open("/system/common/lib/libc.sprx", O_RDONLY, 0);
    if (fd < 0) {
      // It's really broken
      return -1;
    }
  }

  // Read SELF header from file
  lseek(fd, 0, SEEK_SET);
  SelfHeader self_header;
  if (read(fd, &self_header, sizeof(self_header)) != sizeof(self_header)) {
    return -1;
  }

  // Calculate ELF header offset from the number of SELF segments
  uint64_t elf_header_offset = sizeof(self_header) + self_header.num_of_segments * sizeof(SelfEntry);

  // Read ELF header from file
  lseek(fd, elf_header_offset, SEEK_SET);
  Elf64_Ehdr elf_header;
  if (read(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header)) {
    return -1;
  }

  // Calculate SCE header offset from number of ELF entries
  uint64_t sce_header_offset = elf_header_offset + elf_header.e_ehsize + elf_header.e_phnum * elf_header.e_phentsize;

  // Align
  while (sce_header_offset % 0x10 != 0) {
    sce_header_offset++;
  }

  // Read SCE header
  lseek(fd, sce_header_offset, SEEK_SET);
  SceHeader sce_header;
  if (read(fd, &sce_header, sizeof(sce_header)) != sizeof(sce_header)) {
    return -1;
  }

  close(fd);

  // Format and return
  char string_fw[5] = {0}; // "0000\0"
  snprintf_s(string_fw, sizeof(string_fw), "%02lx%02lx", (sce_header.fw_version >> (5 * 8)) & 0xFF, (sce_header.fw_version >> (4 * 8)) & 0xFF);

  uint16_t ret = atoi(string_fw); // Numerical representation of the firmware version. ex: 505 for 5.05, 702 for 7.02, etc

  // Firmware versions with same offset values
  switch (ret) {
  case 507:
    ret = 505;
    break;
  case 602:
    ret = 600;
    break;
  case 671:
    ret = 670;
    break;
  case 701:
  case 702:
    ret = 700;
    break;
  case 1071:
    ret = 1070;
    break;
  case 1152:
    ret = 1150;
    break;
  case 1202:
    ret = 1200;
    break;
  case 1252:
    ret = 1250;
  }

  g_firmware = ret;
  return ret;
}

int jailbreak() {
  if (is_jailbroken()) {
    return 0;
  }
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_jailbreak, &kpayload_firmware_info);
}
