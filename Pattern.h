#ifndef __PATTERN_H__
#include <stdio.h>
#include <math.h>
/* #include <stdlib.h>*/

#include "X_include.h"
#include "types.h"
#include "constant.h"
#include "macros.h"

#define PATTERN_VACUM          0
#define PATTERN_CONTROL        1
#define PATTERN_SENSOR         2
#define PATTERN_BROKEN         4
/* 1 direction */
#define PATTERN_UP             8
#define PATTERN_DOWN           16
#define PATTERN_RIGHT          32
#define PATTERN_LEFT           64
/* 2 direction */
#define PATTERN_UP_RIGHT       128
#define PATTERN_UP_LEFT        256
#define PATTERN_DOWN_RIGHT     512
#define PATTERN_DOWN_LEFT      1024

#define PATTERN_MOVE_MASK      (PATTERN_CONTROL | PATTERN_UP | PATTERN_DOWN | PATTERN_RIGHT | PATTERN_LEFT)

#define PATTERN_VACUM_COLOR    0
#define PATTERN_CONTROL_COLOR  1
#define PATTERN_UP_COLOR       1
#define PATTERN_DOWN_COLOR     1
#define PATTERN_RIGHT_COLOR    1
#define PATTERN_LEFT_COLOR     1
#define PATTERN_SENSOR_COLOR   1
#define PATTERN_BROKEN_COLOR   1

#define PATTERN_CONTROL_SCORE  8

typedef struct _pattern_score {
      int up;
      int down;
      int right;
      int left;
    } pattern_score;


/* For Pattern formation (defined in Pattern.c) */
extern void patternButton(Widget,caddr_t ,XEvent *);
extern void patternNew(int);
extern void patternDelete(void);
extern void patternStep(void);
extern void patternRefresh(void);
extern void patternRandom(Widget,int *,caddr_t);

#define __PATTERN_H__
#endif /* ! __PATTERN_H__ */

