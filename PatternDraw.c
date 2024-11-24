#include "Pattern.h"

#include "globals.h"

#include "check.xbm"

Pixmap check;

void patternDrawCell(Drawable drawable,float x,float y,int color,int status,int size)
{
  XPoint point[4];
  int point_num;
  
  XSetForeground(XtDisplay(screen.field),screen.gc
                 ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));
  XFillRectangle(XtDisplay(screen.field),drawable,screen.gc,
                 x   *size, y   *size,
                 size,size);
  XSetForeground(XtDisplay(screen.field),screen.gc
                 ,BlackPixel(screen.disp,DefaultScreen(screen.disp)));

  switch(status)
    {
        case PATTERN_UP:
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
        case PATTERN_DOWN:
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
        case PATTERN_RIGHT:
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
        case PATTERN_LEFT:
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
        case PATTERN_UP|PATTERN_LEFT:
      point[0].x =  x     *size;
      point[0].y =  y     *size;
      point[1].x = (x+0.5)*size;
      point[1].y = (y+1.0)*size-1;
      point[2].x = (x+1.0)*size-1;
      point[2].y = (y+0.5)*size;
      point_num=3;
      XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                   ,point,point_num,Convex,CoordModeOrigin);
      break;
        case PATTERN_UP|PATTERN_RIGHT:
      point[0].x = (x+1.0)*size-1;
      point[0].y =  y     *size;
      point[1].x =  x     *size;
      point[1].y = (y+0.5)*size;
      point[2].x = (x+0.5)*size-1;
      point[2].y = (y+1.0)*size-1;
      point_num=3;
      XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                   ,point,point_num,Convex,CoordModeOrigin);
      break;
        case PATTERN_DOWN|PATTERN_RIGHT:
      point[0].x = (x+1.0)*size-1;
      point[0].y = (y+1.0)*size-1;
      point[1].x =  x     *size;
      point[1].y = (y+0.5)*size;
      point[2].x = (x+0.5)*size;
      point[2].y =  y     *size;
      point_num=3;
      XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                   ,point,point_num,Convex,CoordModeOrigin);
      break;
        case PATTERN_DOWN|PATTERN_LEFT:
      point[0].x =  x     *size;
      point[0].y = (y+1.0)*size-1;
      point[1].x = (x+0.5)*size;
      point[1].y =  y     *size;
      point[2].x = (x+1.0)*size-1;
      point[2].y = (y+0.5)*size;
      point_num=3;
      XFillPolygon(XtDisplay(screen.field),drawable,screen.gc
                   ,point,point_num,Convex,CoordModeOrigin);
      break;
        case PATTERN_CONTROL:
      XFillRectangle(XtDisplay(screen.field),drawable,screen.gc,
                      x   *size, y   *size,
                     size,size);
      break;
        case PATTERN_VACUM:
      XFillRectangle(screen.disp,drawable,screen.gc,
                     (x+0.5)*size-1,(y+0.5)*size-1,
                     2,2);
      break;
        case PATTERN_BROKEN:
      XDrawLine(screen.disp,drawable,screen.gc,
                 x     *size  , y     *size,
                (x+1.0)*size-1,(y+1.0)*size-1);
      XDrawLine(screen.disp,drawable,screen.gc,
                 x     *size  ,(y+1.0)*size-1,
                (x+1.0)*size-1, y     *size);
      break;
    }

  if(status & PATTERN_SENSOR)
    {
      check = XCreateBitmapFromData(screen.disp,screen.pix,
                                    check_bits,check_width,check_height);
      XSetStipple(screen.disp,screen.gc,check);
      XSetFillStyle(screen.disp,screen.gc,FillStippled);

      point[0].x = (x+0.5) *size;
      point[0].y =  y      *size;
      point[1].x = (x+1.0) *size;
      point[1].y = (y+0.5) *size;
      point[2].x = (x+0.5) *size;
      point[2].y = (y+1.0) *size;
      point[3].x =  x      *size;
      point[3].y = (y+0.5) *size;
      point_num=4;
      XFillPolygon(screen.disp,drawable,screen.gc
                   ,point,point_num,Convex,CoordModeOrigin);
      XSetFillStyle(screen.disp,screen.gc,FillSolid);
    }
}

void patternSetCursor(int state,int color,int mode)
/*
  mode = 0      囲いを書かない
         other  囲いを書く
*/
{
  patternDrawCell(XtWindow(state_display),0,0,color,state,CELL_SIZE);
  if(mode!=0)
    {
      XDrawRectangle(screen.disp,XtWindow(state_display),screen.gc
                     ,0,0,CELL_SIZE-1,CELL_SIZE-1);
    }
}

/* FIELDをボタンクリックした時の動作 (Button) */
void patternButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);

  switch(event->xbutton.button)
    {
        case 1:
      if(screen.n_st!=PATTERN_SENSOR)
        Cell[position].state=screen.n_st;
      else
        Cell[position].state|=screen.n_st;

      Cell[position].color=1;
      patternDrawCell(screen.pix,
                       x,y,Cell[position].color,Cell[position].state,screen.size);
      XCopyArea(screen.disp,screen.pix,XtWindow(screen.field),screen.gc,
                x*screen.size,y*screen.size,
                (x+1)*screen.size,(y+1)*screen.size,
                x*screen.size,y*screen.size);
      break;
        case 2:
      if(screen.sp==pos(screen.x,screen.y))
         {
           screen.sp=position;
           patternSetCursor(screen.n_st,1,1);
         }
         else
         {
           for(x=MIN(pos_x(screen.sp),pos_x(position));
               x<=MAX(pos_x(screen.sp),pos_x(position));
	       x++)
             for(y=MIN(pos_y(screen.sp),pos_y(position));
                 y<=MAX(pos_y(screen.sp),pos_y(position));
		 y++)
               {
                 if(screen.n_st!=PATTERN_SENSOR)
                   Cell[pos(x,y)].state=screen.n_st;
                 else
                   Cell[pos(x,y)].state|=screen.n_st;
                 Cell[pos(x,y)].color=1;
                 patternDrawCell(screen.pix,x,y,
                                  Cell[pos(x,y)].color,Cell[pos(x,y)].state,screen.size);
               }
           exposeField(screen.field,NULL,NULL);
           screen.sp=pos(screen.x,screen.y);
           patternSetCursor(screen.n_st,1,0);
         }
      break;
        case 3:
      switch(screen.n_st)
        {
            case PATTERN_VACUM:
          screen.n_st = PATTERN_UP;
          break;
            case PATTERN_UP:
          screen.n_st = PATTERN_DOWN;
          break;
            case PATTERN_DOWN:
          screen.n_st = PATTERN_RIGHT;
          break;
            case PATTERN_RIGHT:
          screen.n_st = PATTERN_LEFT;
          break;
            case PATTERN_LEFT:
          screen.n_st = PATTERN_SENSOR;
          break;
            case PATTERN_SENSOR:
          screen.n_st = PATTERN_CONTROL;
          break;
            default:
          screen.n_st = PATTERN_VACUM;
          break;
        }
      patternSetCursor(screen.n_st,1,0);
      screen.sp=pos(screen.x,screen.y);
      break;
    }
}

/* セルの再描画 (Refresh) */
void patternRefresh()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        patternDrawCell(screen.pix,
                         x,y,Cell[pos(x,y)].color,Cell[pos(x,y)].state,screen.size);
      }
  exposeField(screen.field,NULL,NULL);
}
