#include "field.h"

#include "globals.h"

void Field(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  char name[100];
  int arg_num=0,i;
  static int firstTime = TRUE;
  
  if( firstTime )
  {
    /* Top */
    FieldTop = XtCreateApplicationShell("Field",topLevelShellWidgetClass,NULL,0);

    /* Application panel */
    XtSetArg(args[arg_num],XtNorientation,XtorientVertical);    arg_num++;
    XtSetArg(args[arg_num],XtNshowGrip,False);                    arg_num++;
    FieldPanel = XtCreateManagedWidget("FieldPanel",panedWidgetClass
                                       ,FieldTop,args,arg_num);

    makeFieldButtons();
    FieldButtonCallbacks();

    makeX();

    makeY();
    XtRealizeWidget(FieldTop);
    firstTime=FALSE;
  }
  else
  {
    XtMapWidget(FieldTop);
  }
  
}

void FieldButtonCallbacks()
{
  int i;
  static void * buttonCallbacks[]={
    FieldApply,
    FieldDismiss,
  };
  
  for(i=0;i<FIELD_BUTTONS;i++)
    XtAddCallback(FieldButton[i],XtNcallback,buttonCallbacks[i],NULL);

}

void makeFieldButtons()
{
  Arg args[10];
  int arg_num=0,i;
  char name[100];

  static char *buttonLabels[]={
    "APPLY",
    "DISMISS",
  };
  
  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  FieldButtonPanel = XtCreateManagedWidget("FieldButtonPanel",boxWidgetClass
                                           ,FieldPanel,args,arg_num);
  for(i=0;i<FIELD_BUTTONS;i++)
    {
      arg_num=0;

      XtSetArg(args[arg_num],XtNlabel,buttonLabels[i]);arg_num++;

      sprintf(name,"FIELD_BTN%d",i);
      FieldButton[i] = XtCreateManagedWidget(name,commandWidgetClass
                                             ,FieldButtonPanel,args,arg_num);
    }
}

void makeX()
{
  Arg args[10];
  int arg_num=0,i;
  char name[100];

  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  FieldXPanel = XtCreateManagedWidget("FieldXPanel",boxWidgetClass
                                      ,FieldPanel,args,arg_num);
  arg_num=0;
  x=screen.x;
  XtSetArg(args[arg_num],XtNlabel,"x:");    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  FieldXTitle = XtCreateManagedWidget("FieldXTitle",labelWidgetClass
                                     ,FieldXPanel,args,arg_num);
  arg_num=0;
  sprintf(name,"%5d",x);
  XtSetArg(args[arg_num],XtNlabel,name);    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  FieldXValue = XtCreateManagedWidget("FieldXValue",labelWidgetClass
                                     ,FieldXPanel,args,arg_num);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"cells"); arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  FieldXUnit = XtCreateManagedWidget("FieldXUnit",labelWidgetClass
                                     ,FieldXPanel,args,arg_num);

  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"UP");    arg_num++;
  XtSetArg(args[arg_num],XtNstate,True);         arg_num++;
  sprintf(name,"FIELD_X_BTN%d",i);
  FieldXUpButton = XtCreateManagedWidget(name,repeaterWidgetClass
                                         ,FieldXPanel,args,arg_num);
  Xup.Text=FieldXValue;
  Xup.size=&x;
  Xup.dsize=1;
  XtAddCallback(FieldXUpButton,XtNcallback,(void *)ChangeSize,&Xup);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"DOWN");    arg_num++;
  XtSetArg(args[arg_num],XtNstate,True);         arg_num++;
  sprintf(name,"FIELD_X_BTN%d",i);
  FieldXDownButton = XtCreateManagedWidget(name,repeaterWidgetClass
                                         ,FieldXPanel,args,arg_num);
  Xdown.Text=FieldXValue;
  Xdown.size=&x;
  Xdown.dsize=-1;
  XtAddCallback(FieldXDownButton,XtNcallback,(void *)ChangeSize,&Xdown);
}  

void makeY()
{
  Arg args[10];
  int arg_num=0,i;
  char name[100];

  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  FieldYPanel = XtCreateManagedWidget("FieldYPanel",boxWidgetClass
                                         ,FieldPanel,args,arg_num);
  arg_num=0;
  y=screen.y;
  XtSetArg(args[arg_num],XtNlabel,"y:");    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  FieldYTitle = XtCreateManagedWidget("FieldYTitle",labelWidgetClass
                                     ,FieldYPanel,args,arg_num);
  arg_num=0;
  sprintf(name,"%5d",y);
  XtSetArg(args[arg_num],XtNlabel,name);    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  FieldYValue = XtCreateManagedWidget("FieldYValue",labelWidgetClass
                                     ,FieldYPanel,args,arg_num);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"cells"); arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  FieldYUnit = XtCreateManagedWidget("FieldYUnit",labelWidgetClass
                                     ,FieldYPanel,args,arg_num);

  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"UP");    arg_num++;
  XtSetArg(args[arg_num],XtNstate,True);         arg_num++;
  FieldYUpButton = XtCreateManagedWidget("FieldYUp",repeaterWidgetClass
                                         ,FieldYPanel,args,arg_num);
  Yup.Text=FieldYValue;
  Yup.size=&y;
  Yup.dsize=1;
  XtAddCallback(FieldYUpButton,XtNcallback,(void *)ChangeSize,&Yup);

  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"DOWN");    arg_num++;
  XtSetArg(args[arg_num],XtNstate,True);         arg_num++;
  FieldYDownButton = XtCreateManagedWidget("FieldYDown",repeaterWidgetClass
                                           ,FieldYPanel,args,arg_num);

  Ydown.Text=FieldYValue;
  Ydown.size=&y;
  Ydown.dsize=-1;
  XtAddCallback(FieldYDownButton,XtNcallback,(void *)ChangeSize,&Ydown);
}  

void FieldDismiss(Widget w,caddr_t client_data,caddr_t call_data)
{
  XtUnmapWidget(FieldTop);
}

void FieldApply(Widget w,caddr_t client_data,caddr_t call_data)
{
  (screen.rule->Delete)();
  free(Cell);

  screen.x=x;
  screen.y=y;
  
  Cell=(CELL *)malloc(sizeof(CELL)*screen.x*screen.y);

  XtDestroyWidget(f_screen);
  make_field();
  make_cellWidget();
  (screen.rule->New)(TRUE);
  XtUnmapWidget(FieldTop);
}

void ChangeSize(Widget w,FIELD_DATA *data,caddr_t client_data)
{
  Arg args[10];
  int arg_num=0;
  char name[100];
  
  *(data->size) += data->dsize;
  if(*(data->size) <= 1)
    *(data->size)=1;

  sprintf(name,"%5d",*(data->size));
  XtSetArg(args[arg_num],XtNlabel,name);    arg_num++;
  XtSetValues(data->Text,args,arg_num);
}
