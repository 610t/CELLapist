#include "state.h"

#include "globals.h"

/*
        公開されている関数
*/
void State(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  char name[100];
  int arg_num=0,i;
  static int firstTime = TRUE;
  
  if(firstTime)
  {
    /* Top */
    StateTop = XtCreateApplicationShell("STATE",topLevelShellWidgetClass
                                        ,NULL,0);

    /* Application panel */
    XtSetArg(args[arg_num],XtNorientation,XtorientVertical);    arg_num++;
    XtSetArg(args[arg_num],XtNshowGrip,False);                    arg_num++;
    StatePanel = XtCreateManagedWidget("StatePanel",panedWidgetClass
                                       ,StateTop,args,arg_num);

    make_StateButtons();
    StateButtonCallbacks();

    make_Distribution();

    make_Density();

    make_Width();

    XtRealizeWidget(StateTop);
    firstTime = FALSE;
  }
  else
  {
    XtMapWidget(StateTop);
  }
}


/*
        Private関数
*/
void make_StateButtons()
{
  Arg args[10];
  int arg_num=0,i;
  char name[100];

  static char * labelButtons[]= {
    "APPLY",
    "DISMISS",
  };
  
  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  StateButtonPanel = XtCreateManagedWidget("StateButtonPanel",boxWidgetClass
                                           ,StatePanel,args,arg_num);
  for(i=0;i<STATE_BUTTONS;i++)
    {
      arg_num=0;
      sprintf(name,"STATE_BTN%d",i);

      XtSetArg(args[arg_num],XtNlabel,labelButtons[i]);arg_num++;
      StateButton[i] = XtCreateManagedWidget(name,commandWidgetClass
                                             ,StateButtonPanel,args,arg_num);
    }
}

void make_Distribution()
{
  Arg args[10];
  int arg_num=0,i;
  static int radioData[]= {0,1,2};
  char name[100];
  XtTranslations trans_table;

  static char *labelButtons[]={
    "Uniform",
    "Normal",
    "Step",
  };
  
  trans_table = XtParseTranslationTable(radioTranslations);
  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  StateDistPanel = XtCreateManagedWidget("StateDistPanel",boxWidgetClass
                                           ,StatePanel,args,arg_num);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"Distribution:");    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  StateDistText = XtCreateManagedWidget("StateDistText",labelWidgetClass
                                        ,StateDistPanel,args,arg_num);

  for(i=0;i<STATE_DIST_BUTTONS;i++)
    {
      arg_num=0;

      XtSetArg(args[arg_num],XtNlabel,labelButtons[i]);    arg_num++;

      if( i ==0 )
      {
        XtSetArg(args[arg_num],XtNstate,True);         arg_num++;
      }

      sprintf(name,"STATE_DIST_BTN%d",i);
      XtSetArg(args[arg_num],XtNradioData,&radioData[i]); arg_num++;
      StateDistButton[i] = XtCreateManagedWidget(name,toggleWidgetClass
                                                 ,StateDistPanel,args,arg_num);
      XtOverrideTranslations(StateDistButton[i],trans_table);
      switch(i)
        {
         case 0:
          XtAddCallback(StateDistButton[i],XtNcallback
                        ,(void *)WidthUnsensitive,NULL);
          XtAddCallback(StateDistButton[i],XtNcallback
                        ,(void *)DenseSensitive,NULL);
          break;
         case 1:
          XtAddCallback(StateDistButton[i],XtNcallback
                        ,(void *)WidthSensitive,NULL);
          XtAddCallback(StateDistButton[i],XtNcallback
                        ,(void *)DenseSensitive,NULL);
          break;
         case 2:
          XtAddCallback(StateDistButton[i],XtNcallback
                        ,(void *)WidthSensitive,NULL);
          XtAddCallback(StateDistButton[i],XtNcallback
                        ,(void *)DenseUnsensitive,NULL);
          break;
            default:
          break;
        }  
      if(i!=0)
        XawToggleChangeRadioGroup(StateDistButton[i],StateDistButton[0]);
    }
}  

void make_Density()
{
  char name[100];
  Arg args[10];
  int arg_num=0;

  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  StateDensePanel = XtCreateManagedWidget("StateDensePanel",boxWidgetClass
                                           ,StatePanel,args,arg_num);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"Density     :");    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  StateDenseText = XtCreateManagedWidget("StateDenseText",labelWidgetClass
                                         ,StateDensePanel,args,arg_num);

  arg_num=0;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  sprintf(name,"%3d%%",dense);
  XtSetArg(args[arg_num],XtNlabel,name);    arg_num++;
  StateDenseValue = XtCreateManagedWidget("StateDenseValue",labelWidgetClass
                                          ,StateDensePanel,args,arg_num);
  arg_num = 0;
  XtSetArg(args[arg_num],XtNwidth,105); arg_num++;
  XtSetArg(args[arg_num],XtNheight,10); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasWidth,105); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasHeight,10); arg_num++;
  XtSetArg(args[arg_num],XtNsliderWidth,5); arg_num++;
  XtSetArg(args[arg_num],XtNsliderHeight,10); arg_num++;
  XtSetArg(args[arg_num],XtNinternalSpace,0); arg_num++;
  XtSetArg(args[arg_num],XtNshadowThickness,0); arg_num++;
  XtSetArg(args[arg_num],XtNsliderX,dense); arg_num++;
  XtSetArg(args[arg_num],XtNrubberBand,True); arg_num++;
  StateDenseSlider = XtCreateManagedWidget("Density",pannerWidgetClass
                                           ,StateDensePanel,args,arg_num);
  XtAddCallback(StateDenseSlider,XtNreportCallback,(void *)StateDense,NULL);
}

void StateDense(Widget w,XtPointer client_data,XawPannerReport *report)
{
  Arg args[10];
  int arg_num=0;
  char name[100];
  
  dense=report->slider_x;

  sprintf(name,"%3d%%",dense);
  XtSetArg(args[arg_num],XtNlabel,name); arg_num++;
  XtSetValues(StateDenseValue,args,arg_num);
}

void make_Width()
{
  char name[100];
  Arg args[10];
  int arg_num=0;

  XtSetArg(args[arg_num],XtNorientation,XtorientHorizontal);    arg_num++;
  XtSetArg(args[arg_num],XtNshowGrip,False); arg_num++;
  StateWidthPanel = XtCreateManagedWidget("StateWidthPanel",boxWidgetClass
                                           ,StatePanel,args,arg_num);
  arg_num=0;
  XtSetArg(args[arg_num],XtNlabel,"Width       :");    arg_num++;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  StateWidthText = XtCreateManagedWidget("StateWidthText",labelWidgetClass
                                         ,StateWidthPanel,args,arg_num);

  arg_num=0;
  XtSetArg(args[arg_num],XtNborderWidth,0); arg_num++;
  sprintf(name,"%3d%%",width);
  XtSetArg(args[arg_num],XtNlabel,name);    arg_num++;
  StateWidthValue = XtCreateManagedWidget("StateWidthValue",labelWidgetClass
                                          ,StateWidthPanel,args,arg_num);
  arg_num = 0;
  XtSetArg(args[arg_num],XtNwidth,105); arg_num++;
  XtSetArg(args[arg_num],XtNheight,10); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasWidth,105); arg_num++;
  XtSetArg(args[arg_num],XtNcanvasHeight,10); arg_num++;
  XtSetArg(args[arg_num],XtNsliderWidth,5); arg_num++;
  XtSetArg(args[arg_num],XtNsliderHeight,10); arg_num++;
  XtSetArg(args[arg_num],XtNinternalSpace,0); arg_num++;
  XtSetArg(args[arg_num],XtNshadowThickness,0); arg_num++;
  XtSetArg(args[arg_num],XtNsliderX,width); arg_num++;
  XtSetArg(args[arg_num],XtNrubberBand,True); arg_num++;
  StateWidthSlider = XtCreateManagedWidget("Width",pannerWidgetClass
                                           ,StateWidthPanel,args,arg_num);
  XtAddCallback(StateWidthSlider,XtNreportCallback,(void *)StateWidth,NULL);
  WidthUnsensitive(StateWidthSlider,NULL,NULL);
}

void StateWidth(Widget w,XtPointer client_data,XawPannerReport *report)
{
  Arg args[10];
  int arg_num=0;
  char name[100];
  
  width=report->slider_x;

  sprintf(name,"%3d%%",width);
  XtSetArg(args[arg_num],XtNlabel,name); arg_num++;
  XtSetValues(StateWidthValue,args,arg_num);
}

void StateButtonCallbacks()
{
  int i,arg_num;
  Arg args[10];

  for(i=0;i<STATE_BUTTONS;i++)
    {
      arg_num=0;
      switch(i)
        {
         case 0:
          XtAddCallback(StateButton[i],XtNcallback
                        ,(void *)StateApply,&dense);
          break;
         case 1:
          XtAddCallback(StateButton[i],XtNcallback,(void *)StateDismiss,NULL);
          break;
            default:
          break;
        }
    }

}

void StateApply(Widget w,caddr_t client_data,caddr_t call_data)
{
  screen.rule->Random(w,&dense,call_data);
  XtUnmapWidget(StateTop);
}

void StateDismiss(Widget w,caddr_t client_data,caddr_t call_data)
{
  XtUnmapWidget(StateTop);
}

void WidthSensitive(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  int arg_num=0;
  
  XtSetArg(args[arg_num],XtNsensitive,True); arg_num++;

  XtSetValues(StateWidthText,args,arg_num);
  XtSetValues(StateWidthValue,args,arg_num);
  XtSetValues(StateWidthSlider,args,arg_num);
}

void WidthUnsensitive(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  int arg_num=0;
  
  XtSetArg(args[arg_num],XtNsensitive,False); arg_num++;
  XtSetValues(StateWidthText,args,arg_num);
  XtSetValues(StateWidthValue,args,arg_num);
  XtSetValues(StateWidthSlider,args,arg_num);
}

void DenseSensitive(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  int arg_num=0;
  
  XtSetArg(args[arg_num],XtNsensitive,True); arg_num++;

  XtSetValues(StateDenseText,args,arg_num);
  XtSetValues(StateDenseValue,args,arg_num);
  XtSetValues(StateDenseSlider,args,arg_num);
}

void DenseUnsensitive(Widget w,caddr_t client_data,caddr_t call_data)
{
  Arg args[10];
  int arg_num=0;
  
  XtSetArg(args[arg_num],XtNsensitive,False); arg_num++;
  XtSetValues(StateDenseText,args,arg_num);
  XtSetValues(StateDenseValue,args,arg_num);
  XtSetValues(StateDenseSlider,args,arg_num);
}

