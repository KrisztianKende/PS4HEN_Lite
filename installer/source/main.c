#include <ps4.h>

#include "common.h"
#include "kpayloads.h"
#include "path.h"
#include "version.h"

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

  uint16_t fw_version = get_firmware();
  if (fw_version < MIN_FW || fw_version > MAX_FW) {
    printf_notification("Unsupported firmware!");
    return -1;
  }

  // Jailbreak the process
  jailbreak();

  // Use temp file to prevent re-running HEN
  if (file_exists(IS_LOADED_PATH)) {
    printf_notification("PS4HEN is already loaded!");
    return 0;
  }
  touch_file(IS_LOADED_PATH);

  // Apply all HEN kernel patches
  install_patches();

  exploit_fixes();
  mmap_patch();

  block_updates();
  disable_aslr();

  // Install and run kpayload
  install_payload();

  printf_notification("Welcome to PS4HEN Lite %s", VERSION);

  return 0;
}
