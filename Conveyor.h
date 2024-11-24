#ifndef __CONVEYOR_H__
#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#ifdef __CELLapist__
#include "X_include.h"
#endif /* ! __CELLapist__ */
#include "types.h"
#include "constant.h"
#include "macros.h"

#define CONVEYOR_STATE_NUM  2048      /* セルの状態数 */

#define CONVEYOR_VACUM          0
#define CONVEYOR_CONTROL        ( 1 << 0 )
#define CONVEYOR_SENSOR         ( 1 << 1 )
/* 1 direction */
#define CONVEYOR_UP             ( 1 << 2 )
#define CONVEYOR_RIGHT          ( 1 << 3 )
#define CONVEYOR_DOWN           ( 1 << 4 )
#define CONVEYOR_LEFT           ( 1 << 5 )
/* 2 direction */
#define CONVEYOR_UP_RIGHT       ( 1 << 6 )
#define CONVEYOR_UP_LEFT        ( 1 << 7 )
#define CONVEYOR_DOWN_RIGHT     ( 1 << 8 )
#define CONVEYOR_DOWN_LEFT      ( 1 << 9 )

/* for isUpdated */
#define CONVEYOR_BROKEN         ( 1 << 10 )

/* for Can't allocate signal */
#define CONVEYOR_CANT_ALLOC     ( 1 << 11 )

/* for relative positioning */
#define CONVEYOR_CENTER         ( 1 << 0 )      /* forward  */
#define CONVEYOR_CW             ( 1 << 1 )      /* right    */
#define CONVEYOR_OPP            ( 1 << 2 )      /* backward */
#define CONVEYOR_CCW            ( 1 << 3 )      /* left     */

/* for signrals */
#define SIG_LENGTH      2                       /* bits of signals */
#define SIG_MASK        ((1 << SIG_LENGTH)-1)   /* mask for signals */    
#define NO_SIGNAL       0
#define SIGNAL          1
#define LOOKING         2
#define CANT_ALLOC      3

/* for lookup signals */
#define SHIFT(num,x)    ( (x) >> (num)  & SIG_MASK)
#define UP(x)           ( (x)           & SIG_MASK) 
#define RIGHT(x)        ( ((x) >> 2)    & SIG_MASK) 
#define DOWN(x)         ( ((x) >> 4)    & SIG_MASK) 
#define LEFT(x)         ( ((x) >> 6)    & SIG_MASK) 

/* for GAs */
#define CONV_UP                 1
#define CONV_DOWN               2
#define CONV_RIGHT              4
#define CONV_LEFT               8
#define CONV_LOAD               16
#define CONV_CTL                32

#define CONVEYOR_MOVE_MASK      (CONVEYOR_CONTROL | CONVEYOR_UP | CONVEYOR_DOWN | CONVEYOR_RIGHT | CONVEYOR_LEFT)

enum {CONVEYOR_VACUM_COLOR=0,CONVEYOR_CONTROL_COLOR,
        CONVEYOR_UP_COLOR,CONVEYOR_DOWN_COLOR,
        CONVEYOR_RIGHT_COLOR,CONVEYOR_LEFT_COLOR,
        CONV_UP_RIGHT_COLOR,CONV_DOWN_RIGHT_COLOR,
        CONV_DOWN_LEFT_COLOR,CONV_UP_LEFT_COLOR,
        CONVEYOR_SENSOR_COLOR,CONVEYOR_BROKEN_COLOR,
        CONVEYOR_BACKGROUND
    };

#define LOADED                  1
#define UNLOADED                0

/* For Conveyor system (defined in Conveyor.c) */
#ifdef __CELLapist__
extern void conveyorButton(Widget,caddr_t ,XEvent *);
#endif /* __CELLapist__ */
extern void conveyorNew(int);
extern void conveyorDelete(void);
extern void conveyorStep4(void);
extern void conveyorStep4Rand(void);
extern void conveyorStep4MOD(void);
extern void conveyorStep8(void);
extern void conveyorStep8New(void);
extern void conveyorStep8Fujita(void);
extern void conveyorStepGA(void);
extern void conveyorRefresh(void);

#ifdef __CELLapist__
extern void conveyorRandom(Widget,int *,caddr_t);
#endif /*  __CELLapist__ */
#ifdef __GA__
extern void conveyorRandom(int,int);
#endif /* __GA__ */
#define __CONVEYOR_H__
#endif /* ! __CONVEYOR_H__ */
