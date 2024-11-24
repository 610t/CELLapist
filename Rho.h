#ifndef __RHO_H__
#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#ifdef __CELLapist__
#include "X_include.h"
#endif /* ! __CELLapist__ */
#include "types.h"
#include "constant.h"
#include "macros.h"

#define RHO_STATE_NUM  2      /* セルの状態数 */

#define RHO_BLACK               0
#define RHO_WHITE               ( 1 << 0 )

#define RHO_BLACK_COLOR         0
#define RHO_WHITE_COLOR         1

/* 1 direction */
#define RHO_UP             ( 1 << 1 )
#define RHO_DOWN           ( 1 << 2 )
#define RHO_RIGHT          ( 1 << 3 )
#define RHO_LEFT           ( 1 << 4 )
/* 2 direction */
#define RHO_UP_RIGHT       ( 1 << 5 )
#define RHO_UP_LEFT        ( 1 << 6 )
#define RHO_DOWN_RIGHT     ( 1 << 7 )
#define RHO_DOWN_LEFT      ( 1 << 8 )

/* For Rho system (defined in Rho.c) */
#ifdef __CELLapist__
extern void rhoButton(Widget,caddr_t ,XEvent *);
#endif /* __CELLapist__ */
extern void rhoNew(int);
extern void rhoDelete(void);
extern void rhoStep4(void);
extern void rhoStep8(void);
extern void rhoStepGA(void);
extern void rhoRefresh(void);

#ifdef __CELLapist__
extern void rhoRandom(Widget,int *,caddr_t);
#endif /*  __CELLapist__ */
#ifdef __GA__
extern void rhoRandom(int,int);
#endif /* __GA__ */
#define __RHO_H__
#endif /* ! __RHO_H__ */
