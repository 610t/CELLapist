#include "Spread.h"

#include "globals.h"

/* Private関数のプロトタイプ宣言 */
void spreadUpdateState(void);
void spreadUpdateCellState(CELL *);
void spreadSetState(void);
void spreadSetCellState(CELL *);
void spreadDrawCell(int,int,int);
int spreadAliveNeighbour(CELL *);
void spreadCheckANDCount(int,int,int,int,int *);

/*
   公開されている関数
   */
/* FIELDをボタンクリックした時の動作 (Button) */
void spreadButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);
  
  switch(Cell[position].state)
    {
     case SP_VACUM_STATE:
      Cell[position].color=SP_WAIT1_STATE;
      Cell[position].state=SP_WAIT1_STATE;
      break;
     case SP_WAIT1_STATE:
      Cell[position].color=SP_INFO_STATE;
      Cell[position].state=SP_INFO_STATE;
      break;
     case SP_INFO_STATE:
      Cell[position].color=SP_CONTROL_STATE;
      Cell[position].state=SP_CONTROL_STATE;
      break;
     case SP_CONTROL_STATE:
      Cell[position].color=SP_BROKEN_STATE;
      Cell[position].state=SP_BROKEN_STATE;
      break;
     case SP_BROKEN_STATE:
      Cell[position].color=SP_VACUM_STATE;
      Cell[position].state=SP_VACUM_STATE;
      break;
    }

  spreadDrawCell(x,y,Cell[position].color);
  XCopyArea(screen.disp,screen.pix,
            XtWindow(screen.field),
            screen.gc,
            x*screen.size,y*screen.size,
            (x+1)*screen.size,(y+1)*screen.size,
            x*screen.size,y*screen.size);
}

/* destoractor (Delete) */
void spreadDelete()
{
  return;
}

/* セルの初期化 (New) */
void spreadAllocColor()
{
  Colormap cmap;

  cmap=DefaultColormap(screen.disp,DefaultScreen(screen.disp));

  screen.Color[SP_VACUM_STATE].red  = 0;
  screen.Color[SP_VACUM_STATE].blue = 0;
  screen.Color[SP_VACUM_STATE].green= 0;

  screen.Color[SP_WAIT1_STATE].red  = 40000;
  screen.Color[SP_WAIT1_STATE].blue = 0;
  screen.Color[SP_WAIT1_STATE].green= 0;

  screen.Color[SP_INFO_STATE].red  = 65535;
  screen.Color[SP_INFO_STATE].blue = 0;
  screen.Color[SP_INFO_STATE].green= 0;

  screen.Color[SP_CONTROL_STATE].red  = 0;
  screen.Color[SP_CONTROL_STATE].blue = 0;
  screen.Color[SP_CONTROL_STATE].green= 65535;

  screen.Color[SP_GOAL_STATE].red  = 65535;
  screen.Color[SP_GOAL_STATE].blue = 65535;
  screen.Color[SP_GOAL_STATE].green= 0;

  screen.Color[SP_BROKEN_STATE].red  = 65535;
  screen.Color[SP_BROKEN_STATE].blue = 65535;
  screen.Color[SP_BROKEN_STATE].green= 65535;

  XStoreColors(screen.disp,cmap,screen.Color,screen.colormax);
}

void spreadNew(int init_f)
{
  int x,y,position;
  extern void spreadAllocColor();
  
  XGCValues gcv;

  gcv.function=GXcopy;
  XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);
  spreadAllocColor();

  screen.epoch=0;
  showEpoch();
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        position=pos(x,y);
	Cell[position].x                = x;
	Cell[position].y                = y;
        Cell[position].isUpdated        = FALSE;
        Cell[position].state            = SP_VACUM_STATE;
        Cell[position].newstate         = SP_VACUM_STATE;
        Cell[position].color            = SP_VACUM_STATE;
        spreadDrawCell(x,y,0);
      }
  exposeField(screen.field,NULL,NULL);
}

/* セル状態の更新 (Step) */

void spreadStep(void)
{
  spreadUpdateState();
  spreadSetState();
}

/* セルの再描画 (Refresh) */
void spreadRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        spreadDrawCell(x,y,Cell[pos(x,y)].color);
      }
  exposeField(screen.field,NULL,NULL);
}

/* ランダムに初期化 (Random) */
void spreadRandom(Widget w,int *dense,caddr_t call_data)
{
  int x,y,s;
  float tau,radius;
  extern Widget StateDistButton[];
  extern Widget StateTop;
  extern int dense,width;

  /*
     XtDestroyWidget(StateTop);
     */
  s = *(int *)XawToggleGetCurrent(StateDistButton[1]);
  
  switch(s)
    {
     case 0:
      for(y=0;y<screen.y;y++)
        for(x=0;x<screen.x;x++)
          {
            if(rand()%100>=dense)
              {
                Cell[pos(x,y)].state = SP_VACUM_STATE;
                Cell[pos(x,y)].newstate = SP_VACUM_STATE;
                Cell[pos(x,y)].color = SP_VACUM_STATE;
              }
            else
              {
                Cell[pos(x,y)].state = SP_VACUM_STATE;
                Cell[pos(x,y)].newstate = SP_VACUM_STATE;
                Cell[pos(x,y)].color = SP_VACUM_STATE;
              }
          }
      break;
     case 1:
      tau=-2.0*(width/100.0)*MIN(screen.x,screen.y)/2.0;
      for(y=0;y<screen.y;y++)
        for(x=0;x<screen.x;x++)
          {
            radius=sqrt((double)( (screen.x/2.0-x)*(screen.x/2.0-x)
                                 +(screen.y/2.0-y)*(screen.y/2.0-y)));
            if((rand()%100)*exp(radius/tau)>=100-dense)
              {
                Cell[pos(x,y)].state = SP_VACUM_STATE;
                Cell[pos(x,y)].newstate = 1;
                Cell[pos(x,y)].color =SP_VACUM_STATE;
              }
            else
              {
                Cell[pos(x,y)].state = SP_VACUM_STATE;
                Cell[pos(x,y)].newstate = 0;
                Cell[pos(x,y)].color = 0;
              }
          }
      break;
     case 2:
      tau=(width/100.0)*MIN(screen.x,screen.y)/2.0;
      for(y=0;y<screen.y;y++)
        for(x=0;x<screen.x;x++)
          {
            radius=sqrt((double)( (screen.x/2.0-x)*(screen.x/2.0-x)
                                 +(screen.y/2.0-y)*(screen.y/2.0-y)));
            if(radius>=tau)
              {
                Cell[pos(x,y)].state = 0;
                Cell[pos(x,y)].newstate = 0;
                Cell[pos(x,y)].color = 0;
              }
            else
              {
                Cell[pos(x,y)].state = 1;
                Cell[pos(x,y)].newstate = 1;
                Cell[pos(x,y)].color =1;
              }
          }
     default:
      break;
    }
  (screen.rule->Refresh)();
  screen.epoch=0;
  showEpoch();
}

/*
   Private関数
   */
int spreadAliveNeighbour(CELL *celluar)
{
  int num=0,x,y;

  x=celluar->x; y=celluar->y;

  spreadCheckANDCount(x,y,-1, 0,&num);
  spreadCheckANDCount(x,y,-1,-1,&num);
  spreadCheckANDCount(x,y,-1,+1,&num);

  spreadCheckANDCount(x,y, 0,-1,&num);
  spreadCheckANDCount(x,y, 0,+1,&num);
  
  spreadCheckANDCount(x,y,+1, 0,&num);
  spreadCheckANDCount(x,y,+1,-1,&num);
  spreadCheckANDCount(x,y,+1,+1,&num);

  return(num);
}

void spreadCheckANDCount(int x,int y,int dx,int dy,int *num)
{
  int nowX,nowY;
  
  nowX=x+dx;
  nowY=y+dy;

  if(nowX>=0 && nowX<screen.x)
    if(nowY>=0 && nowY<screen.y)
      {
        if(Cell[pos(x,y)].state != SP_VACUM_STATE 
           && Cell[pos(nowX,nowY)].isUpdated == FALSE)
          (spreadUpdateCellState)(&Cell[pos(nowX,nowY)]);
        if(Cell[pos(nowX,nowY)].state==SP_INFO_STATE||
           Cell[pos(nowX,nowY)].state==SP_CONTROL_STATE)
          (*num)++;
      }
}

void spreadDrawCell(int x,int y,int color)
{
  if( color < sizeof(screen.Color))
    XSetForeground(screen.disp,screen.gc,screen.Color[color].pixel);
  else
    XSetForeground(screen.disp,screen.gc
                   ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));

  XFillRectangle(screen.disp,
                 screen.pix,
                 screen.gc,
                 x*screen.size,y*screen.size,
                 screen.size,screen.size);
}

void spreadUpdateState(void)
{
  int x,y;

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        (spreadUpdateCellState)(&Cell[pos(x,y)]);
      }

}

void spreadUpdateCellState(CELL *celluar)
{
  int neighbour;

  celluar->isUpdated = TRUE;
  neighbour=spreadAliveNeighbour(celluar);

  switch(celluar->state)
    {
     case SP_VACUM_STATE:
      if(neighbour != 0)
        celluar->newstate = SP_INFO_STATE;
/* threshold version
      if(neighbour > 0 && neighbour <= 4)
        celluar->newstate = SP_INFO_STATE;
      else if(neighbour >4)
        celluar->newstate = SP_GOAL_STATE;
 */
      break;
     case SP_WAIT1_STATE:
      celluar->newstate = SP_VACUM_STATE;
      break;
     case SP_INFO_STATE:
      celluar->newstate = SP_WAIT1_STATE;
      break;
     case SP_GOAL_STATE:
     case SP_CONTROL_STATE:
     case SP_BROKEN_STATE:
      celluar->newstate = celluar->state;
      break;
    }
  celluar->color=celluar->newstate;
}  

void spreadSetState(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        spreadSetCellState(&Cell[pos(x,y)]);
      }
  exposeField(screen.field,NULL,NULL);
}

void spreadSetCellState(CELL *celluar)
{
  celluar->isUpdated=FALSE;

  if(celluar->state==celluar->newstate )
    return;
  celluar->state=celluar->newstate;
  spreadDrawCell(celluar->x,celluar->y,celluar->color);
}
