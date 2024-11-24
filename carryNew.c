#ifdef __LargeLoad__
#include <math.h>
#if defined(__CELLapist__)
# include "X_include.h"
#endif /* __CELLapist__ */
#include "constant.h"
#include "Conveyor.h"
#include "globals.h"
#include "largeload.h"

struct _line { double a,b; int infty; };

void sumation(OBJECT Obj,int x,int y,double *Fx,double *Fy,double *Phai)
{
  int i;
  double dx, dy, Ax, Ay;

  dx = ((double)x  + 0.5) - Obj.jusin.x;
  dy = ((double)y  + 0.5) - Obj.jusin.y;

  Ax = Ay = 0.0;
  for(i = CONVEYOR_UP; i <= CONVEYOR_LEFT; i <<= 1)
    if(Cell[pos(x, y)].state & i)
    {
      switch(i)
      {
       case CONVEYOR_UP:
        Ax +=   0.0; Ay +=  -1.0; break; /* UP         */
       case CONVEYOR_RIGHT:
        Ax +=   1.0; Ay +=   0.0; break; /* RIGHT      */
       case CONVEYOR_DOWN:
        Ax +=   0.0; Ay +=   1.0; break; /* DOWN       */
       case CONVEYOR_LEFT:
        Ax +=  -1.0; Ay +=   0.0; break; /* LEFT       */
      }
    }
  
  *Fx += Ax;
  *Fy += Ay;
  *Phai += (Ay * dx - Ax * dy);
}

double Fnc(int x, struct _line line)
{
  x = x + 0.5;
  if(line.infty == TRUE)
  {
    return(x);
  }
  else
  {
    return(line.a * (double)x + line.b);
  }
}

void calc_line(struct _line *line,struct _pixel start,struct _pixel end)
{
  if(end.x == start.x)
  {
    line->infty = TRUE;
  }
  else 
  {
    line->infty = FALSE;
    line->a = (end.y - start.y) / (end.x - start.x);
    line->b = start.y - start.x * line->a;
  }
}

void recalc_jusin(OBJECT *Obj)
{
  int i;
  struct _pixel tmp;

  tmp.x = 0.0;
  tmp.y = 0.0;
  
  for(i=1;i<OBJECT_CORNER;i++)
  {
    tmp.x += Obj->pixel[i].x;
    tmp.y += Obj->pixel[i].y;
  }

  Obj->jusin.x = tmp.x/(OBJECT_CORNER-1.0);
  Obj->jusin.y = tmp.y/(OBJECT_CORNER-1.0);
}

int move_obj(OBJECT *Obj)
{
  int i, j, x, y;
  int ptr[4],tmp_ptr;
  struct _line line[4];
  double Fx, Fy, Phai;
  double tmp, tmp2, Obj_I;
  double error;
#ifdef __CELLapist__
  extern void drawsquare(OBJECT);
#endif /* __CELLapist__ */

  /* when the object isn't putted yet */
  if(Obj->pixel[1].x == 0) return(NONE);

  /* initialize */
  Fx = Fy = Phai = 0.0;
  for(i = 0; i < 4; i++)
    ptr[i] = i + 1;
  for(i = 0; i < 3; i++)
    for(j = i + 1; j < 4; j++)
      if(Obj->pixel[ptr[i]].x > Obj->pixel[ptr[j]].x)
      {
        /* swap order of position */
        tmp_ptr = ptr[i];
        ptr[i] = ptr[j];
        ptr[j] = tmp_ptr;
      }

  calc_line(&line[0], Obj->pixel[ptr[0]], Obj->pixel[ptr[1]]);
  calc_line(&line[1], Obj->pixel[ptr[0]], Obj->pixel[ptr[2]]);
  calc_line(&line[2], Obj->pixel[ptr[3]], Obj->pixel[ptr[1]]);
  calc_line(&line[3], Obj->pixel[ptr[3]], Obj->pixel[ptr[2]]);

  for(x=MAX((int)(Obj->pixel[ptr[0]].x+0.5),0);
      x<=MIN((int)(Obj->pixel[ptr[3]].x-0.5),(screen.x-1));
      x++)
    if( x<=(int)(Obj->pixel[ptr[1]].x-0.5) )
    {
      int y_min,y_max;

      y_min = (int)(MIN(Fnc(x,line[0]),Fnc(x,line[1]))+0.5);
      y_max = (int)(MAX(Fnc(x,line[0]),Fnc(x,line[1]))-0.5);

      for(y= MAX(y_min,0);y<=MIN(y_max,(screen.y-1));y++)
        if(Cell[pos(x,y)].state & CONVEYOR_MOVE_MASK) 
          sumation(*Obj,x,y,&Fx,&Fy,&Phai);
    }
    else if(   x> (int)(Obj->pixel[ptr[1]].x+0.5)
            && x<=(int)(Obj->pixel[ptr[2]].x-0.5))
    {
      int y_min,y_max;

      y_min = (int)(MIN(Fnc(x,line[2]),Fnc(x,line[1]))+0.5);
      y_max = (int)(MAX(Fnc(x,line[2]),Fnc(x,line[1]))-0.5);

      for(y=MAX(0,y_min);y<=MIN((screen.y-1),y_max);y++)
        if(Cell[pos(x,y)].state & CONVEYOR_MOVE_MASK) 
          sumation(*Obj,x,y,&Fx,&Fy,&Phai);
    }        
    else if(x>(int)(Obj->pixel[ptr[2]].x+0.5))
    {
      int y_min,y_max;

      y_min = (int)(MIN(Fnc(x,line[2]),Fnc(x,line[3]))+0.5);
      y_max = (int)(MAX(Fnc(x,line[2]),Fnc(x,line[3]))-0.5);

      for(y= MAX(y_min,0);y<=MIN(y_max,(screen.y-1));y++)
        if(Cell[pos(x,y)].state & CONVEYOR_MOVE_MASK) 
          sumation(*Obj,x,y,&Fx,&Fy,&Phai);
    }

  Obj_I = (POW2(OBJECT_X)+POW2(OBJECT_Y))*OBJECT_AREA*OBJECT_RHO*4.0/3.0;
  Phai  /= (2.0*Obj_I);
  Fx    /= (double)OBJECT_AREA;
  Fy    /= (double)OBJECT_AREA;
  
#ifdef __CELLapist__
  drawsquare(*Obj);
#endif /* __CELLapist__ */

  /* heisin */
  for(i = 0; i < 5; i++)
  {
    Obj->pixel[i].x += Fx;
    Obj->pixel[i].y += Fy;
  }
  Obj->delta += sqrt(POW2(Fx)+POW2(Fy));
  
  recalc_jusin(Obj);
  
  for(i = 1; i < OBJECT_CORNER; i++)
  {
    tmp  = (Obj->pixel[i].x -= Obj->jusin.x);
    tmp2 = (Obj->pixel[i].y -= Obj->jusin.y);
    
    Obj->pixel[i].x = (tmp * cos(Phai) - tmp2 * sin(Phai));
    Obj->pixel[i].y = (tmp * sin(Phai) + tmp2 * cos(Phai));
    
    Obj->pixel[i].x += Obj->jusin.x;
    Obj->pixel[i].y += Obj->jusin.y;
  }

  /* Reach to the target position */
  error = sqrt((double)POW2(target.x-Obj->jusin.x)
               + (double)POW2(target.y-Obj->jusin.y));

/*
  fprintf(stderr,"target(%f,%f)-pos(%f,%f) error:%f\n"
          ,target.x,target.y
          ,Obj->jusin.x,Obj->jusin.y
          ,error);
 */

  if(error <= 1.0 )    /* reached */
    return(REACHED);

  /* stop? (MAX_TIME以上経過後にどれぐらい動いているか評価)*/
  if(screen.epoch > MAX_TIME)
  {
    /* 現在，全く動かない場合→情報が届いていない(?) */
    if(Fx==0.0 && Fy==0.0 && Phai==0.0)
    {
      /* Not implemented */
    }

    /* 最初から0.5セル分も移動していない->とまり続けている */
    if(Obj->delta < 0.5)
      return(STOP);
  }

#ifdef __CELLapist__
  drawsquare(*Obj);
#endif /* __CELLapist__ */
  return(MOVING);                    /* moving */
}
#endif /* __LargeLoad__ */
