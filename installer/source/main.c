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

  // Check temp file to prevent re-running HEN
  if (file_exists(IS_LOADED_PATH)) {
    printf_notification("PS4HEN is already loaded!");
    return 0;
  }

  // Apply all HEN kernel patches
  install_patches();

  block_updates();

  // Install and run kpayload
  install_payload();

  // Create temp file to prevent re-running HEN
  touch_file(IS_LOADED_PATH);

  printf_notification("Welcome to PS4HEN Lite %s", VERSION);

  return 0;
}
