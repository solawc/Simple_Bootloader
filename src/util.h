#ifndef __util_h
#define __util_h

#include "main.h"

#if !defined(MIN)
#define MIN(a,b)                        ((a) < (b) ? (a) : (b))
#endif

#if !defined(MAX)
#define MAX(a,b)                        ((a) > (b) ? (a) : (b))
#endif

#define KB(size)                        ((size) * 1024)

#endif
