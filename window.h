#ifndef __WINDOW_H__

#include "constant.h"
#include "types.h"
#include "globals.h"
#include "macros.h"

/* (defined window.c) */
extern void make_cellWidget(void);
extern void make_slider(void);
extern void make_field(void);
extern void allocateColor(int);
extern void makeStateDisplay();

#define __WINDOW_H__
#endif /* ! __WINDOW_H__ */
