#include "2DRoad.h"
  
#include "globals.h"
  
#include "check.xbm"
  
Pixmap check;
extern long tmpcount;

void carDrawCell(Drawable drawable,float x,float y,int color,int status,int size)
{
  XPoint point[4];
  int point_num;
  long count;
  char strings[100];
  int length;
  int radius;
  INITIAL *tmp;
  
  XSetForeground(XtDisplay(screen.field),screen.gc
                 ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));
  XFillRectangle(XtDisplay(screen.field),drawable,screen.gc,
                 x   *size, y   *size,
                 size,size);
  
  switch(status)
  {
  case CAR_UP:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CAR_UP_COLOR].pixel);
    point[0].x = (x+0.5)*size;
    point[0].y =  y     *size;
    point[1].x = (x+1.0)*size-1;
    point[1].y = (y+1.0)*size-1;
    point[2].x =  x     *size;
    point[2].y = (y+1.0)*size-1;
    point_num=3;
    XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                 ,point,point_num,Convex,CoordModeOrigin);
    break;
/*
   case CAR_DOWN:
    point[0].x = (x+0.5)*size;
    point[0].y = (y+1.0)*size-1;
    point[1].x =  x     *size;
    point[1].y =  y     *size;
    point[2].x = (x+1.0)*size-1;
    point[2].y =  y     *size;
    point_num=3;
    XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                 ,point,point_num,Convex,CoordModeOrigin);
    break;
 */
   case CAR_RIGHT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CAR_RIGHT_COLOR].pixel);
    point[0].x = (x+1.0)*size-1;
    point[0].y = (y+0.5)*size;
    point[1].x =  x     *size;
    point[1].y =  y     *size;
    point[2].x =  x     *size;
    point[2].y = (y+1.0)*size-1;
    point_num=3;
    XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                 ,point,point_num,Convex,CoordModeOrigin);
    break;
/*
   case CAR_LEFT:
    point[0].x =  x     *size;
    point[0].y = (y+0.5)*size;
    point[1].x = (x+1.0)*size-1;
    point[1].y =  y     *size;
    point[2].x = (x+1.0)*size-1;
    point[2].y = (y+1.0)*size-1;
    point_num=3;
    XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                 ,point,point_num,Convex,CoordModeOrigin);
    break;
 */
   case CAR_VACUM:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CAR_VACUM_COLOR].pixel);
    XFillRectangle(screen.disp,drawable,screen.gc,
                   (x+0.5)*size-1,(y+0.5)*size-1,
                   2,2);
    break;
  default:
    XFillRectangle(XtDisplay(screen.field),drawable,screen.gc,
                   x   *size, y   *size,
                   size,size);
    break;
  }
}

void carSetCursor(int state,int color,int mode)
  /*
    mode = 0      囲いを書かない
    other  囲いを書く
    */
{
  carDrawCell(XtWindow(state_display),0,0,color,state,CELL_SIZE);
  if(mode!=0)
  {
    XDrawRectangle(screen.disp,XtWindow(state_display),screen.gc
                   ,0,0,CELL_SIZE-1,CELL_SIZE-1);
  }
}

void
  carSetButtonState(CELL *celluar,unsigned long state)
{
  extern void allocLoad(CELL *,int);
  extern void deleteLOAD(CELL *);

  celluar->state=screen.n_st;
  
  celluar->color=1;
  carDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,
                   celluar->state,screen.size);
}

/* FIELDをボタンクリックした時の動作 (Button) */
void carButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);
  
  switch(event->xbutton.button)
  {
  case 1:
    carSetButtonState(&Cell[position],screen.n_st);
    XCopyArea(screen.disp,screen.pix,XtWindow(screen.field),screen.gc,
              x*screen.size,y*screen.size,
              (x+1)*screen.size,(y+1)*screen.size,
              x*screen.size,y*screen.size);
    break;
  case 2:
    if(screen.sp==pos(screen.x,screen.y))
      {
        screen.sp=position;
        carSetCursor(screen.n_st,1,1);
      }
    else
      {
        for(x=MIN(pos_x(screen.sp),pos_x(position))
            ;x<=MAX(pos_x(screen.sp),pos_x(position));x++)
          for(y=MIN(pos_y(screen.sp),pos_y(position))
              ;y<=MAX(pos_y(screen.sp),pos_y(position));y++)
            {
              carSetButtonState(&Cell[pos(x,y)],screen.n_st);
            }
        exposeField(screen.field,NULL,NULL);
        screen.sp=pos(screen.x,screen.y);
        carSetCursor(screen.n_st,1,0);
      }
    break;
  case 3:
    switch(screen.n_st)
    {
    case CAR_VACUM:
      screen.n_st = CAR_UP;
      break;
    case CAR_UP:
      screen.n_st = CAR_RIGHT;
      break;
    case CAR_RIGHT:
      screen.n_st = CAR_VACUM;
      break;
    default:
      screen.n_st = CAR_VACUM;
      break;
    }
    carSetCursor(screen.n_st,1,0);
    screen.sp=pos(screen.x,screen.y);
    break;
  }
}

/* セルの再描画 (Refresh) */
void carRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      carDrawCell(screen.pix,
                  x,y,Cell[pos(x,y)].color,
                  Cell[pos(x,y)].state,screen.size);
    }
  exposeField(screen.field,NULL,NULL);
}
