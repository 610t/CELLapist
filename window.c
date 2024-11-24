#include "X_include.h"

#include "window.h"


extern void exposeField(Widget,caddr_t,XEvent*);
extern void changeTime(Widget,XtPointer,XawPannerReport);
extern void changeSize(Widget,XtPointer,XawPannerReport);

void make_cellWidget()
{
  int arg_num;
  Arg args[20];


  arg_num=0;
  XtSetArg(args[arg_num],XtNheight       ,screen.y*screen.size);  arg_num++;
  XtSetArg(args[arg_num],XtNwidth        ,screen.x*screen.size);  arg_num++;
  XtSetArg(args[arg_num],XtNlabel               ,"");             arg_num++;
  XtSetArg(args[arg_num],XtNhighlightThickness  ,0);              arg_num++;
  XtSetArg(args[arg_num],XtNright               ,XtChainLeft);    arg_num++;
  XtSetArg(args[arg_num],XtNleft                ,XtChainLeft);    arg_num++;
  XtSetArg(args[arg_num],XtNtop                  ,XtChainTop);    arg_num++;
  XtSetArg(args[arg_num],XtNbottom              ,XtChainTop);     arg_num++;
  screen.field = XtCreateManagedWidget("CELL",labelWidgetClass
                                       ,field,args,arg_num);
  screen.pix   = XCreatePixmap(XtDisplay(screen.field),
                               XtWindow(screen.field),
                               screen.x*screen.size,screen.y*screen.size,
                               screen.depth);

  XSetForeground(XtDisplay(screen.field),screen.gc,0);
  XFillRectangle(XtDisplay(screen.field),
                 screen.pix,
                 screen.gc,
                 0,0,screen.x*screen.size,screen.x*screen.size);
  
  XtAddEventHandler(screen.field,ExposureMask,FALSE,
                    (void *)exposeField,NULL);
  XtAddEventHandler(screen.field,ButtonPressMask,FALSE,
                    (void *)(screen.rule->Button),NULL);
}

void allocateColor(int mode)
{
  int i;
  Colormap cmap;

  cmap=DefaultColormap(screen.disp,DefaultScreen(screen.disp));

  if(mode == TRUE)
    XAllocColorCells(screen.disp,cmap,True,
                     NULL,0,screen.cells,screen.colormax);
  
  screen.Color[0].red  = 0;
  screen.Color[0].blue = 0;
  screen.Color[0].green= 0;
  screen.Color[0].flags = DoRed|DoGreen|DoBlue;
  screen.Color[0].pixel = screen.cells[0];

  for(i=1;i<screen.colormax;i++)
    {
      screen.Color[i].red  
        = (int)(65535.0-65535.0/2.0*(i-1)/(COLOR_MAX-2.0));
      screen.Color[i].blue 
        = (int)(65535.0-65535.0/2.0*((COLOR_MAX-2)-(i-1))/(COLOR_MAX-2.0));
      screen.Color[i].green
        = 0;
      screen.Color[i].flags = DoRed|DoGreen|DoBlue;

      screen.Color[i].pixel = screen.cells[i];
    }

  XStoreColors(screen.disp,cmap,screen.Color,screen.colormax);
}

/* Replaced by Macro version
int pos(int x,int y)
{
  return(y*screen.x+x);
}

int pos_x(int position)
{
  return(position%screen.y);
}       

int pos_y(int position)
{
  return(position/screen.y);
}       
*/

void make_slider()
{
  Arg args[20];
  int arg_num=0;
  char tmp[100];
  int i;
  
  sprintf(tmp,"\nCELL SIZE:\n    %3d",screen.size);
  XtSetArg(args[arg_num],XtNlabel,tmp);                 arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0);             arg_num++;
  cell_size = XtCreateManagedWidget("CELL SIZE",labelWidgetClass
                                    ,button_panel,args,arg_num);

  arg_num = 0;
  XtSetArg(args[arg_num],XtNwidth,SLIDER_WIDGET_WIDTH); arg_num++;
  XtSetArg(args[arg_num],XtNheight,SLIDER_HEIGHT); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasWidth,SLIDER_WIDGET_WIDTH); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasHeight,SLIDER_HEIGHT); arg_num++;
  XtSetArg(args[arg_num],XtNsliderWidth,SLIDER_WIDTH); arg_num++;
  XtSetArg(args[arg_num],XtNsliderHeight,SLIDER_HEIGHT); arg_num++;
  XtSetArg(args[arg_num],XtNinternalSpace,0); arg_num++;
  XtSetArg(args[arg_num],XtNshadowThickness,0); arg_num++;
  XtSetArg(args[arg_num],XtNsliderX,SIZEtoSLIDER(screen.size)); arg_num++;
  XtSetArg(args[arg_num],XtNrubberBand,True); arg_num++;
  size_slide = XtCreateManagedWidget("CELL SIZE",pannerWidgetClass
                                    ,button_panel,args,arg_num);
  XtAddCallback(size_slide,XtNreportCallback,(void *)changeSize,NULL);

  arg_num = 0;
  sprintf(tmp,"\nUpdate Time:\n  %5d",screen.time);
  XtSetArg(args[arg_num],XtNlabel,tmp);                 arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0);             arg_num++;
  update_time = XtCreateManagedWidget("UPDATE TIME",labelWidgetClass
                                      ,button_panel,args,arg_num);

  arg_num = 0;
  XtSetArg(args[arg_num],XtNwidth,SLIDER_WIDGET_WIDTH); arg_num++;
  XtSetArg(args[arg_num],XtNheight,SLIDER_HEIGHT); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasWidth,SLIDER_WIDGET_WIDTH); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasHeight,SLIDER_HEIGHT); arg_num++;
  XtSetArg(args[arg_num],XtNsliderWidth,SLIDER_WIDTH); arg_num++;
  XtSetArg(args[arg_num],XtNsliderHeight,SLIDER_HEIGHT); arg_num++;
  XtSetArg(args[arg_num],XtNinternalSpace,0); arg_num++;
  XtSetArg(args[arg_num],XtNshadowThickness,0); arg_num++;
  XtSetArg(args[arg_num],XtNsliderX,TIMEtoSLIDER(screen.time)); arg_num++;
  XtSetArg(args[arg_num],XtNrubberBand,True); arg_num++;
  update_slide = XtCreateManagedWidget("UPDATE TIME",pannerWidgetClass
                                    ,button_panel,args,arg_num);
  XtAddCallback(update_slide,XtNreportCallback,(void *)changeTime,NULL); 
}

void make_field()
{
  Arg args[10];
  int arg_num=0;

  XtSetArg(args[arg_num],XtNallowHoriz,True);arg_num++;
  XtSetArg(args[arg_num],XtNallowVert,True);arg_num++;
  XtSetArg(args[arg_num],XtNheight,screen.y*screen.size+2);arg_num++;
  XtSetArg(args[arg_num],XtNwidth ,screen.x*screen.size+2);arg_num++;
  f_screen = XtCreateManagedWidget("screen",viewportWidgetClass
                                  ,panel,args,arg_num);
  
  XtRealizeWidget(screen.toplevel);
  screen.disp = XtDisplay(screen.toplevel);
  screen.depth= DefaultDepth(screen.disp,0);

  arg_num=0;
  XtSetArg(args[arg_num],XtNheight,screen.y*screen.size);arg_num++;
  XtSetArg(args[arg_num],XtNwidth ,screen.x*screen.size);arg_num++;
  XtSetArg(args[arg_num],XtNdefaultDistance , 0);arg_num++;

  field = XtCreateManagedWidget("field",formWidgetClass
                                ,f_screen,args,arg_num);

}

void makeStateDisplay()
{
  Arg args[10];
  int arg_num=0;

  XtSetArg(args[arg_num],XtNheight,CELL_SIZE);  arg_num++;
  XtSetArg(args[arg_num],XtNwidth ,CELL_SIZE);  arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0);     arg_num++;
  
  state_display = XtCreateManagedWidget("stateDisplay",formWidgetClass
                                        ,button_panel,args,arg_num);
}

