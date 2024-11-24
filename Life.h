#ifndef __LIFE_H__

#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#include "X_include.h"
#include "types.h"
#include "constant.h"
#include "macros.h"

/* セル状態の具体的な定義 */
#define VACUM_STATE      0         
#define ALIVE_STATE      1         

/* For Life GAME(defined in Life.c) */
extern void lifeButton(Widget,caddr_t ,XEvent *);
extern void lifeNew(int);
extern void lifeDelete(void);
extern void lifeStep(void);
extern void lifeRefresh(void);
extern void lifeRandom(Widget,int *,caddr_t);

#define __LIFE_H__
#endif /*  ! __LIFE_H__ */
