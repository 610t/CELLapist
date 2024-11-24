#include "Rho.h"

#include "globals.h"

#define rhoCheckRegion(x,y,dx,dy) (((x)+(dx)>=0 && (x)+(dx)<screen.x)&&((y)+(dy)>=0 && (y)+(dy)<screen.y))

/* Private関数の定義 */
void rhoSetState(void);
void rhoSetCellState(CELL *);
int rhoGetState(int,int,int,int);
unsigned long rhoNeighbourState(CELL *,int,int);
int rhoCheckANDState(int,int,int,int,int,int);
/*
int rhoCheckRegion(int,int,int,int);
 */
int rhoRealMove(int,int,int,int);

/* rhoRule*.c */
/*
void rhoUpdateCellState4(CELL *);
void rhoUpdateCellState8(CELL *);
 */
void rhoUpdateCellStateGA(CELL *);

#ifdef __CELLapist__
extern void rhoSetCursor(int,int,int);
extern void rhoDrawCell(Drawable,float,float,int,int,int);
#endif /* __CELLapist__ */

/*
  公開されている関数
 */

/* セルの初期化 (New) */
void 
  rhoNew(int init_f)
{
  int x,y,position;
  
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
      Cell[position].state            = RHO_WHITE;
#ifdef __CELLapist__
      Cell[position].color            = RHO_WHITE_COLOR;
      rhoDrawCell(screen.pix,
                  x,y,Cell[position].color,Cell[position].state
                  ,screen.size);
#endif /* __CELLapist__ */
      Cell[position].newstate         = Cell[position].state;
    }
#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
  rhoSetCursor(RHO_WHITE,RHO_WHITE_COLOR,0);
  screen.n_st=RHO_WHITE;
  screen.sp=pos(screen.x,screen.y);
#endif /* __CELLapist__ */
}

/* セル状態の更新 (Step) */
#ifdef __CELLapist__
/*
void rhoStep4(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (rhoUpdateCellState4)(&Cell[pos(x,y)]);
      }
  
  rhoSetState();
}

void rhoStep8(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (rhoUpdateCellState8)(&Cell[pos(x,y)]);
      }
  
  rhoSetState();
}
 */
#endif /* ! __CELLapist__ */
void rhoStepGA(void)
{
  int x,y;

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (rhoUpdateCellStateGA)(&Cell[pos(x,y)]);
      }

  rhoSetState();

/*
  fprintf(stderr,"[Epoch %d]\n",screen.epoch);
  for(y=0;y<screen.y;y++)
  {
    for(x=0;x<screen.x;x++)
    {
      if(Cell[pos(x,y)].state==RHO_BLACK)
        fprintf(stderr,"X");
      else
        fprintf(stderr,"O");
    }
    fprintf(stderr,"\n"); 
  }
 */
}

/* ランダムに初期化 (Random) */
void
  putABlack()
{
  int x,y,position;

#ifdef __DEBUG__
  for(x=0;x<screen.x;x++)
  {
    for(y=0;y<screen.y;y++)
      if( Cell[pos(x,y)].state == RHO_WHITE )
        fprintf(stderr,"O");
      else if( Cell[pos(x,y)].state == RHO_BLACK )
        fprintf(stderr,"X");
      else
        fprintf(stderr,"?");
    fprintf(stderr,"\n");
  }
#endif /* __DEBUG__ */
  do
  {
    position = rand()%(screen.x*screen.y);
  } while( Cell[position].state != RHO_WHITE );
  
  Cell[position].isUpdated = FALSE;
  Cell[position].state = RHO_BLACK;
  Cell[position].newstate = RHO_BLACK;
#ifdef __CELLapist__
  Cell[position].color = RHO_BLACK_COLOR;
#endif /* __CELLapist */
}

#ifdef __CELLapist__
void 
  rhoRandom(Widget w,int *dense,caddr_t call_data)
#endif /* __CELLapist */
#ifdef __GA__
void 
  rhoRandom(int dense,int mode)
#endif /* __GA__ */
{
  int x,y,s,d;
  int pos;
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
    rhoNew(0);
    for(d=0;d<dense * (screen.x*screen.y)/100;d++)
    {
      putABlack();
    }
    break;
  case 1:
    rhoNew(0);
    for(pos=0;pos<dense * (screen.x*screen.y)/100;pos++)
    {
      Cell[pos].isUpdated = FALSE;
      Cell[pos].state = RHO_BLACK;
      Cell[pos].newstate = RHO_BLACK;
#ifdef __CELLapist__
      Cell[pos].color = RHO_BLACK_COLOR;
#endif /* __CELLapist */
    }
    break;
  default:
    break;
  }
  screen.epoch=0;

#ifdef __CELLapist__
  rhoRefresh();
  showEpoch();
#endif /* __CELLapist */
}

/*
  Private関数
 */
int rhoGetState(int x,int y,int dx,int dy)
{
  int real_x,real_y;
  
  real_x = x+dx;
  if( x+dx < 0 )
    real_x += screen.x;
  else if ( x+dx >= screen.x )
    real_x -= screen.x;
  
  real_y = y+dy;
  if( y+dy < 0 )
    real_y += screen.y;
  else if ( y+dy >= screen.y )
    real_y -= screen.y;
  
  return(Cell[pos(real_x,real_y)].state);
}
/* when flag == TRUE use GA mask */
unsigned long rhoNeighbourState(CELL *celluar,int neighbour,int flag)
{
  int x,y,state=0;
  
  x=celluar->x; y=celluar->y;
  
  state |= rhoCheckANDState(x,y, 0,-1,RHO_UP   ,flag);
  state |= rhoCheckANDState(x,y, 0,+1,RHO_DOWN ,flag);
  state |= rhoCheckANDState(x,y,-1, 0,RHO_LEFT ,flag);
  state |= rhoCheckANDState(x,y,+1, 0,RHO_RIGHT,flag);
  
  if(neighbour==8)
  {
    state |= rhoCheckANDState(x,y,+1,-1,RHO_UP_RIGHT  ,flag);
    state |= rhoCheckANDState(x,y,-1,-1,RHO_UP_LEFT   ,flag);
    state |= rhoCheckANDState(x,y,+1,+1,RHO_DOWN_RIGHT,flag);
    state |= rhoCheckANDState(x,y,-1,+1,RHO_DOWN_LEFT ,flag);
  }
  return(state);
}


int rhoCheckANDState(int x,int y,int dx,int dy,int direction,int flag)
{
  unsigned long state;
  int position;
  extern unsigned long signal_mask;

  position=pos(x+dx,y+dy);
  
  if( rhoGetState(x,y,dx,dy) == RHO_WHITE )
  {
    return(direction);
  }
  else
    return(0);
}

void rhoSetState(void)
{
  int x,y;
  unsigned long position;

  for(y=0;y<screen.y;y++)
  {
    for(x=0;x<screen.x;x++)
    {
      position = pos(x,y);
      rhoSetCellState(&Cell[position]);
    }
#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
#endif /* __CELLapist__ */
  }
}

void rhoSetCellState(CELL *celluar)
{
  celluar->isUpdated = FALSE;
  
  if( celluar->state == celluar->newstate )
  {
    celluar->newstate=RHO_WHITE;
    return;
  }

  celluar->state=celluar->newstate;
#ifdef __CELLapist__
  rhoDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,
                   celluar->state,screen.size);
#endif /* __CELLapist__ */
  celluar->newstate=RHO_WHITE;
}

void rhoDelete()
{
}

