#include "Rho.h"
  
#include "globals.h"
  
Pixmap check;

void rhoDrawCell(Drawable drawable,float x,float y,int color,int status,int size)
{
  XPoint point[4];
  int point_num;
  long count;
  char strings[100];
  int length;
  int radius;
  INITIAL *tmp;
  
  switch(status)
  {
  case RHO_WHITE:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));
    XFillRectangle(screen.disp,drawable,screen.gc,
                   x*size,y*size,
                   size,size);
    break;
  case RHO_BLACK:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,BlackPixel(screen.disp,DefaultScreen(screen.disp)));
    XFillRectangle(screen.disp,drawable,screen.gc,
                   x*size,y*size,
                   size,size);
    break;
  default:
    break;
  }
}

void rhoSetCursor(int state,int color,int mode)
  /*
    mode = 0      囲いを書かない
    other  囲いを書く
    */
{
  rhoDrawCell(XtWindow(state_display),0,0,color,state,CELL_SIZE);
  if(mode!=0)
  {
    XDrawRectangle(screen.disp,XtWindow(state_display),screen.gc
                   ,0,0,CELL_SIZE-1,CELL_SIZE-1);
  }
}

void
  rhoSetButtonState(CELL *celluar,unsigned long state)
{
  extern void allocLoad(CELL *,int);
  extern void deleteLOAD(CELL *);

  celluar->state=screen.n_st;
  
  celluar->color=1;
  rhoDrawCell(screen.pix,
              celluar->x,celluar->y,celluar->color,
              celluar->state,screen.size);
}

/* FIELDをボタンクリックした時の動作 (Button) */
void rhoButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);
  
  switch(event->xbutton.button)
  {
  case 1:
    rhoSetButtonState(&Cell[position],screen.n_st);
    XCopyArea(screen.disp,screen.pix,XtWindow(screen.field),screen.gc,
              x*screen.size,y*screen.size,
              (x+1)*screen.size,(y+1)*screen.size,
              x*screen.size,y*screen.size);
    break;
  case 2:
    if(screen.sp==pos(screen.x,screen.y))
    {
      screen.sp=position;
      rhoSetCursor(screen.n_st,1,1);
    }
    else
    {
      for(x=MIN(pos_x(screen.sp),pos_x(position))
          ;x<=MAX(pos_x(screen.sp),pos_x(position));x++)
        for(y=MIN(pos_y(screen.sp),pos_y(position))
            ;y<=MAX(pos_y(screen.sp),pos_y(position));y++)
        {
          rhoSetButtonState(&Cell[pos(x,y)],screen.n_st);
        }
      exposeField(screen.field,NULL,NULL);
      screen.sp=pos(screen.x,screen.y);
      rhoSetCursor(screen.n_st,1,0);
    }
    break;
  case 3:
    switch(screen.n_st)
    {
    case RHO_WHITE:
      screen.n_st = RHO_BLACK;
      break;
    case RHO_BLACK:
      screen.n_st = RHO_WHITE;
      break;
    default:
      screen.n_st = RHO_WHITE;
      break;
    }
    rhoSetCursor(screen.n_st,1,0);
    screen.sp=pos(screen.x,screen.y);
    break;
  }
}

/* セルの再描画 (Refresh) */
void rhoRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      rhoDrawCell(screen.pix,
                  x,y,Cell[pos(x,y)].color,
                  Cell[pos(x,y)].state,screen.size);
    }
  exposeField(screen.field,NULL,NULL);
}
