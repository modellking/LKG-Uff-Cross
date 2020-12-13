#include "Arduino.h"
#ifndef UTIL
#define UTIL 1

#define SIZEOF(a) sizeof(a)/sizeof(*a)
#define CLAMP(a, b, c) if(a < b){a = b;}else if(a > c){a = c;}
#define SEGB(x, seg) x * seg / 256

#endif
