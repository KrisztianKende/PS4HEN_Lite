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

typedef float float32;
typedef double float64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

/* POSIX types */
typedef uint16_t mode_t;
typedef int64_t off_t;
typedef int64_t time_t;
typedef long suseconds_t;

#endif
