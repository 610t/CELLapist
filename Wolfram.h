#ifndef __WOLFRAM_H__

#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#include "X_include.h"
#include "types.h"
#include "constant.h"
#include "macros.h"

/* セル状態の具体的な定義 */
#define VACUM_STATE             0         
#define ALIVE_STATE             1         
#define WOLFRAM_NEIGHBOUR       2
#define WOLFRAM_STATE           2

/* For Rule window */
#define WOLF_RULE_NULL          0
#define WOLF_RULE_OK            1
#define WOLF_RULE_UP            2
#define WOLF_RULE_DOWN          3

/* For Wolfram (defined in Wolfram.c) */
extern void wolframButton(Widget,caddr_t ,XEvent *);
extern void wolframNew(int);
extern void wolframDelete(void);
extern void wolframStep(void);
extern void wolframRefresh(void);
extern void wolframRandom(Widget,int *,caddr_t);

#define __WOLFRAM_H__
#endif /*  ! __WOLFRAM_H__ */
