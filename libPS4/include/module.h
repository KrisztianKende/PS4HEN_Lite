#pragma once

#ifndef MODULE_H
#define MODULE_H

#define RESOLVE(module, name) getFunctionAddressByName(module, #name, &name)

int getFunctionAddressByName(int loadedModuleID, char *name, void *destination);
int loadModule(const char *name, int *idDestination);

#endif
