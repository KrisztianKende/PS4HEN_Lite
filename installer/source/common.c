#include <ps4.h>

#include "common.h"

#define PS4UPDATE_FILE "/update/PS4UPDATE.PUP"
#define PS4UPDATE_TEMP_FILE "/update/PS4UPDATE.PUP.net.temp"

void block_updates() {
  // Delete existing updates/blocker and recreate
  unlink(PS4UPDATE_FILE);
  rmdir(PS4UPDATE_FILE);
  mkdir(PS4UPDATE_FILE, 777);

  unlink(PS4UPDATE_TEMP_FILE);
  rmdir(PS4UPDATE_TEMP_FILE);
  mkdir(PS4UPDATE_TEMP_FILE, 777);

  // Unmount update directory. From etaHEN
  if ((int)unmount("/update", 0x80000LL) < 0) {
    unmount("/update", 0);
  }
}
