#ifdef __LargeLoad__
#include <math.h>
#ifdef __CELLapist__
# include "X_include.h"
#endif /* __CELLapist__ */
#include "constant.h"
#include "globals.h"
#include "macros.h"
#include "largeload.h"

#ifdef __CELLapist__
enum{LINE,RECT};

void DrawLargeLoad(OBJECT Obj,int mode)
{
  XPoint point[10];
  int point_num;

  point[0].x = (int)(Obj.pixel[1].x * screen.size);
  point[0].y = (int)(Obj.pixel[1].y * screen.size);
  point[1].x = (int)(Obj.pixel[2].x * screen.size);
  point[1].y = (int)(Obj.pixel[2].y * screen.size);
  point[2].x = (int)(Obj.pixel[3].x * screen.size);
  point[2].y = (int)(Obj.pixel[3].y * screen.size);
  point[3].x = (int)(Obj.pixel[4].x * screen.size);
  point[3].y = (int)(Obj.pixel[4].y * screen.size);

  point_num=4;

  if(mode == LINE)
  {
    /* Set cross line */
    point[4].x = (int)(Obj.pixel[2].x * screen.size);
    point[4].y = (int)(Obj.pixel[2].y * screen.size);
    point[5].x = (int)(Obj.pixel[3].x * screen.size);
    point[5].y = (int)(Obj.pixel[3].y * screen.size);
    point[6].x = (int)(Obj.pixel[1].x * screen.size);
    point[6].y = (int)(Obj.pixel[1].y * screen.size);
    point[7].x = (int)(Obj.pixel[4].x * screen.size);
    point[7].y = (int)(Obj.pixel[4].y * screen.size);
    point_num = 8;
    
    XDrawLines(screen.disp, screen.pix, screen.gc,
               point,point_num,CoordModeOrigin);
  }
  else if(mode == RECT)
  {
    XFillPolygon(screen.disp, screen.pix, screen.gc,
                 point,point_num,Convex,CoordModeOrigin);
  }
}

void drawsquare(OBJECT Obj)
{
  XGCValues gcv;

  gcv.function=GXxor;
  gcv.line_width=(int)((screen.size/10.0)*5);
  XChangeGC(screen.disp,screen.gc,GCFunction|GCLineWidth,&gcv);
  
  XSetForeground(XtDisplay(screen.field),screen.gc
                 ,BlackPixel(screen.disp,DefaultScreen(screen.disp)));
  /*
     XSetForeground(XtDisplay(screen.field),screen.gc,screen.Color[8].pixel);
   */            

  DrawLargeLoad(Obj,RECT);
  
  gcv.function=GXcopy;
  gcv.line_width=1;
  XChangeGC(screen.disp,screen.gc,GCFunction|GCLineWidth,&gcv);
}
#endif /* __CELLapist__ */

void
put_obj(double jusin_x,double jusin_y
        ,double point_x,double point_y)
{
  double dx, dy, shita;
  int obj_num = Obj_cnt;
  
  Obj_cnt++;

  if(Obj_cnt > Obj_max)
  {
    int i,j;
    OBJECT *newObj;

    newObj = (OBJECT *)xmalloc(sizeof(OBJECT)*Obj_cnt);

    for(i=0;i<obj_num;i++)
    {
      newObj[i].jusin.x    = Obj[i].jusin.x;
      newObj[i].jusin.y    = Obj[i].jusin.y;
      newObj[i].startPos.x = Obj[i].startPos.x;
      newObj[i].startPos.y = Obj[i].startPos.y;
      newObj[i].delta      = Obj[i].delta;
      newObj[i].time       = Obj[i].time;
      newObj[i].flg        = Obj[i].flg;

      for(j=0;j<OBJECT_CORNER;j++)
      {
        newObj[i].pixel[j].x=Obj[i].pixel[j].x;
        newObj[i].pixel[j].y=Obj[i].pixel[j].y;
      }
    }
    free(Obj);

    Obj_max = Obj_cnt;
    Obj = newObj;
  }

  /* normalization */
#ifdef __CELLapist__
  jusin_x /= screen.size;
  jusin_y /= screen.size;
  point_x /= screen.size;
  point_y /= screen.size;
#endif /* __CELLapist__ */
  
  Obj[obj_num].time                                     = 0;
  Obj[obj_num].delta                                    = 0.0;
  Obj[obj_num].flg                                      = FALSE;
  Obj[obj_num].startPos.x = Obj[obj_num].jusin.x        = jusin_x;
  Obj[obj_num].startPos.y = Obj[obj_num].jusin.y        = jusin_y;
  
  dx = point_x-jusin_x;
  dy = point_y-jusin_y;

  if(dx != 0.0)
  { 
    shita = atan(dy / dx);
    if(dx < 0.0) shita += M_PI;
  }
  else
    shita = M_PI/2.0;

{
  double x_cos,x_sin,y_cos,y_sin;

  x_cos = OBJECT_X/2.0 * cos(shita);
  x_sin = OBJECT_X/2.0 * sin(shita);
  y_cos = OBJECT_Y/2.0 * cos(shita);
  y_sin = OBJECT_Y/2.0 * sin(shita);
  
  Obj[obj_num].pixel[1].x = Obj[obj_num].jusin.x + x_cos - y_sin;
  Obj[obj_num].pixel[1].y = Obj[obj_num].jusin.y + x_sin + y_cos;
  
  Obj[obj_num].pixel[2].x = Obj[obj_num].jusin.x + x_cos + y_sin;
  Obj[obj_num].pixel[2].y = Obj[obj_num].jusin.y + x_sin - y_cos;
  
  Obj[obj_num].pixel[3].x = Obj[obj_num].jusin.x - x_cos + y_sin;
  Obj[obj_num].pixel[3].y = Obj[obj_num].jusin.y - x_sin - y_cos;
  
  Obj[obj_num].pixel[4].x = Obj[obj_num].jusin.x - x_cos - y_sin;
  Obj[obj_num].pixel[4].y = Obj[obj_num].jusin.y - x_sin + y_cos;
}
}
#endif /* __LargeLoad__ */
