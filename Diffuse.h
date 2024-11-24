#ifndef __DIFFUSE_H__
#include <stdio.h>
#include <math.h>
/* #include <stdlib.h> */

#include "X_include.h"
#include "types.h"
#include "constant.h"
#include "macros.h"

#define DIFFUSE_HEAT       10001
#define DIFFUSE_COOL       0
#define DIFFUSE_LOW        1
#define DIFFUSE_HIGH       10000
#define DIFFUSE_OBSTACLE   10100
#define DIFFUSE_HEAT_NUM   (DIFFUSE_HIGH-DIFFUSE_LOW+1)     

/* For Diffusion Equation (defined in Diffuse.c) */
extern void diffuseButton(Widget,caddr_t ,XEvent *);
extern void diffuseNew(int);
extern void diffuseDelete(void);
extern void diffuseStep(void);
extern void diffuseRefresh(void);
extern void diffuseRandom(Widget,int *,caddr_t);

#define __DIFFUSE_H__
#endif /* ! __DIFFUSE_H__ */

