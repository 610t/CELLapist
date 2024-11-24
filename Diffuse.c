#include "Diffuse.h"

#include "globals.h"

/* Private関数の定義 */
void diffuseUpdateState(void);
void diffuseUpdateCellState(CELL *);
void diffuseSetState(void);
void diffuseSetCellState(CELL *);
void diffuseDrawCell(Drawable,int,int,int,int,int);
int diffuseAliveNeighbour(CELL *);
void diffuseCheckANDCount(int,int,int,int,int *);
int diffuseColor(int);

/*
        公開されている関数
 */
/* FIELDをボタンクリックした時の動作 (Button) */
void diffuseButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,xx,yy,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);
  
  switch(event->xbutton.button)
    {
        case 1:
      Cell[position].state=screen.n_st;
      Cell[position].newstate=screen.n_st;
      Cell[position].color=diffuseColor(screen.n_st);

      diffuseDrawCell(screen.pix,x,y
                      ,Cell[position].color,Cell[position].state,screen.size);
      XCopyArea(screen.disp,screen.pix,XtWindow(screen.field),screen.gc,
                x*screen.size,y*screen.size,
                (x+1)*screen.size,(y+1)*screen.size,
                x*screen.size,y*screen.size);
      break;
        case 2:
      if(screen.sp==pos(screen.x,screen.y))
         {
           screen.sp=position;
         }
         else
         {
           for(xx=MIN(pos_x(screen.sp),pos_x(position));
               xx<=MAX(pos_x(screen.sp),pos_x(position));
	       xx++)
             for(yy=MIN(pos_y(screen.sp),pos_y(position));
                 yy<=MAX(pos_y(screen.sp),pos_y(position));
		 yy++)
               {
                 Cell[pos(xx,yy)].state =screen.n_st;
                 Cell[pos(xx,yy)].newstate=screen.n_st;
                 Cell[pos(xx,yy)].color=diffuseColor(screen.n_st);
                 diffuseDrawCell(screen.pix,xx,yy,
                                 Cell[pos(xx,yy)].color,screen.n_st,screen.size);
               }
           exposeField(screen.field,NULL,NULL);
           screen.sp=pos(screen.x,screen.y);
         }
      break;
        case 3:
      switch(screen.n_st)
        {
         case DIFFUSE_COOL:
          screen.n_st = DIFFUSE_LOW;
          break;
         case DIFFUSE_HEAT:
          screen.n_st = DIFFUSE_COOL;
          break;
         case DIFFUSE_OBSTACLE:
          screen.n_st = DIFFUSE_HEAT;
          break;
         case DIFFUSE_LOW:
          screen.n_st = DIFFUSE_HIGH;
          break;
         default:
          screen.n_st = DIFFUSE_OBSTACLE;
          break;
        }
      diffuseDrawCell(XtWindow(state_display),0,0
                               ,diffuseColor(screen.n_st),screen.n_st,CELL_SIZE);
      screen.sp=pos(screen.x,screen.y);
      break;
    }
}

/* destoractor (Delete) */
void diffuseDelete()
{
  return;
}

/* セルの初期化 (New) */
void diffuseNew( int init_f )
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
      if( init_f )
      {
        Cell[position].state = DIFFUSE_LOW;
      }
      Cell[position].color            = diffuseColor(Cell[position].state);
      Cell[position].newstate         = Cell[position].state;
      diffuseDrawCell(screen.pix,x,y
                      ,diffuseColor(Cell[position].state),Cell[position].state
                      ,screen.size);
    }
  exposeField(screen.field,NULL,NULL);
  screen.n_st=0;
}

/* セル状態の更新 (Step) */

void diffuseStep(void)
{
  diffuseUpdateState();
  diffuseSetState();
}

/* セルの再描画 (Refresh) */
void diffuseRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        diffuseDrawCell(screen.pix,x,y
                        ,Cell[pos(x,y)].color,Cell[pos(x,y)].state,screen.size);
      }
  exposeField(screen.field,NULL,NULL);
}

/* ランダムに初期化 (Random) */
void diffuseRandom(Widget w,int *dense,caddr_t call_data)
{
  int x,y,s;
  float radius,tau;

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
                Cell[pos(x,y)].state = DIFFUSE_LOW;
                Cell[pos(x,y)].newstate = DIFFUSE_LOW;
                Cell[pos(x,y)].color = diffuseColor(DIFFUSE_LOW);
              }
            else
              {
                Cell[pos(x,y)].state = rand()%255+1;
                Cell[pos(x,y)].newstate = DIFFUSE_LOW;
                Cell[pos(x,y)].color 
                  = diffuseColor(Cell[pos(x,y)].state);
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
                Cell[pos(x,y)].state = rand()%255+1;
                Cell[pos(x,y)].newstate = DIFFUSE_LOW;
                Cell[pos(x,y)].color 
                  = diffuseColor(Cell[pos(x,y)].state);
              }
            else
              {
                Cell[pos(x,y)].state = DIFFUSE_LOW;
                Cell[pos(x,y)].newstate = DIFFUSE_LOW;
                Cell[pos(x,y)].color = diffuseColor(DIFFUSE_LOW);
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
                Cell[pos(x,y)].state = DIFFUSE_LOW;
                Cell[pos(x,y)].newstate = DIFFUSE_LOW;
                Cell[pos(x,y)].color = diffuseColor(DIFFUSE_LOW);
              }
            else
              {
                Cell[pos(x,y)].state = DIFFUSE_HIGH;
                Cell[pos(x,y)].newstate = DIFFUSE_LOW;
                Cell[pos(x,y)].color 
                  = diffuseColor(DIFFUSE_HIGH);
              }
          }
      break;
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
int diffuseAliveNeighbour(CELL *celluar)
{
  int num=0,x,y;

  x=celluar->x; y=celluar->y;

  diffuseCheckANDCount(x,y,-1, 0,&num);
  diffuseCheckANDCount(x,y,-1,-1,&num);
  diffuseCheckANDCount(x,y,-1,+1,&num);

  diffuseCheckANDCount(x,y, 0, 0,&num);
  diffuseCheckANDCount(x,y, 0,-1,&num);
  diffuseCheckANDCount(x,y, 0,+1,&num);
  
  diffuseCheckANDCount(x,y,+1, 0,&num);
  diffuseCheckANDCount(x,y,+1,-1,&num);
  diffuseCheckANDCount(x,y,+1,+1,&num);

  return(num);
}

void diffuseCheckANDCount(int x,int y,int dx,int dy,int *num)
{
  int nowX,nowY;
  
  nowX=x+dx;
  nowY=y+dy;

  if(nowX>=0 && nowX<screen.x)
    if(nowY>=0 && nowY<screen.y)
      {
        if(Cell[pos(x,y)].state != 0
           && Cell[pos(nowX,nowY)].isUpdated == FALSE)
          (diffuseUpdateCellState)(&Cell[pos(nowX,nowY)]);
        if(Cell[pos(nowX,nowY)].state!=DIFFUSE_OBSTACLE)
          (*num)+=Cell[pos(nowX,nowY)].state;
      }
}

void diffuseDrawCell(Drawable drawable,int x,int y,int color,int state,int size)
{
  if(state==DIFFUSE_OBSTACLE)
    {
      XSetForeground(screen.disp,screen.gc,screen.Color[0].pixel);
      XFillRectangle(screen.disp,drawable,screen.gc,x*size,y*size,size,size);
      XSetForeground(screen.disp,screen.gc,screen.Color[1].pixel);
      XDrawLine(screen.disp,drawable,screen.gc,
                 x     *size  , y     *size,
                (x+1.0)*size-1,(y+1.0)*size-1);
      XDrawLine(screen.disp,drawable,screen.gc,
                 x     *size  ,(y+1.0)*size-1,
                (x+1.0)*size-1, y     *size);
    }
  else
    {
      XSetForeground(screen.disp,screen.gc,screen.Color[color].pixel);
      XFillRectangle(screen.disp,drawable,
                     screen.gc,
                     x*size,y*size,size,size);
    }
}

void diffuseUpdateState(void)
{
  int x,y;

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        if(Cell[pos(x,y)].state!=0
           && Cell[pos(x,y)].isUpdated==FALSE)
          (diffuseUpdateCellState)(&Cell[pos(x,y)]);
      }

}

void diffuseUpdateCellState(CELL *celluar)
{
  int neighbour;

  celluar->isUpdated = TRUE;
  neighbour=diffuseAliveNeighbour(celluar);

  if(celluar->state != DIFFUSE_OBSTACLE 
     && celluar->state != DIFFUSE_HEAT
     && celluar->state != DIFFUSE_COOL)
    {
      celluar->newstate = neighbour / 9;
      if(celluar->newstate == DIFFUSE_COOL)
        celluar->newstate = DIFFUSE_LOW;
      celluar->color = diffuseColor(celluar->newstate);
    }
  else
    {
      celluar->newstate = celluar->state;
    }
}  

void diffuseSetState(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        diffuseSetCellState(&Cell[pos(x,y)]);
      }
  exposeField(screen.field,NULL,NULL);
}

void diffuseSetCellState(CELL *celluar)
{
  celluar->isUpdated=FALSE;

  if(celluar->state==celluar->newstate )
    return;
  celluar->state=celluar->newstate;
  diffuseDrawCell(screen.pix
                  ,celluar->x,celluar->y,celluar->color,celluar->state,screen.size);
}

int diffuseColor(int state)
{
  if(state==DIFFUSE_COOL)
    return(0);
  else if(state==DIFFUSE_HEAT)
    return(1);
  else
    return(screen.colormax-((state/2) * (screen.colormax-1)/(DIFFUSE_HEAT_NUM)+1));
}
