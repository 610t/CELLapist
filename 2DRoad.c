#include "2DRoad.h"

#include "globals.h"
/* #include "carLookup.h" */

/*
#define carNeighbour(x,y,dx,dy) {\
                                   int tmpx,tmpy;\
                                   tmpx = (x)+(dx);\
                                   if(tmpx<0) tmpx += screen.x;\
                                   else if(tmpx>=screen.x) tmpx -=screen.x;\
                                   tmpy = (y)+(dy);\
                                   if(tmpy<0) tmpy += screen.y;\
                                   else if(tmpy>=screen.y) tmpy -=screen.y;\
                                   pos(x,y);\
                                 }
 */
/* Private関数の定義 */
void carSetState(void);
void carUpdateCellState(CELL *);
void carSetCellState(CELL *);
int carCheckANDState(int,int,int,int);
int carRealMove(int,int,int,int);
int carNeighbour(int,int,int,int);

#ifdef __CELLapist__
extern void carSetCursor(int,int,int);
extern void carDrawCell(Drawable,float,float,int,int,int);
#endif /* __CELLapist__ */

long tmpcount;

/*
  公開されている関数
 */

/* destoractor (Delete) */
void 
  carDelete()
{
  return;
}

/* セルの初期化 (New) */
void
carAllocColor()
{
  Colormap cmap;

  cmap=DefaultColormap(screen.disp,DefaultScreen(screen.disp));

  screen.Color[CAR_VACUM_COLOR].red     = 0;
  screen.Color[CAR_VACUM_COLOR].blue    = 0;
  screen.Color[CAR_VACUM_COLOR].green   = 0;

  screen.Color[CAR_RIGHT_COLOR].red     = 65535;
  screen.Color[CAR_RIGHT_COLOR].blue    = 0;
  screen.Color[CAR_RIGHT_COLOR].green   = 0;

  screen.Color[CAR_UP_COLOR].red        = 0;
  screen.Color[CAR_UP_COLOR].blue       = 65535;
  screen.Color[CAR_UP_COLOR].green      = 0;

  XStoreColors(screen.disp,cmap,screen.Color,screen.colormax);
}

void 
  carNew(int init_f)
{
  int x,y,position;

  carAllocColor();
  
  screen.epoch=0;
#ifdef __CELLapist__
  showEpoch();
#endif /* __CELLapist__ */
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      position=pos(x,y);
      Cell[position].x                = x;
      Cell[position].y                = y;
      Cell[position].isUpdated        = FALSE;
/*
      allocLoad(&(Cell[position]),FALSE,screen.epoch);
      */
      if( init_f )
      {
        Cell[position].state            = CAR_VACUM;
#ifdef __CELLapist__
        Cell[position].color            = CAR_VACUM_COLOR;
#endif /* __CELLapist__ */
      }
#ifdef __CELLapist__
      else
      {
        if( Cell[position].state != CAR_VACUM )
          Cell[position].color = 1;
        else
          Cell[position].color = CAR_VACUM_COLOR;
      }
      carDrawCell(screen.pix,
                       x,y,Cell[position].color,Cell[position].state
                       ,screen.size);
#endif /* __CELLapist__ */
      Cell[position].newstate         = Cell[position].state;
    }
#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
  carSetCursor(CAR_VACUM,CAR_VACUM_COLOR,0);
  screen.n_st=CAR_VACUM;
  screen.sp=pos(screen.x,screen.y);
#endif /* __CELLapist__ */
}

/* セル状態の更新 (Step) */
void carStep(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (carUpdateCellState)(&Cell[pos(x,y)]);
      }
  
  carSetState();
}

/* ランダムに初期化 (Random) */
#ifdef __CELLapist__
void 
  carRandom(Widget w,int *dense,caddr_t call_data)
#endif /* __CELLapist */
#ifdef __GA__
void 
  carRandom(int dense,int mode)
#endif /* __GA__ */
{
  int x,y,s;
  unsigned long position;
#ifdef __CELLapist__
  int mode;

  extern Widget StateDistButton[];
  extern Widget StateTop;
  extern int dense,width;

/*
  XtDestroyWidget(StateTop);
 */

  mode = *(int *)XawToggleGetCurrent(StateDistButton[1]);
#endif /* __CELLapist__ */
  
  switch(mode)
  {
  case 0:
    for(y=0;y<screen.y;y++)
      for(x=0;x<screen.x;x++)
      {
        position=pos(x,y);
        Cell[position].isUpdated = FALSE;
        if(rand()%100>=dense)
        {
          Cell[position].state
            = Cell[position].newstate
              = CAR_VACUM;
/*
          allocLoad(&(Cell[position]),FALSE,screen.epoch);
          */
#ifdef __CELLapist__
          Cell[position].color = CAR_VACUM_COLOR;
#endif /* __CELLapist */
        }
        else
        {
          if( ((rand()%10001)/10000.0) >0.5)
          {
            Cell[position].state
              = Cell[position].newstate
                = CAR_UP;
#ifdef __CELLapist__
          Cell[position].color  = CAR_UP_COLOR;
#endif /* __CELLapist */
          }
          else
          {
            Cell[position].state
              = Cell[position].newstate
                = CAR_RIGHT;
#ifdef __CELLapist__
          Cell[position].color  = CAR_UP_COLOR;
#endif /* __CELLapist */
          }
        }
      }
    break;
  case 1:
    break;
  default:
    break;
  }

  screen.epoch=0;

#ifdef __CELLapist__
  carRefresh();
  showEpoch();
#endif /* __CELLapist */
}

/*
  Private関数
 */

void carUpdateCellState(CELL *cellular)
{
  int x,y,state;
  
  x=cellular->x; y=cellular->y;
  
  cellular->newstate = cellular->state;

  switch(cellular->state)
    {
     case CAR_UP:
      if(screen.epoch%2==0)
        if(carCheckANDState(x,y, 0,-1)==CAR_VACUM)
          cellular->newstate = CAR_VACUM;
      break;
     case CAR_RIGHT:
      if(screen.epoch%2==1)
        if(carCheckANDState(x,y,+1, 0)==CAR_VACUM)
          cellular->newstate = CAR_VACUM;
      break;
     case CAR_VACUM:
      if((screen.epoch%2)==0)
        {
          if(carCheckANDState(x,y, 0,+1)==CAR_UP)
            cellular->newstate = CAR_UP;
        }
      else
        {
          if(carCheckANDState(x,y,-1, 0)==CAR_RIGHT)
            cellular->newstate = CAR_RIGHT;
        }
      
      break;
     default:
    }      
      
  return;
}


int carNeighbour(x,y,dx,dy)
{
  int tmpx,tmpy;

  tmpx = x+dx;

  if(tmpx<0)
    tmpx += screen.x;
  else if(tmpx>=screen.x)
    tmpx -= screen.x;

  tmpy = y+dy;
  if(tmpy<0)
    tmpy += screen.y;
  else if(tmpy>=screen.y)
    tmpy -= screen.y;

  return(pos(tmpx,tmpy));
}

int carCheckANDState(int x,int y,int dx,int dy)
{
  unsigned long state;
  int position;
  extern unsigned long signal_mask;

  position = carNeighbour(x,y,dx,dy);

  return(Cell[position].state);
}

void carSetState(void)
{
  int x,y;
  unsigned long position;

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        position = pos(x,y);
        if(Cell[position].state != Cell[position].newstate)
          {
            Cell[position].state = Cell[position].newstate;
            carDrawCell(screen.pix,
                        x,y,Cell[position].color,Cell[position].state
                        ,screen.size);
          }
      }  

#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
#endif /* __CELLapist__ */
}

