#include "Life.h"

#include "globals.h"

/* Private関数のプロトタイプ宣言 */
static void lifeUpdateState(void);
static void lifeUpdateCellState(CELL *);
static void lifeSetState(void);
static void lifeSetCellState(CELL *);
static void lifeDrawCell(int,int,int);
static int lifeAliveNeighbour(CELL *);
static void lifeCheckANDCount(int,int,int,int,int *);

/*
        公開されている関数
 */
/* FIELDをボタンクリックした時の動作 (Button) */
void lifeButton(Widget w,caddr_t client_data,XEvent *event)
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

  lifeDrawCell(x,y,Cell[position].color);
  XCopyArea(screen.disp,screen.pix,
            XtWindow(screen.field),
            screen.gc,
            x*screen.size,y*screen.size,
            (x+1)*screen.size,(y+1)*screen.size,
            x*screen.size,y*screen.size);
}

/* destoractor (Delete) */
void lifeDelete()
{
  return;
}

/* セルの初期化 (New) */
void lifeNew(int init_f)
{
  int x,y,position;
  extern void allocateColor(int);
  
  allocateColor(FALSE);

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
      lifeDrawCell(x,y,Cell[position].color);
    }
  exposeField(screen.field,NULL,NULL);
}

/* セル状態の更新 (Step) */

void lifeStep(void)
{
  lifeUpdateState();
  lifeSetState();
}

/* セルの再描画 (Refresh) */
void lifeRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        lifeDrawCell(x,y,Cell[pos(x,y)].color);
      }
  exposeField(screen.field,NULL,NULL);
}

/* ランダムに初期化 (Random) */
void lifeRandom(Widget w,int *dense,caddr_t call_data)
{
  int x,y,s;
  float tau,radius;
  extern Widget StateDistButton[];
  extern Widget StateTop;
  extern int dense,width;

  s = *(int *)XawToggleGetCurrent(StateDistButton[1]);
  
  switch(s)
    {
        case 0:
      for(y=0;y<screen.y;y++)
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
      tau=-2.0*(width/100.0)*MIN(screen.x,screen.y)/2.0;
      for(y=0;y<screen.y;y++)
        for(x=0;x<screen.x;x++)
          {
            radius=sqrt((double)( (screen.x/2.0-x)*(screen.x/2.0-x)
                                 +(screen.y/2.0-y)*(screen.y/2.0-y)));
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
static int 
  lifeAliveNeighbour(CELL *celluar)
{
  int num=0,x,y;

  x=celluar->x; y=celluar->y;

  lifeCheckANDCount(x,y,-1, 0,&num);
  lifeCheckANDCount(x,y,-1,-1,&num);
  lifeCheckANDCount(x,y,-1,+1,&num);

  lifeCheckANDCount(x,y, 0,-1,&num);
  lifeCheckANDCount(x,y, 0,+1,&num);
  
  lifeCheckANDCount(x,y,+1, 0,&num);
  lifeCheckANDCount(x,y,+1,-1,&num);
  lifeCheckANDCount(x,y,+1,+1,&num);

  return(num);
}

static void 
  lifeCheckANDCount(int x,int y,int dx,int dy,int *num)
{
  int nowX,nowY;
  
  nowX=x+dx;
  nowY=y+dy;

  if(nowX>=0 && nowX<screen.x)
    if(nowY>=0 && nowY<screen.y)
      {
        if(Cell[pos(x,y)].state == ALIVE_STATE 
           && Cell[pos(nowX,nowY)].isUpdated == FALSE)
          (lifeUpdateCellState)(&Cell[pos(nowX,nowY)]);
        if(Cell[pos(nowX,nowY)].state==ALIVE_STATE)
          (*num)++;
      }
}

static void
  lifeDrawCell(int x,int y,int color)
{
  XSetForeground(screen.disp,screen.gc,screen.Color[color].pixel);
  XFillRectangle(screen.disp,
                 screen.pix,
                 screen.gc,
                 x*screen.size,y*screen.size,
                 screen.size,screen.size);
}

static void 
  lifeUpdateState(void)
{
  int x,y;

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        if(Cell[pos(x,y)].state==ALIVE_STATE
           && Cell[pos(x,y)].isUpdated==FALSE)
          (lifeUpdateCellState)(&Cell[pos(x,y)]);
      }

}

static void 
  lifeUpdateCellState(CELL *celluar)
{
  int neighbour;

  celluar->isUpdated = TRUE;
  neighbour=lifeAliveNeighbour(celluar);

  if(celluar->state==ALIVE_STATE  && (neighbour==2 || neighbour==3) )
    {
      celluar->newstate = ALIVE_STATE;
      if(celluar->color < screen.colormax - 1)
          (celluar->color)++;
    }
  else
    if(celluar->state==VACUM_STATE && neighbour==3  )
      {
        celluar->newstate = ALIVE_STATE;
        celluar->color = 1;
      }
    else
      {
        celluar->newstate = VACUM_STATE;
        celluar->color = 0;
      }
}  

static void 
  lifeSetState(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        lifeSetCellState(&Cell[pos(x,y)]);
      }
  exposeField(screen.field,NULL,NULL);
}

static void
  lifeSetCellState(CELL *celluar)
{
  celluar->isUpdated=FALSE;

  if(celluar->state == VACUM_STATE && celluar->state==celluar->newstate )
    return;
  celluar->state=celluar->newstate;
  lifeDrawCell(celluar->x,celluar->y,celluar->color);
}

