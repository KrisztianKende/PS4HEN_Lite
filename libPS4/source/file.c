#include "syscall.h"
#include "file.h"

SYSCALL(read, 3);
SYSCALL(open, 5);
SYSCALL(close, 6);
SYSCALL(unlink, 10);
SYSCALL(unmount, 22);
SYSCALL(mkdir, 136);
SYSCALL(rmdir, 137);
SYSCALL(lseek, 478);

int file_exists(char *fname) {
  int file = open(fname, O_RDONLY, 0);
  if (file != -1) {
    close(file);
    return 1;
  }
  return 0;
}

void touch_file(char *destfile) {
  int fd = open(destfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (fd != -1) {
    close(fd);
  }
}
