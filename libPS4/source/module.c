#include "syscall.h"
#include "module.h"

SYSCALL(getFunctionAddressByName, 591);

int loadModule(const char *name, int *idDestination) {
  return syscall(594, name, 0, idDestination, 0);
}
