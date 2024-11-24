#ifndef __FIELD_H__
#include "X_include.h"
#include "types.h"

#define FIELD_BUTTONS 2

typedef struct _field_Data
{
  Widget Text;
  int *size;
  int dsize;
} FIELD_DATA;

/* Private$B4X?t$N%W%m%H%?%$%W@k8@(B */
void makeFieldButtons(void);
void makeX(void);
void makeY(void);
void FieldButtonCallbacks();
void FieldDismiss(Widget,caddr_t,caddr_t);
void FieldApply(Widget,caddr_t,caddr_t);
void ChangeSize(Widget,FIELD_DATA * ,caddr_t);

/* $BBg0hJQ?t$NDj5A(B */
static Widget FieldTop;
Widget FieldPanel
      ,FieldButtonPanel,FieldButton[FIELD_BUTTONS]
      ,FieldXPanel,FieldXTitle,FieldXValue,FieldXUnit
       ,FieldXUpButton,FieldXDownButton
      ,FieldYPanel,FieldYTitle,FieldYValue,FieldYUnit
       ,FieldYUpButton,FieldYDownButton;

int x,y;
FIELD_DATA Xup,Xdown,Yup,Ydown;

#define __FIELD_H__
#endif /* ! __FIELD_H__ */

