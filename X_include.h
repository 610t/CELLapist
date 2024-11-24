#ifndef __X_INCLUDE_H__
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>
#ifdef MY_XAW3D
#  include <X11/Xaw3d/XawInit.h>
#  include <X11/Xaw3d/Paned.h>
#  include <X11/Xaw3d/Box.h>
#  include <X11/Xaw3d/Form.h>
#  include <X11/Xaw3d/Simple.h>
#  include <X11/Xaw3d/Grip.h>
#  include <X11/Xaw3d/Command.h>
#  include <X11/Xaw3d/SimpleMenu.h>
#  include <X11/Xaw3d/SmeBSB.h>
#  include <X11/Xaw3d/SmeLine.h>
#  include <X11/Xaw3d/MenuButton.h>
#  include <X11/Xaw3d/Label.h>
#  include <X11/Xaw3d/Panner.h>
#  include <X11/Xaw3d/Toggle.h>
#  include <X11/Xaw3d/Reports.h>
#  include <X11/Xaw3d/Repeater.h>
#  include <X11/Xaw3d/Viewport.h>
#else
#  include <X11/Xaw/XawInit.h>
#  include <X11/Xaw/Paned.h>
#  include <X11/Xaw/Box.h>
#  include <X11/Xaw/Form.h>
#  include <X11/Xaw/Simple.h>
#  include <X11/Xaw/Grip.h>
#  include <X11/Xaw/Command.h>
#  include <X11/Xaw/SimpleMenu.h>
#  include <X11/Xaw/SmeBSB.h>
#  include <X11/Xaw/SmeLine.h>
#  include <X11/Xaw/MenuButton.h>
#  include <X11/Xaw/Label.h>
#  include <X11/Xaw/Panner.h>
#  include <X11/Xaw/Toggle.h>
#  include <X11/Xaw/Reports.h>
#  include <X11/Xaw/Repeater.h>
#  include <X11/Xaw/Viewport.h>
#endif /* MY_XAW3D */
#include <X11/Xmu/Atoms.h>
#include <X11/Xmu/Drawing.h>

/* Xの外観に関する定義 */
#define BUTTONS 6
/* ボタンの数とラベルの対応 */
#define B_FILE          0
#define B_RULE          1
#define B_RUN           2
#define B_PAUSE         2
#define B_STEP          3
#define B_STATE         4
#define B_FIELD         5

/* 範囲などに関する定数 */
#define SLIDER_HEIGHT 10
#define SLIDER_WIDGET_WIDTH 105
#define SLIDER_WIDTH       5
#define SLIDER_RANGE (float)(SLIDER_WIDGET_WIDTH-SLIDER_WIDTH)

#define TIME_MIN 1
#define TIME_MAX 1000
#define TIMEtoSLIDER(x) (int)(SLIDER_RANGE*((x)-TIME_MIN)/(TIME_MAX-TIME_MIN))
#define SLIDERtoTIME(x) (TIME_MIN+(int)((x)/(float)SLIDER_RANGE*(TIME_MAX-TIME_MIN)))

#define CELL_SIZE_MIN 2
#define CELL_SIZE_MAX (20)
#define SIZEtoSLIDER(x) (int)((SLIDER_RANGE*((x)-CELL_SIZE_MIN))/(CELL_SIZE_MAX-CELL_SIZE_MIN))
#define SLIDERtoSIZE(x) (2*(CELL_SIZE_MIN/2+(int)((x)/(float)SLIDER_RANGE*(CELL_SIZE_MAX/2-CELL_SIZE_MIN))))

#define COLOR_MAX 62

#define __X_INCLUDE_H__
#endif /* __X_INCLUDE_H__ */
