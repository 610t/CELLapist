#include "X_include.h"

#include "buttons.h"

/* (defined main.c) */
extern void quit(Widget,caddr_t,caddr_t);
extern void exposeField(Widget,caddr_t,XEvent *);

/* (defined state.c) */
extern void State(Widget,caddr_t,caddr_t);

/* (define field.c) */
extern void Field(Widget,caddr_t,caddr_t);

void make_button()
{
  int i,arg_num=0;
  Arg args[10];
  char name[256];
  Widget popupShell;

  void make_rule_pulldown();
  void make_file_pulldown();

  static char * buttonLabels[]={ /* label of buttons */
    "FILE   ",
    "RULE   ",
    "RUN    ",
    "STEP   ",
    "STATE  ",
    "FIELD  ",
  };

  for(i=0;i<BUTTONS;i++)
  {
    arg_num=0;
    sprintf(name,"BTN%d",i);
    XtSetArg(args[arg_num],XtNlabel,buttonLabels[i]);  arg_num++;
    
    switch(i)
    {
    case B_FILE:
      XtSetArg(args[arg_num],XtNmenuName,"PopupFile");arg_num++;
      break;
    case B_RULE:
      XtSetArg(args[arg_num],XtNmenuName,"PopupRule");arg_num++;
      break;
    default:
      break;
    }

    /* XtSetArg(args[arg_num],XtNshapeStyle,XmuShapeOval);       arg_num++; */

    switch(i)
    {
      /* These buttons are pulldown menu */
    case B_FILE:
    case B_RULE: 
      button[i] = XtCreateManagedWidget(name,menuButtonWidgetClass
                                        ,button_panel,args,arg_num);
      break;
    default:
      button[i] = XtCreateManagedWidget(name,commandWidgetClass
                                        ,button_panel,args,arg_num);
      break;
    }
    
    switch(i)
    {
    case B_RULE:
      arg_num=0;
      XtSetArg(args[arg_num],XtNborderWidth,0);             arg_num++;
      XtSetArg(args[arg_num]
               ,XtNlabel,(char *)screen.rule->RuleName);    arg_num++;
      ruleName=XtCreateManagedWidget("RuleName",labelWidgetClass
                                     ,button_panel,args,arg_num);
      break;
    case B_STEP:
      sprintf(name,"%5d",screen.epoch);
      arg_num=0;
      XtSetArg(args[arg_num],XtNborderWidth,0);     arg_num++;
      XtSetArg(args[arg_num],XtNlabel,name);        arg_num++;
      epoch=XtCreateManagedWidget("Epoch",labelWidgetClass
                                  ,button_panel,args,arg_num);
      break;
    }
  }
  
  make_file_pulldown(); 
  make_rule_pulldown(); 
}

void make_rule_pulldown()
{
  int i,arg_num=0;
  Arg args[10];
  char name[256];
  Widget ruleShell,*ruleMenu,line;
  static int rule_num[100];

  for(i=0;i<screen.rules;i++)
    rule_num[i]=i;
  
  ruleMenu = (Widget *)malloc(sizeof(Widget)*screen.rules);
  
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"Rule"); arg_num++;
  ruleShell = XtCreatePopupShell("PopupRule",simpleMenuWidgetClass
                                 ,button[B_RULE],args,arg_num);
  
  line = XtCreateManagedWidget("Line",smeLineObjectClass
                               ,ruleShell,args,arg_num);
  for(i=0;i<screen.rules;i++)
  {
    sprintf(name,"RuleMenu%d",i);
    
    arg_num=0;
    XtSetArg(args[arg_num],XtNlabel,Rules[i].RuleName); arg_num++;
    ruleMenu[i] = XtCreateManagedWidget(name,smeBSBObjectClass
                                        ,ruleShell,args,arg_num);
    XtAddCallback(ruleMenu[i],XtNcallback,(void *)rule,&rule_num[i]);
  }
}

void make_file_pulldown()
{
#define FileMenuButtons 4
  int i,arg_num;
  Arg args[10];
  char name[256],label[256];
  Widget popupShell,fileMenu[FileMenuButtons],line;

  extern void SaveState(Widget,caddr_t,caddr_t);
  extern void LoadState(Widget,caddr_t,caddr_t);
  extern void LoadRule(Widget,caddr_t,caddr_t);

  static char *labelNames[]={	/* label of buttons */
    "LoadState",
    "Save State",
    "Load Rule",
    "Quit",
  };

  static void *buttonCallbacks[]={
    LoadState,
    SaveState,
    LoadRule,
    quit,
  };
  
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"File"); arg_num++;
  popupShell = XtCreatePopupShell("PopupFile",simpleMenuWidgetClass
                                  ,button[B_FILE],args,arg_num);
  
  line = XtCreateManagedWidget("Line",smeLineObjectClass
                               ,popupShell,args,arg_num);
  for(i=0;i<FileMenuButtons;i++)
  {
    /* make widget */
    sprintf(name,"FileMenu%d",i);
    arg_num=0;
    XtSetArg(args[arg_num],XtNlabel,labelNames[i]); arg_num++;
    
    fileMenu[i] = XtCreateManagedWidget(name,smeBSBObjectClass
                                        ,popupShell,args,arg_num);
    /* Set callbacks */
    XtAddCallback(fileMenu[i],XtNcallback,buttonCallbacks[i],NULL);
  }
}

void button_callback()
{
  int i;
  static void * buttonCallbacks[]= {
    NULL,       /* File button(pulldown menu) */
    NULL,       /* Rule button(pulldown menu) */
    Run,
    Step,
    State,
    Field,    
  };
  
  for(i=0;i<BUTTONS;i++)
  {
    if(buttonCallbacks[i]!=NULL)
      XtAddCallback(button[i],XtNcallback,buttonCallbacks[i],NULL);
  }
}

/* Below button callbacks */
void Pause(Widget w,caddr_t client_data,caddr_t call_data)
{
  int i,arg_num=0;
  Arg args[10];
  char name[256];
  
  XtRemoveTimeOut(screen.Run_timeout);
  
  sprintf(name,"RUN    ");
  XtSetArg(args[arg_num],XtNlabel,name);                arg_num++;
  XtSetValues(button[B_RUN],args,arg_num);
  
  arg_num=0;
  XtSetArg(args[arg_num],XtNsensitive,True);            arg_num++;
  for(i=0;i<BUTTONS;i++)
  {
    if( i != B_RUN )
      XtSetValues(button[i],args,arg_num);
  }
  
  XtRemoveAllCallbacks(button[B_RUN],XtNcallback);
  
  XtAddCallback(button[B_PAUSE],XtNcallback,(void *)Run,NULL);
}


void Run_by_Step(caddr_t clientdata,XtIntervalId *id)
{
  Step(screen.toplevel,NULL,NULL);
  screen.Run_timeout = XtAddTimeOut( screen.time,(void *)Run_by_Step,NULL);
}

void Run(Widget w,caddr_t client_data,caddr_t call_data)
{
  int i,arg_num=0;
  Arg args[10];
  char name[256];
  
  sprintf(name,"PAUSE  ");
  XtSetArg(args[arg_num],XtNlabel,name);                arg_num++;
  XtSetValues(button[B_RUN],args,arg_num);
  
  arg_num=0;
  XtSetArg(args[arg_num],XtNsensitive,False);       arg_num++;
  for(i=0;i<BUTTONS;i++)
  {
    if(i!=B_FILE&&i!=B_RUN)
      XtSetValues(button[i],args,arg_num);
  }
  
  XtRemoveAllCallbacks(button[B_RUN],XtNcallback);
  
  XtAddCallback(button[B_PAUSE],XtNcallback,(void *)Pause,NULL);
  screen.Run_timeout = XtAddTimeOut( screen.time,(void *)Run_by_Step,NULL);
}

void Step(Widget w,caddr_t client_data,caddr_t call_data)
{
  (screen.rule->Step)(NULL);
  screen.epoch++;
  showEpoch();
}

void showEpoch()
{
  char name[100];
  int arg_num=0;
  Arg args[10];
  
  sprintf(name,"%5d",screen.epoch);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,name);        arg_num++;
  XtSetValues(epoch,args,arg_num);
}

void changeSize(Widget w,XtPointer client_data,XawPannerReport *report)
{
  Arg args[10];
  int arg_num=0,x,y;
  char tmp[100];
  
  screen.size = SLIDERtoSIZE(report->slider_x);
  
  XtDestroyWidget(f_screen);
  make_field();
  make_cellWidget();
  
  (screen.rule->Refresh)();
  
  sprintf(tmp,"\nCELL SIZE:\n    %3d",screen.size);
  XtSetArg(args[arg_num],XtNlabel,tmp);                 arg_num++;
  XtSetValues(cell_size,args,arg_num);
}

void changeTime(Widget w,XtPointer client_data,XawPannerReport *report)
{
  Arg args[10];
  int arg_num=0,x,y;
  char tmp[100];
  
  screen.time = SLIDERtoTIME(report->slider_x);
  
  sprintf(tmp,"\nUpdate Time:\n  %5d",screen.time);
  XtSetArg(args[arg_num],XtNlabel,tmp);                 arg_num++;
  XtSetValues(update_time,args,arg_num);
}

void rule(Widget w,int *rule_num,caddr_t call_data)
{
  void ruleBody();
  
  (screen.rule->Delete)();
  screen.rule_num = *rule_num;
  ruleBody();
  (screen.rule->New)(TRUE);
}

void ruleNonNew()
{
  void ruleBody();
  
  (screen.rule->Delete)();
  ruleBody();
  (screen.rule->New)(FALSE);
}

void ruleBody()
{
  Arg args[10];
  int arg_num=0;

  XtRemoveEventHandler(screen.field,ButtonPressMask,FALSE,
                       (void *)(screen.rule->Button),NULL);
  screen.rule = &Rules[screen.rule_num];
  
  XtSetArg(args[arg_num]
           ,XtNlabel,(char *)screen.rule->RuleName);    arg_num++;
  XtSetValues(ruleName,args,arg_num);
  
  XtAddEventHandler(screen.field,ButtonPressMask,FALSE,
                    (void *)(screen.rule->Button),NULL);
}
