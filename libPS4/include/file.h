#pragma once

#ifndef FILE_H
#define FILE_H

#include "types.h"

#define O_RDONLY 0x0000
#define O_WRONLY 0x0001

#define O_CREAT 0x0200    /* create if nonexistent */
#define O_TRUNC 0x0400    /* truncate to zero length */

ssize_t read(int fd, void *buf, size_t nbyte);
int open(const char *path, int flags, int mode);
int close(int fd);
int unlink(const char *pathname);
int unmount(const char *dir, int flags);
int mkdir(const char *pathname, mode_t mode);
int rmdir(const char *path);
off_t lseek(int fildes, off_t offset, int whence);
int file_exists(char *fname);
void touch_file(char *destfile);

#endif
