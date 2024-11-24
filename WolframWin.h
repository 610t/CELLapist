#ifndef __WOLFWIN_H__
#include "X_include.h"
#include "types.h"

#define WOLFWIN_BUTTONS 3

/* Private$B4X?t$N%W%m%H%?%$%W@k8@(B */
void makeWolfwin(void);
void WolfwinButtonCallbacks();
void WolfwinApply(Widget,caddr_t,caddr_t);
void WolfwinUp(Widget,caddr_t,caddr_t);
void WolfwinDown(Widget,caddr_t,caddr_t);
void ChangeRuleNum(Widget,int ,caddr_t);

/* $BBg0hJQ?t$NDj5A(B */
static Widget WolfwinTop;
Widget WolfwinPanel
      ,WolfwinButtonPanel,WolfwinButton[WOLFWIN_BUTTONS]
      ,WolfRuleText
      ,WolfwinXPanel,WolfwinXTitle,WolfwinXValue,WolfwinXUnit
       ,WolfwinXUpButton,WolfwinXDownButton
      ,WolfwinYPanel,WolfwinYTitle,WolfwinYValue,WolfwinYUnit
       ,WolfwinYUpButton,WolfwinYDownButton;

static long ruleNum;

#define __WOLFWIN_H__
#endif /* ! __WOLFWIN_H__ */

