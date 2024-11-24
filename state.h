#ifndef __STATE_H__
#include "X_include.h"
#include "types.h"

#define STATE_BUTTONS 2
#define STATE_DIST_BUTTONS 3

/* Private関数のプロトタイプ宣言 */
void make_StateButtons(void);
void make_Distribution(void);
void make_Density(void);
void make_Width(void);
void StateButtonCallbacks();
void StateDense(Widget,XtPointer,XawPannerReport *);
void StateWidth(Widget,XtPointer,XawPannerReport *);
void StateDismiss(Widget,caddr_t,caddr_t);
void StateApply(Widget,caddr_t,caddr_t);
void WidthSensitive(Widget,caddr_t,caddr_t);
void WidthUnsensitive(Widget,caddr_t,caddr_t);
void DenseSensitive(Widget,caddr_t,caddr_t);
void DenseUnsensitive(Widget,caddr_t,caddr_t);

/* 大域変数の定義 */
static char radioTranslations[] = 
  " <EnterWindow>:              highlight(Always)\n \
    <LeaveWindow>:              unhighlight()\n \
    <Btn1Down>,<Btn1Up>:        set()notify()";

static Widget StateTop;
Widget StatePanel
      ,StateButtonPanel,StateButton[STATE_BUTTONS]
      ,StateDistPanel,StateDistText,StateDistButton[STATE_DIST_BUTTONS]
      ,StateDensePanel,StateDenseText,StateDenseValue,StateDenseSlider
      ,StateWidthPanel,StateWidthText,StateWidthValue,StateWidthSlider;

int dense=10,width=10;

#define __STATE_H__
#endif /* ! __STATE_H__ */
