#ifndef __BUTTONS_H__

#include "constant.h"
#include "types.h"
#include "globals.h"
#include "macros.h"

/* (defined buttons.c) */
extern void button_callback(void);
extern void make_button_callback(void);
extern void Pause(Widget,caddr_t,caddr_t);
extern void Run(Widget,caddr_t,caddr_t);
extern void Run_Step(Widget,caddr_t,caddr_t);
extern void Step(Widget,caddr_t,caddr_t);
extern void rule(Widget,int *,caddr_t);
extern void changeSize(Widget,XtPointer,XawPannerReport *);
extern void changeTime(Widget,XtPointer,XawPannerReport *);
extern void showEpoch();

#define __BUTTONS_H__
#endif /* ! __BUTTONS_H__ */
