#include "kernel.h"
#include "module.h"
#include "libc.h"

int libc;

void *(*memset)(void *destination, int value, size_t num);
void *(*memcpy)(void *destination, const void *source, size_t num);
int (*snprintf_s)(char *restrict buffer, rsize_t bufsz, const char *restrict format, ...);
int (*atoi)(const char *s);

void initLibc(void) {
  if (libc) {
    return;
  }

  libc = sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, 0, 0, NULL, NULL);

  RESOLVE(libc, memset);
  RESOLVE(libc, memcpy);
  RESOLVE(libc, snprintf_s);
  RESOLVE(libc, atoi);
}
