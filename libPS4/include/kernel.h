#pragma once

#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

typedef struct {
  int type;                // 0x00
  int req_id;              // 0x04
  int priority;            // 0x08
  int msg_id;              // 0x0C
  int target_id;           // 0x10
  int user_id;             // 0x14
  int unk1;                // 0x18
  int unk2;                // 0x1C
  int app_id;              // 0x20
  int error_num;           // 0x24
  int unk3;                // 0x28
  char use_icon_image_uri; // 0x2C
  char message[1024];      // 0x2D
  char uri[1024];          // 0x42D
  char unkstr[1024];       // 0x82D
} SceNotificationRequest;  // Size = 0xC30

extern int libKernelHandle;

extern int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

extern int (*getuid)();

extern int (*sceKernelSendNotificationRequest)(int device, SceNotificationRequest *req, size_t size, int blocking);
extern const char *(*sceKernelGetFsSandboxRandomWord)();

void initKernel(void);

int kexec(void *func, void *user_arg);

int is_in_sandbox();

#endif
