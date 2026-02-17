#include "module.h"
#include "syscall.h"
#include "kernel.h"

int libKernelHandle;
int *(*__error)();
int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);
int (*getuid)();
int (*sceKernelSendNotificationRequest)(int device, SceNotificationRequest *req, size_t size, int blocking);
const char *(*sceKernelGetFsSandboxRandomWord)();

SYSCALL(kexec, 11);

SYSCALL(is_in_sandbox, 585);

void initKernel(void) {
  if (libKernelHandle) {
    return;
  }

  __error = NULL;

  if (loadModule("libkernel.sprx", &libKernelHandle)) {
    if (loadModule("libkernel_web.sprx", &libKernelHandle)) {
      loadModule("libkernel_sys.sprx", &libKernelHandle);
    }
  }

  RESOLVE(libKernelHandle, __error);
  RESOLVE(libKernelHandle, sceKernelLoadStartModule);
  RESOLVE(libKernelHandle, getuid);
  RESOLVE(libKernelHandle, sceKernelSendNotificationRequest);
  RESOLVE(libKernelHandle, sceKernelGetFsSandboxRandomWord);
}
