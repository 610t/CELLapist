#include "math.h"
#include "X_include.h"
#include "constant.h"
#include "globals.h"

#ifdef __CELLapist__
void drawsquare(OBJECT Obj)
{
  XDrawLine(screen.disp, screen.pix, screen.gc, 
	    (int)Obj.pixel[2].x, (int)Obj.pixel[2].y, 
	    (int)Obj.pixel[3].x, (int)Obj.pixel[3].y); 
  XDrawLine(screen.disp, screen.pix, screen.gc,
            (int)Obj.pixel[3].x, (int)Obj.pixel[3].y, 
	    (int)Obj.pixel[4].x, (int)Obj.pixel[4].y);
  XDrawLine(screen.disp, screen.pix, screen.gc, 
	    (int)Obj.pixel[4].x, (int)Obj.pixel[4].y, 
	    (int)Obj.pixel[1].x, (int)Obj.pixel[1].y);
  XDrawLine(screen.disp, screen.pix, screen.gc,
	    (int)Obj.pixel[1].x, (int)Obj.pixel[1].y, 
	    (int)Obj.pixel[2].x, (int)Obj.pixel[2].y);
  XDrawLine(screen.disp, screen.pix, screen.gc,
	    (int)Obj.pixel[2].x, (int)Obj.pixel[2].y, 
	    (int)Obj.pixel[4].x, (int)Obj.pixel[4].y);
  XDrawLine(screen.disp, screen.pix, screen.gc, 
	    (int)Obj.pixel[1].x, (int)Obj.pixel[1].y, 
	    (int)Obj.pixel[3].x, (int)Obj.pixel[3].y);
}
#endif /* __CELLapist__ */

void put_obj(OBJECT *Obj,int jusin_x,int jusin_y,double point_x,double point_y)
{
  int i,j,tmp;
  double dx, dy, kyori, shita;
 
  Obj_cnt++;
  Obj->time = 0;
  Obj->jusin.x = (double)jusin_x;
  Obj->jusin.y = (double)jusin_y;
  dx = point_x - Obj->pixel[0].x;
  dy = point_y - Obj->pixel[0].y;
  kyori = sqrt( OBJECT_X * OBJECT_X + OBJECT_Y * OBJECT_Y )
    * CELL_SIZE / (2.0*sqrt( dx * dx + dy * dy ));
  if(dx != 0.0) { 
    shita = atan(dy / dx);
    if(dx < 0.0) shita += M_PI;
  } else {
    shita = M_PI / 2.0;
    if(dy < 0.0) shita = -shita;
    else if(dy == 0.0) shita = 0.0;
  }
  shita += atan2((double)OBJECT_X,(double)OBJECT_Y);
  
  Obj->pixel[4].x = Obj->pixel[0].x 
    + kyori*(point_x - Obj->pixel[0].x);
  Obj->pixel[4].y = Obj->pixel[0].y 
    + kyori*(point_y - Obj->pixel[0].y);
  Obj->pixel[1].x = Obj->pixel[0].x 
    + (int)((double)OBJECT_Y * CELL_SIZE * cos(shita));
  Obj->pixel[1].y = Obj->pixel[0].y 
    + (int)((double)OBJECT_Y * CELL_SIZE * sin(shita));
  Obj->pixel[2].x = Obj->pixel[0].x 
    - (Obj->pixel[4].x-Obj->pixel[0].x);
  Obj->pixel[2].y = Obj->pixel[0].y 
    - (Obj->pixel[4].y-Obj->pixel[0].y);
  Obj->pixel[3].x = Obj->pixel[0].x 
    - (Obj->pixel[1].x-Obj->pixel[0].x);
  Obj->pixel[3].y = Obj->pixel[0].y 
    - (Obj->pixel[1].y-Obj->pixel[0].y);
}
