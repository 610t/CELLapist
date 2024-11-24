#include "WolframWin.h"
#include "Wolfram.h"
  
#include "globals.h"
  
void wolframRuleSelection(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  char name[100];
  int arg_num=0,i;
  static int firstTime = TRUE;

  if( firstTime )
    {
      /* Top */
      WolfwinTop = XtCreateApplicationShell("Wolfwin",topLevelShellWidgetClass,
                                            NULL,0);
  
      /* Application panel */
      XtSetArg(args[arg_num],XtNorientation,XtorientVertical);    arg_num++;
      XtSetArg(args[arg_num],XtNshowGrip,False);                    arg_num++;
      WolfwinPanel = XtCreateManagedWidget("WolfwinPanel",panedWidgetClass
                                           ,WolfwinTop,args,arg_num);
  
      makeWolfwin();
      WolfwinButtonCallbacks();

      XtRealizeWidget(WolfwinTop);
      firstTime = FALSE;
    }
  else
    {
      XtMapWidget(WolfwinTop);
    }
}

void WolfwinButtonCallbacks()
{
  int i,arg_num;
  Arg args[10];
  
  for(i=0;i<WOLFWIN_BUTTONS;i++)
  {
    arg_num=0;
    switch(i)
    {
    case 0:
      XtAddCallback(WolfwinButton[i],XtNcallback,(void *)WolfwinApply,NULL);
      break;
    case 1:
      XtAddCallback(WolfwinButton[i],XtNcallback,(void *)ChangeRuleNum,1);
      break;
    case 2:
      XtAddCallback(WolfwinButton[i],XtNcallback,(void *)ChangeRuleNum,-1);
      break;
    default:
      break;
    }
  }
  
}

void makeWolfwin()
{
  Arg args[10];
  int arg_num,i;
  char name[100];

  arg_num=0;
  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  WolfwinButtonPanel = XtCreateManagedWidget("WolfwinButtonPanel",
                                             boxWidgetClass,
                                             WolfwinPanel,args,arg_num);

  arg_num=0;
  sprintf(name,"Code:%8d",ruleNum);
  XtSetArg(args[arg_num],XtNlabel,name);        arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0);     arg_num++;
  WolfRuleText=XtCreateManagedWidget("wolRuleText",
                                     labelWidgetClass,WolfwinPanel,
                                     args,arg_num);
  

  for(i=0;i<WOLFWIN_BUTTONS;i++)
  {
    arg_num=0;
    sprintf(name,"WOLFWIN_BTN%d",i);
    switch(i)
    {
    case 0:
      XtSetArg(args[arg_num],XtNlabel,"OKay");arg_num++;
      break;
    case 1:
      XtSetArg(args[arg_num],XtNlabel,"UP");arg_num++;
      XtSetArg(args[arg_num],XtNstate,True);arg_num++;
      break;
    case 2:
      XtSetArg(args[arg_num],XtNlabel,"DOWN");arg_num++;
      XtSetArg(args[arg_num],XtNstate,True);arg_num++;
      break;
    default:
      break;
    }
    XtSetArg(args[arg_num],XtNshapeStyle,XmuShapeOval);arg_num++;
    WolfwinButton[i] = XtCreateManagedWidget(name,repeaterWidgetClass
                                             ,WolfwinButtonPanel,args,arg_num);
  }
}

void WolfwinDismiss(Widget w,caddr_t client_data,caddr_t call_data)
{
  XtUnmapWidget(WolfwinTop);
}

void WolfwinApply(Widget w,caddr_t client_data,caddr_t call_data)
{
  void wolframSetRule(long);
  
  wolframSetRule(ruleNum);

  XtUnmapWidget(WolfwinTop);
}

void ChangeRuleNum(Widget w,int data,caddr_t client_data)
{
  Arg args[10];
  int arg_num=0;
  char name[100];
  
  ruleNum += data;
  if(ruleNum <= 0)
    ruleNum=0;
  else if(ruleNum >= (int)pow(2.0,2.0*WOLFRAM_NEIGHBOUR+1+1))
    ruleNum = (int)pow(2.0,2.0*WOLFRAM_NEIGHBOUR+1+1)-1;

  sprintf(name,"Code:%8d",ruleNum);
  XtSetArg(args[arg_num],XtNlabel,name);    arg_num++;
  XtSetValues(WolfRuleText,args,arg_num);
}

