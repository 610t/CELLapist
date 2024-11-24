#include "Wolfram.h"
  
#include "globals.h"
  
  int W_Rule[32]; /* 32 means pow(2,2*WOLFRAM_NEIGHBOUR+1) */

/* Private関数のプロトタイプ宣言 */
static void wolframUpdateState(void);
static void wolframUpdateCellState(CELL *);
static void wolframSetState(void);
static void wolframSetCellState(CELL *);
static void wolframDrawCell(int,int,int);
void wolframRealRandom(int,int,int);
static int wolframAliveNeighbour(CELL *);
extern long wolframRuleSelection(Widget,caddr_t,caddr_t);
void wolframSetRule(long);

/*
  公開されている関数
  */
/* FIELDをボタンクリックした時の動作 (Button) */
void wolframButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);
  
  Cell[position].state = (0 == Cell[position].state);
  if(Cell[position].color==0)
    Cell[position].color = 1;
  else
    Cell[position].color = 0;
  
  wolframDrawCell(x,y,Cell[position].color);
  XCopyArea(screen.disp,screen.pix,
            XtWindow(screen.field),
            screen.gc,
            x*screen.size,y*screen.size,
            (x+1)*screen.size,(y+1)*screen.size,
            x*screen.size,y*screen.size);
}

/* destoractor (Delete) */
void wolframDelete()
{
  return;
}

/* セルの初期化 (New) */
void wolframNew(int init_f)
{
  int x,y,position;
  int density;
  
  screen.epoch=0;
  showEpoch();
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      position=pos(x,y);
      Cell[position].x                = x;
      Cell[position].y                = y;
      Cell[position].isUpdated        = FALSE;
      if(init_f)
      {
        Cell[position].state    = VACUM_STATE;
        Cell[position].color            = 0;
      }
      else
      {
        if( Cell[position].state != 0 )
          Cell[position].color = 1;
        else
          Cell[position].color = 0;
      }
      Cell[position].newstate = Cell[position].state;
      wolframDrawCell(x,y,Cell[position].color);
    }
  exposeField(screen.field,NULL,NULL);

  density=50;
  wolframRealRandom(density,0,0);
  
  wolframRuleSelection(screen.toplevel,NULL,NULL);
}

/* セル状態の更新 (Step) */

void wolframStep(void)
{
  if(screen.epoch >= screen.y-1) screen.epoch=0;
  
  wolframUpdateState();
  wolframSetState();
}

/* セルの再描画 (Refresh) */
void wolframRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      wolframDrawCell(x,y,Cell[pos(x,y)].color);
    }
  exposeField(screen.field,NULL,NULL);
}

/* ランダムに初期化 (Random) */
void wolframRandom(Widget w,int *dense,caddr_t call_data)
{
  int s;
  extern Widget StateDistButton[];
  extern Widget StateTop;
  extern int dense,width;
  
/*
  XtDestroyWidget(StateTop);
 */
  s = *(int *)XawToggleGetCurrent(StateDistButton[1]);

  wolframRealRandom(dense,s,width);

}

void
  wolframRealRandom(int dense,int s,int width)
{
  int x,y;
  
  float tau,radius;

  y=0;
  switch(s)
  {
  case 0:
    for(x=0;x<screen.x;x++)
    {
      if(rand()%100>=dense)
      {
        Cell[pos(x,y)].state = 0;
        Cell[pos(x,y)].newstate = 0;
        Cell[pos(x,y)].color = 0;
      }
      else
      {
        Cell[pos(x,y)].state = 1;
        Cell[pos(x,y)].newstate = 1;
        Cell[pos(x,y)].color = 1;
      }
    }
    break;
  case 1:
    tau=-2.0*(width/100.0)*screen.x/2.0;
    for(x=0;x<screen.x;x++)
    {
      radius=sqrt((double)( (screen.x/2.0-x)*(screen.x/2.0-x)) );
      if((rand()%100)*exp(radius/tau)>=100-dense)
      {
        Cell[pos(x,y)].state = ALIVE_STATE;
        Cell[pos(x,y)].newstate = 1;
        Cell[pos(x,y)].color =1;
      }
      else
      {
        Cell[pos(x,y)].state = VACUM_STATE;
        Cell[pos(x,y)].newstate = 0;
        Cell[pos(x,y)].color = 0;
      }
    }
    break;
  case 2:
    tau=(width/100.0)*MIN(screen.x,screen.y)/2.0;
    for(x=0;x<screen.x;x++)
    {
      radius=sqrt((double)( (screen.x/2.0-x)*(screen.x/2.0-x) ));
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
static int 
  wolframAliveNeighbour(CELL *celluar)
{
  int num=0,x,y;
  int i;
  
  x=celluar->x; y=celluar->y;
  
  if(y==0) return 1;
  
  for(i=x-2;i<=x+2;i++)
  {
    num <<= 1;
    if(i<0)
      num += Cell[pos(i+screen.x,y-1)].state;
    else if(i>=screen.x)
      num += Cell[pos(i-screen.x,y-1)].state;
    else
      num += Cell[pos(i         ,y-1)].state;
  }
  return(num);
}

static void
  wolframDrawCell(int x,int y,int color)
{
  XSetForeground(screen.disp,screen.gc,screen.Color[color].pixel);
  XFillRectangle(screen.disp,
                 screen.pix,
                 screen.gc,
                 x*screen.size,y*screen.size,
                 screen.size,screen.size);
}

static void 
  wolframUpdateState(void)
{
  int x,y;
/*  
  for(x=0;x<screen.x;x++)
  {
    Cell[pos(x,0)].newstate = Cell[pos(x,0)].state;
  }
 */
/*
  for(y=1;y<screen.y;y++)
 */
  y=screen.epoch+1;
    for(x=0;x<screen.x;x++)
    {
      (wolframUpdateCellState)(&Cell[pos(x,y)]);
    }
  
}

static void 
  wolframUpdateCellState(CELL *celluar)
{
  int neighbour;
  
  celluar->isUpdated = TRUE;
  celluar->newstate = W_Rule[wolframAliveNeighbour(celluar)];
  if(celluar->newstate==ALIVE_STATE)
  {
    celluar->color = 1;
  }
  else
  {
    celluar->color = 0;
  }
}  

static void 
  wolframSetState(void)
{
  int x,y;
/*  
  for(y=0;y<screen.y;y++)
 */
  y=screen.epoch+1;
    for(x=0;x<screen.x;x++)
    {
      wolframSetCellState(&Cell[pos(x,y)]);
    }
  
  exposeField(screen.field,NULL,NULL);
}

static void
  wolframSetCellState(CELL *celluar)
{
  celluar->isUpdated=FALSE;
  
/*
  if(celluar->state == VACUM_STATE && celluar->state==celluar->newstate )
    return;
 */
  celluar->state=celluar->newstate;
  wolframDrawCell(celluar->x,celluar->y,celluar->color);
}

void
  wolframSetRule(long ruleNumber)
{
  long i,j;
  int bitcount(unsigned long,int);
  
  for(i=0;i<=(int)pow(2.0,2.0*WOLFRAM_NEIGHBOUR+1);i++)
    W_Rule[i]=0;

  for(i=0;i<2*WOLFRAM_NEIGHBOUR+1;i++)
  {
    if( ruleNumber & 1 )
      for(j=0;j<(int)pow(2.0,2.0*WOLFRAM_NEIGHBOUR+1);j++)
        if( bitcount(j,2*WOLFRAM_NEIGHBOUR+1) == i )
        {
          W_Rule[j] = 1;
        }
    ruleNumber >>= 1;
  }
}
