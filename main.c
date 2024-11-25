#include <stdio.h>
#include <math.h>
#include <stdlib.h>
  
#include "X_include.h"
  
#include "buttons.h"
#include "window.h"

#include "Wolfram.h"  
#include "Life.h"
#include "Conveyor.h"
#include "2DRoad.h"
#include "Diffuse.h"
#include "Pattern.h"
#include "Spread.h"
#include "Rho.h"
  
CELL_WINDOW screen;
CELL *Cell;
RuleTbl *ruleT;
Widget panel,button_panel
  ,button[BUTTONS],f_screen,field,title,ruleName,epoch
  ,cell_size,size_slide
  ,update_time,update_slide,state_display;

/**/
int sensor_num,broken_num,goal,miss_num;
long st_pos;
float total_time;

#ifdef __LargeLoad__
int block_size=1,Obj_cnt=0,Obj_max = 0;
OBJECT *Obj;
struct _pixel target;
#endif /* __LargeLoad__ */
/**/

RULE Rules[]=
{
/*
{0,"Wolfram 1D CAs\n  k=2,r=2"
   ,wolframNew,wolframDelete
     ,wolframStep
       ,wolframRandom
         ,wolframButton,wolframRefresh},
*/
{2,"Conveyor System\n     (4)"
   ,conveyorNew,conveyorDelete
     ,conveyorStep4
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
{2,"Conveyor System\n     (4Rand)"
   ,conveyorNew,conveyorDelete
     ,conveyorStep4Rand
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
{7,"Conveyor System\n     (4MOD)"
   ,conveyorNew,conveyorDelete
     ,conveyorStep4MOD
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
{1,"Conveyor System\n     (8)"
   ,conveyorNew,conveyorDelete
     ,conveyorStep8
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
{1,"Conveyor System\n     (8New)"
   ,conveyorNew,conveyorDelete
     ,conveyorStep8New
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
{8,"Conveyor System\n     (8Fujiata)"
   ,conveyorNew,conveyorDelete
     ,conveyorStep8Fujita
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
{8,"2D Car System"
   ,carNew,carDelete
     ,carStep
       ,carRandom
         ,carButton,carRefresh},
{0,"2D rho system"
   ,rhoNew,rhoDelete
     ,rhoStepGA
       ,rhoRandom
         ,rhoButton,rhoRefresh},
{3,"Life GAME      "
   ,lifeNew,lifeDelete
     ,lifeStep
       ,lifeRandom
         ,lifeButton,lifeRefresh},
{4,"Diffusion Eqn. "
   ,diffuseNew,diffuseDelete
     ,diffuseStep
       ,diffuseRandom
         ,diffuseButton,diffuseRefresh},
{5,"Pattern Formation"
   ,patternNew,patternDelete
     ,patternStep
       ,patternRandom
         ,patternButton,patternRefresh},
{6,"Infomation Spread"
   ,spreadNew,spreadDelete
     ,spreadStep
       ,spreadRandom
         ,spreadButton,spreadRefresh},
{9,"Conveyor System\n  (GA rule)"
   ,conveyorNew,conveyorDelete
     ,conveyorStepGA
       ,conveyorRandom
         ,conveyorButton,conveyorRefresh},
};


void exposeField(Widget w,caddr_t client_data,XEvent *event)
{
  XCopyArea(screen.disp,screen.pix,XtWindow(screen.field),screen.gc,
            0,0,
            screen.x*screen.size,screen.y*screen.size,
            0,0);
}

void quit(Widget w,caddr_t client_data,caddr_t call_data)
{
  exit(0);
}

int main(int argc,char *argv[])
{
  int i,arg_num,x,y;
  Arg args[10];
  char name[256];
  
  /* Create Base Window */
  screen.toplevel = XtInitialize(argv[0],"CELLapist",NULL,0,&argc,argv);
    
  /* Initialize variables */
  screen.x = CELL_X;
  screen.y = CELL_Y;
  screen.size = CELL_SIZE;
  screen.time = 100;
  screen.epoch = 0;
  screen.rules = sizeof(Rules)/sizeof(RULE) - 1; /* GA can't select */
  screen.rule_num = 0;
  screen.rule = &Rules[screen.rule_num];
  
  /* alloc Cell space */
  Cell=(CELL *)malloc(sizeof(CELL)*screen.x*screen.y);
  
  /* Create panel window */
  arg_num=0;
  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False);                    arg_num++;
  panel = XtCreateManagedWidget("panel",panedWidgetClass
                                ,screen.toplevel,args,arg_num);
  
  /* Creat button panel */
  arg_num=0;
  XtSetArg(args[arg_num],XtNorientation,XtorientVertical);      arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False);                    arg_num++;
  button_panel = XtCreateManagedWidget("BTN_panel",boxWidgetClass
                                       ,panel,args,arg_num);

  /* Creat Title window */
  arg_num=0;
/*
  XtSetArg(args[arg_num],XtNforeground,"red");          arg_num++;
  XtSetArg(args[arg_num],XtNbackground,"blue");         arg_num++;
 */
  XtSetArg(args[arg_num],XtNlabel,"CELLapist \nfor X"); arg_num++;
  title = XtCreateManagedWidget("Title",labelWidgetClass
                                ,button_panel,args,arg_num);
  
  /* Set up Buttons */
  make_button();
  button_callback();
  
  make_slider();

  make_field();
  makeStateDisplay();
  
  /* Check color of this display */
  if((int)(pow(2.0,(float)screen.depth)) > COLOR_MAX)
  {
    screen.colormax=COLOR_MAX;
    allocateColor(TRUE);
  }
  else
  {
    screen.Color[0].pixel=0;
    screen.Color[1].pixel=1;
    screen.colormax=2;
  }
  
  /* Set gc */
  {
    XGCValues gcv;

    gcv.line_width=1;
    screen.gc = XCreateGC(XtDisplay(field),
                          XtWindow(field),
                          GCLineWidth,&gcv);
  }

  /* Font Initialize */
  screen.font = XLoadQueryFont(screen.disp,"a14");

  /* Make Cell-window */
  make_cellWidget();
  
  /* セルの初期化 */
  (screen.rule->New)();
  
  XtMainLoop();
}
