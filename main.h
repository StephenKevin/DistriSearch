#ifndef MAIN_H_INCLUDE
#define MAIN_H_INCLUDE

#ifndef MAIN_C_
    #define MAIN_EXTERN extern
#else
    #define MAIN_EXTERN
#endif


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
// #include <stdbool.h>

#include "array.h"
#include "list.h"
#include "series.h"

MAIN_EXTERN int malloccheck(void * ptr);

#endif