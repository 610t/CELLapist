#ifndef __2DROAD_H__
#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#ifdef __CELLapist__
#include "X_include.h"
#endif /* ! __CELLapist__ */
#include "types.h"
#include "constant.h"
#include "macros.h"

#define CAR_STATE_NUM           16      /* セルの状態数 */

#define CAR_VACUM               0
#define CAR_RIGHT               ( 1 << 0 )
#define CAR_UP                  ( 1 << 1 )

enum{CAR_VACUM_COLOR=0,CAR_RIGHT_COLOR,CAR_UP_COLOR};

#define CAR_EMPTY               0
#define CAR_AT                  0

/* For Car system (defined in 2DRoad.c) */
#ifdef __CELLapist__
extern void carButton(Widget,caddr_t ,XEvent *);
#endif /* __CELLapist__ */
extern void carNew(int);
extern void carDelete(void);
extern void carStep(void);
extern void carRefresh(void);

#ifdef __CELLapist__
extern void carRandom(Widget,int *,caddr_t);
#endif /*  __CELLapist__ */
#ifdef __GA__
extern void carRandom(int,int);
#endif /* __GA__ */
#define __2DROAD_H__
#endif /* ! __CAR_H__ */
