#ifndef __GLOBALS_H__
#include "types.h"

#if defined(__LargeLoad__)
# include "largeload.h"
#endif

/* グローバル変数 */
#ifdef __CELLapist__
extern Widget panel,
  button_panel,
  button[],
  f_screen,
  field,title,ruleName,epoch,
  cell_size,size_slide,
  update_time,update_slide,
  state_display;
extern RuleTbl *ruleT;
#endif /* __CELLapist__ */
#ifdef __GA__ 
extern int sensor_num,broken_num,goal,miss_num;
extern float total_time;
extern long st_pos;
#endif /* __GA__ */

#ifdef __LargeLoad__
extern int block_size,Obj_cnt,Obj_max;
extern OBJECT *Obj;
extern struct _pixel target;
#endif /* __LargeLoad__ */

extern CELL_WINDOW screen;
extern CELL *Cell;
extern RULE Rules[];

#define __GLOBALS_H__
#endif /* ! __GLOBALS_H__ */
