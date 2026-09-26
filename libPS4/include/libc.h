#pragma once

#ifndef LIBC_H
#define LIBC_H

#define SEEK_SET 0

extern void *(*memset)(void *destination, int value, size_t num);
extern void *(*memcpy)(void *destination, const void *source, size_t num);
extern int (*snprintf_s)(char *restrict buffer, rsize_t bufsz, const char *restrict format, ...);
extern int (*atoi)(const char *s);

void initLibc(void);

#endif
