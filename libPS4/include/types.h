#pragma once

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

#ifndef NULL
#define NULL 0
#endif

typedef uint64_t size_t;
typedef uint64_t rsize_t;
typedef int64_t ssize_t;

typedef uint64_t u64;

/* POSIX types */
typedef uint16_t mode_t;
typedef int64_t off_t;

#endif
