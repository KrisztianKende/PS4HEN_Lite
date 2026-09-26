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

void fix_trophy_db() {
  int dir_fd = open("/user/home", O_RDONLY, 0);
  if (dir_fd < 0) {
    return;
  }

  char dir_buf[1024];
  int nbytes;

  while ((nbytes = getdents(dir_fd, dir_buf, sizeof(dir_buf))) > 0) {
    int pos = 0;

    while (pos < nbytes) {
      struct dirent *entry = (struct dirent *)(dir_buf + pos);
      if (entry->d_reclen == 0) {
        break;
      }

      if (entry->d_namlen != 8) {
        pos += entry->d_reclen;
        continue;
      }

      char db_path[46];
      memcpy(db_path, "/user/home/", 11);
      memcpy(db_path + 11, entry->d_name, 8);
      memcpy(db_path + 19, "/trophy/db/trophy_local.db", 27);

      int fd = open(db_path, O_RDWR, 0);
      if (fd >= 0) {
        unsigned char file_buf[4096];
        int bytes_read;
        int carry = 0;
        long long file_offset = 0;

        while ((bytes_read = read(fd, file_buf + carry, sizeof(file_buf) - carry)) > 0) {
          bytes_read += carry;
          if (bytes_read < 46) {
            break;
          }

          for (int i = 0; i <= bytes_read - 46; i++) {
            if (file_buf[i] == 0xFF &&
                (((file_buf[i + 1] == '0' && file_buf[i + 2] == '0') && ((file_buf[i + 24] == '2' && file_buf[i + 25] == '0') || (file_buf[i + 24] == '1' && file_buf[i + 25] == '9'))) ||
                  (file_buf[i + 1] == '1' && file_buf[i + 2] == '9' && file_buf[i + 24] == '2' && file_buf[i + 25] == '0')) &&
                file_buf[i + 5] == '-'  && file_buf[i + 8] == '-'  && file_buf[i + 11] == 'T' && file_buf[i + 14] == ':' && file_buf[i + 17] == ':' && file_buf[i + 20] == '.' &&
                file_buf[i + 23] == 'Z') {

              if (pwrite(fd, &file_buf[i + 24], 22, file_offset + i + 1) != 22) {
                goto close_file;
              }

              i += 45;
            }
          }

          if (bytes_read < (int)sizeof(file_buf)) {
            break;
          }

          memcpy(file_buf, file_buf + sizeof(file_buf) - 45, 45);
          file_offset += sizeof(file_buf) - 45;
          carry = 45;
        }

close_file:
        close(fd);
      }

      pos += entry->d_reclen;
    }
  }

  close(dir_fd);
}
