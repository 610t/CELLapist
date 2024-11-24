#ifndef __SPREAD_H__
#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#include "X_include.h"
#include "types.h"
#include "constant.h"
#include "macros.h"

/* セル状態の具体的な定義 */
enum
{
  SP_VACUM_STATE=0,
  SP_WAIT1_STATE,
  SP_INFO_STATE,
  SP_CONTROL_STATE,
  SP_GOAL_STATE,
  SP_BROKEN_STATE,
};

/* For Spread information (defined in Spread.c) */
extern void spreadButton(Widget,caddr_t ,XEvent *);
extern void spreadNew(int);
extern void spreadDelete(void);
extern void spreadStep(void);
extern void spreadRefresh(void);
extern void spreadRandom(Widget,int *,caddr_t);

#define __SPREAD_H__
#endif /* ! __SPREAD_H__ */
