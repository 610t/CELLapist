#include "Conveyor.h"
  
#include "globals.h"
  
#include "check.xbm"
  
Pixmap cursor_pix=(Pixmap)NULL;
Pixmap check;
extern long tmpcount;

void conveyorDrawCell(Drawable drawable,float x,float y,int color,int status,int size)
{
  XPoint point[4];
  int point_num;
  long count;
  char strings[100];
  int length;
  int radius;
  INITIAL *tmp;

  {
    XGCValues gcv;

    gcv.function=GXxor;
    XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);
  }
  
  XSetForeground(XtDisplay(screen.field),screen.gc
                 ,BlackPixel(screen.disp,DefaultScreen(screen.disp)));
  
  switch(status&~CONVEYOR_SENSOR)
  {
  case CONVEYOR_UP:
  case CONVEYOR_UP|CONVEYOR_RIGHT|CONVEYOR_LEFT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONVEYOR_UP_COLOR].pixel);
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
  case CONVEYOR_DOWN:
  case CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONVEYOR_DOWN_COLOR].pixel);
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
  case CONVEYOR_RIGHT:
  case CONVEYOR_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONVEYOR_RIGHT_COLOR].pixel);
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
  case CONVEYOR_LEFT:
  case CONVEYOR_LEFT|CONVEYOR_UP|CONVEYOR_DOWN:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONVEYOR_LEFT_COLOR].pixel);
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
  case CONVEYOR_UP|CONVEYOR_LEFT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONV_UP_LEFT_COLOR].pixel);
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
  case CONVEYOR_UP|CONVEYOR_RIGHT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONV_UP_RIGHT_COLOR].pixel);
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
  case CONVEYOR_DOWN|CONVEYOR_RIGHT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONV_DOWN_RIGHT_COLOR].pixel);
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
  case CONVEYOR_DOWN|CONVEYOR_LEFT:
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,screen.Color[CONV_DOWN_LEFT_COLOR].pixel);
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
  case CONVEYOR_UP|CONVEYOR_DOWN:
    XFillRectangle(screen.disp,drawable,screen.gc,
                   (x+0.5)*size-1,(y+0.5)*size-2,
                   2,4);
    break;
  case CONVEYOR_RIGHT|CONVEYOR_LEFT:
    XFillRectangle(screen.disp,drawable,screen.gc,
                   (x+0.5)*size-2,(y+0.5)*size-1,
                   4,2);
    break;
  case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
    XFillRectangle(screen.disp,drawable,screen.gc,
                   (x+0.5)*size-1,(y+0.5)*size-2,
                   2,4);
    XFillRectangle(screen.disp,drawable,screen.gc,
                   (x+0.5)*size-2,(y+0.5)*size-1,
                   4,2);
    break;
/*
   case CONVEYOR_CONTROL:
    XFillRectangle(XtDisplay(screen.field),drawable,screen.gc,
                   x   *size, y   *size,
                   size,size);
    break;
 */
  case CONVEYOR_BROKEN:
    XDrawLine(screen.disp,drawable,screen.gc,
              x     *size  , y     *size,
              (x+1.0)*size-1,(y+1.0)*size-1);
    XDrawLine(screen.disp,drawable,screen.gc,
              x     *size  ,(y+1.0)*size-1,
              (x+1.0)*size-1, y     *size);
    break;
  case CONVEYOR_VACUM:
    XFillRectangle(screen.disp,drawable,screen.gc,
                   (x+0.5)*size-1,(y+0.5)*size-1,
                   2,2);
    break;
  default:
    if( status & CONVEYOR_CONTROL )
      XFillRectangle(XtDisplay(screen.field),drawable,screen.gc,
                     x   *size, y   *size,
                     size,size);
    break;
  }
#if !defined(__LargeLoad__)
  if(( status & CONVEYOR_SENSOR ) != 0)
  {
    count=0;
    for(tmp=Cell[pos(x,y)].load->head;tmp!=NULL;tmp=tmp->next)
      count++;
/*     fprintf(stderr, "(%f,%f) -> %d\n",x,y,count);  */
/*
    if( st_pos != pos(x,y) )
      tmpcount+=count;
*/
/*  **** For Draw number of loads ****
    sprintf(strings,"%d",count);
    length=strlen(strings);
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));
    XDrawString(screen.disp,screen.pix,screen.gc
                ,x*size  ,(y+1)*size  ,strings,length);
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,BlackPixel(screen.disp,DefaultScreen(screen.disp)));
    XDrawString(screen.disp,screen.pix,screen.gc
                ,x*size+1,(y+1)*size-1,strings,length);
 */
/*  **** For Draw variable circle **** */
    radius = (int)((0.5*size*count-2)/(screen.x*screen.y))+2;

    check = XCreateBitmapFromData(screen.disp,screen.pix,
                                  check_bits,check_width,check_height);
    XSetStipple(screen.disp,screen.gc,check);
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));
    XFillArc(screen.disp,screen.pix,screen.gc,
             (x+0.5)*size-radius,(y+0.5)*size-radius,
             2*radius,2*radius,0,360*64);
    XSetForeground(XtDisplay(screen.field),screen.gc
                   ,BlackPixel(screen.disp,DefaultScreen(screen.disp)));
    XSetFillStyle(screen.disp,screen.gc,FillStippled);
    XFillArc(screen.disp,screen.pix,screen.gc,
             (x+0.5)*size-radius,(y+0.5)*size-radius,
             2*radius,2*radius,0,360*64);

    XSetFillStyle(screen.disp,screen.gc,FillSolid);
/* */
/*  **** For Draw recrangle ****
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
 */
  }
#endif /* !__LargeLoad__ */
  
  {
    XGCValues gcv;

    gcv.function=GXcopy;
    XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);
  }
}

void conveyorSetCursor(int state,int color,int mode)
  /*
    mode = 0      囲いを書かない
    other  囲いを書く
    */
{

  if(mode!=0)
  {
    XGCValues gcv;

    gcv.function=GXxor;
    XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);

    XDrawRectangle(screen.disp,XtWindow(state_display),screen.gc
                   ,0,0,CELL_SIZE-1,CELL_SIZE-1);

    gcv.function=GXcopy;
    XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);
  }
  else
    conveyorDrawCell(XtWindow(state_display),0,0,color,state,CELL_SIZE);
}

void
  conveyorSetButtonState(CELL *celluar,unsigned long state,XEvent *event)
{
#if !defined(__LargeLoad__)
  extern void allocLoad(CELL *,int);
  extern void deleteLOAD(CELL *);
#endif
#if defined(__LargeLoad__)
  extern void put_obj(double,double,double,double); /* in locate.c */
# if defined(__CELLapist__)
  extern void drawsquare(OBJECT); /* locate.c */
# endif /* __CELLapist__ */
#endif /* __LargeLoad__ */
  
  conveyorDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,
                   celluar->state,screen.size);
  switch(state)
  {
#if defined(__LargeLoad__)
   case CONVEYOR_CONTROL:
    target.x = celluar->x;
    target.y = celluar->y;
    celluar->state = screen.n_st;
    break;
#endif
   case CONVEYOR_SENSOR:
#if defined(__LargeLoad__)
    {
      static int button_cnt = 0;
      static double jusin_x,jusin_y;

      if(button_cnt == 0) {
          button_cnt = 1;

          jusin_x = (double)event->xbutton.x;
          jusin_y = (double)event->xbutton.y;
      } else {
          button_cnt=0;

          put_obj(jusin_x,jusin_y
                  ,(double)event->xbutton.x
                  ,(double)event->xbutton.y);
#  if defined(__CELLapist__)
          drawsquare(Obj[Obj_cnt-1]);
          exposeField(screen.field,NULL,NULL);
#  endif /* --CELLapist__ */
        }
    }
#else /* __LargeLoad__ */
    celluar->state|=screen.n_st;
    deleteLOAD( celluar );
    allocLoad( celluar,TRUE );
#endif /* !__LargeLoad__ */
    break;
  case CONVEYOR_BROKEN:
    celluar->isUpdated = CONVEYOR_BROKEN;
  default:
    celluar->state=screen.n_st;
    break;
  }
  
  celluar->color=1;
  conveyorDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,
                   celluar->state,screen.size);
}

/* FIELDをボタンクリックした時の動作 (Button) */
void conveyorButton(Widget w,caddr_t client_data,XEvent *event)
{
  int x,y,position;
  
  x=(int)(event->xbutton.x/screen.size);
  y=(int)(event->xbutton.y/screen.size);
  position=pos(x,y);
  
  switch(event->xbutton.button)
  {
  case 1:
    conveyorSetButtonState(&Cell[position],screen.n_st,event);
    XCopyArea(screen.disp,screen.pix,XtWindow(screen.field),screen.gc,
              x*screen.size,y*screen.size,
              (x+1)*screen.size,(y+1)*screen.size,
              x*screen.size,y*screen.size);
    break;
  case 2:
    if(screen.sp==pos(screen.x,screen.y))
    {
      screen.sp=position;
      conveyorSetCursor(screen.n_st,1,1);
    }
    else
    {
      for(x=MIN(pos_x(screen.sp),pos_x(position))
          ;x<=MAX(pos_x(screen.sp),pos_x(position));x++)
        for(y=MIN(pos_y(screen.sp),pos_y(position))
            ;y<=MAX(pos_y(screen.sp),pos_y(position));y++)
          {
            conveyorSetButtonState(&Cell[pos(x,y)],screen.n_st,event);
          }
      exposeField(screen.field,NULL,NULL);
      screen.sp=pos(screen.x,screen.y);
      conveyorSetCursor(screen.n_st,1,1);
    }
    break;
  case 3:
    conveyorDrawCell(XtWindow(state_display),0,0,1,screen.n_st,CELL_SIZE);

    switch(screen.n_st)
    {
    case CONVEYOR_VACUM:
      screen.n_st = CONVEYOR_BROKEN;
      break;
    case CONVEYOR_CONTROL:
      screen.n_st = CONVEYOR_SENSOR;
      break;
    case CONVEYOR_SENSOR:
      screen.n_st = CONVEYOR_VACUM;
      break;
    default:
      screen.n_st = CONVEYOR_CONTROL;
      break;
    }
    conveyorSetCursor(screen.n_st,1,0);
    screen.sp=pos(screen.x,screen.y);
    break;
  }
}

/* セルの再描画 (Refresh) */
void conveyorRefresh()
{
  extern void drawsquare(OBJECT);
  int x,y,n;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      conveyorDrawCell(screen.pix,
                       x,y,Cell[pos(x,y)].color,
                       Cell[pos(x,y)].state,screen.size);

  for(n=0;n<Obj_cnt;n++)
    drawsquare(Obj[n]);

  exposeField(screen.field,NULL,NULL);
}
