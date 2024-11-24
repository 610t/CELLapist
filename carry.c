#define sqr(x) ((x)*(x))
#ifndef __HYOUKA__
#define CTR_FIELD 20
#endif
#include <math.h>
#include "X_include.h"
#include "constant.h"
#include "Conveyor.h"
#include "globals.h"

struct _line { double a,b; };

/* pixelサイズからcellサイズへ変換 */
int virtual(double value, unsigned char mode)
{
  if(mode)
    return( ((int)value + CELL_SIZE / 2) / CELL_SIZE );
  else
    return( ((int)value - CELL_SIZE / 2) / CELL_SIZE );
}

void sumation(OBJECT Obj,int x,int y,double *Fx,double *Fy,double *Phai)
{
  int i;
  double dx, dy, Ax, Ay, CNST;

  dx = (double)(x * CELL_SIZE + CELL_SIZE / 2) - Obj.jusin.x;
  dy = (double)(y * CELL_SIZE + CELL_SIZE / 2) - Obj.jusin.y;

  Ax = Ay = 0.0;
  CNST = sqrt(2.0);
  for(i = 2; i <= 5; i++)
    if(Cell[pos(x, y)].state & (1 << i))
      {
	switch(i)
	  {
	    /* 1 direction */
	  case 2: Ax =   0.0; Ay =  -1.0; break; /* UP         */
	  case 3: Ax =   1.0; Ay =   0.0; break; /* RIGHT      */
	  case 4: Ax =   0.0; Ay =   1.0; break; /* DOWN       */
	  case 5: Ax =  -1.0; Ay =   0.0; break; /* LEFT       */
	    /* 2 direction */
	  case 6: Ax =  CNST; Ay = -CNST; break; /* UP_RIGHT   */
	  case 7: Ax = -CNST; Ay = -CNST; break; /* UP_LEFT    */
	  case 8: Ax =  CNST; Ay =  CNST; break; /* DOWN_RIGHT */
	  case 9: Ax = -CNST; Ay =  CNST; break; /* DOWN_LEFT  */
	  }
	break;
      }
  
  *Fx += Ax;
  *Fy += Ay;
  *Phai += (Ay * dx - Ax * dy);
}

double Fnc(int x, struct _line line)
{
  x = x * CELL_SIZE + CELL_SIZE / 2;
  return(line.a * (double)x + line.b);
}

void calc_line(struct _line *line,struct _pixel start,struct _pixel end)
{
  line->a = (end.y - start.y) / (end.x - start.x);
  line->b = start.y - start.x * line->a;
}

int move_obj(OBJECT *Obj)
{
  int i, j, x, y;
  int ptr[4],tmp_ptr;
  struct _line line[4];
  double Fx, Fy, Phai;
  double tmp, tmp2, Obj_I;
#ifdef __CELLapist__
  extern void drawsquare(OBJECT);

  /* when the object isn't putted yet */
  if(Obj->pixel[1].x == 0) return(0);
#endif /* __CELLapist__ */

#ifdef __HOGEHOGE__
  /* when the center of object(jusin) already reached target position */
  tmp = sqrt( (double)sqr(target_x - (int)Obj->jusin.x)
	     + (double)sqr(target_y - (int)Obj->jusin.y) );

  if(tmp <= 1.0 * CELL_SIZE) return(1); /* reached */
#endif

  /* initialize */
  Fx = Fy = Phai = 0.0;
  for(i = 0; i < 4; i++) ptr[i] = i + 1;
  for(i = 0; i < 3; i++)
    for(j = i + 1; j < 4; j++)
      if(Obj->pixel[ptr[i]].x > Obj->pixel[ptr[j]].x) {
	tmp_ptr = ptr[i];
	ptr[i] = ptr[j];
	ptr[j] = tmp_ptr;
      }
  calc_line(&line[0], Obj->pixel[ptr[0]], Obj->pixel[ptr[1]]);
  calc_line(&line[1], Obj->pixel[ptr[0]], Obj->pixel[ptr[2]]);
  calc_line(&line[2], Obj->pixel[ptr[3]], Obj->pixel[ptr[1]]);
  calc_line(&line[3], Obj->pixel[ptr[3]], Obj->pixel[ptr[2]]);

  /* before places */
  if(screen.epoch == MAX_TIME)
    for(i=0;i<LIMIT;i++) Obj->before[i].x=Obj->before[i].y=0.0;  
  if(screen.epoch > MAX_TIME) {
    for(i=LIMIT-1;i>0;i--) {
      Obj->before[i].x = Obj->before[i-1].x;
      Obj->before[i].y = Obj->before[i-1].y;
    }
    Obj->before[0].x = Obj->jusin.x;
    Obj->before[0].y = Obj->jusin.y;    
  }

  for(x = virtual(Obj->pixel[ptr[0]].x, 1);
      x <= virtual(Obj->pixel[ptr[3]].x, 0);
      x++) if(x >= 0 && x < screen.x) 
	if(Obj->pixel[ptr[1]].y < Obj->pixel[ptr[2]].y) {
	  for(y = virtual(Obj->pixel[ptr[1]].y, 1);
	      y <= virtual(Obj->pixel[ptr[2]].y, 0); 
	      y++) if(y >= 0 && y < screen.y) 
		if(Cell[pos(x,y)].state & CONVEYOR_MOVE_MASK) 
		  if(x-virtual(Obj->pixel[ptr[0]].x,1) >= 0
		     && x-virtual(Obj->pixel[ptr[0]].x,1) < screen.x
		     && y-virtual(Obj->pixel[ptr[1]].y,1) >= 0
		     && y-virtual(Obj->pixel[ptr[1]].y,1) < screen.y)
		  if(  ( x <= virtual(Obj->pixel[ptr[1]].x, 0)
			&& y >= virtual(Fnc(x, line[0]), 1)
			&& y <= virtual(Fnc(x, line[1]), 0) )
		     ||( x > virtual(Obj->pixel[ptr[1]].x, 1)
			&& x <= virtual(Obj->pixel[ptr[2]].x, 0)
			&& y >= virtual(Fnc(x, line[2]), 1)
			&& y <= virtual(Fnc(x, line[1]), 0) )
		     ||( x > virtual(Obj->pixel[ptr[2]].x, 1)
			&& y >= virtual(Fnc(x, line[2]), 1)
			&& y <= virtual(Fnc(x, line[3]), 0) ) )
		      sumation(*Obj,x,y,&Fx,&Fy,&Phai);
	} else {
	  for(y = virtual(Obj->pixel[ptr[2]].y, 1);
	      y <= virtual(Obj->pixel[ptr[1]].y, 0); 
	      y++) if(y >= 0 && y < screen.y) 
		if(Cell[pos(x,y)].state & CONVEYOR_MOVE_MASK) 
		  if(x-virtual(Obj->pixel[ptr[0]].x,1) >= 0
		     && x-virtual(Obj->pixel[ptr[0]].x,1) < screen.x
		     && y-virtual(Obj->pixel[ptr[2]].y,1) >= 0
		     && y-virtual(Obj->pixel[ptr[2]].y,1) < screen.y)
		  if(  ( x <= virtual(Obj->pixel[ptr[1]].x, 0)
			&& y >= virtual(Fnc(x, line[1]), 1)
			&& y <= virtual(Fnc(x, line[0]), 0) )
		     ||( x > virtual(Obj->pixel[ptr[1]].x, 1)
			&& x <= virtual(Obj->pixel[ptr[2]].x, 0)
			&& y >= virtual(Fnc(x, line[1]), 1)
			&& y <= virtual(Fnc(x, line[2]), 0) )
		     ||( x > virtual(Obj->pixel[ptr[2]].x, 1)
			&& y >= virtual(Fnc(x, line[3]), 1)
			&& y <= virtual(Fnc(x, line[2]), 0) ) )
		      sumation(*Obj,x,y,&Fx,&Fy,&Phai);
	}

  Obj_I = (OBJECT_X * OBJECT_X + OBJECT_Y * OBJECT_Y) 
    * OBJECT_X * OBJECT_Y * OBJECT_RHO * 4.0 / 3.0;
  Phai = Phai / (Obj_I * 2.0);
  Fx = (Fx / (double)(OBJECT_X * OBJECT_Y));
  Fy = (Fy / (double)(OBJECT_X * OBJECT_Y));
  
  /* heisin */
  for(i = 0; i < 5; i++) {
    Obj->pixel[i].x += Fx * CELL_SIZE;
    Obj->pixel[i].y += Fy * CELL_SIZE;
  }
  /* kaiten */
  for(i = 1; i < 5; i++) {
    tmp = Obj->pixel[i].x -= Obj->jusin.x;
    tmp2 = Obj->pixel[i].y -= Obj->jusin.y;
    
    Obj->pixel[i].x = tmp * cos(Phai) - tmp2 * sin(Phai);
    Obj->pixel[i].y = tmp * sin(Phai) + tmp2 * cos(Phai);
    
    Obj->pixel[i].x += Obj->jusin.x;
    Obj->pixel[i].y += Obj->jusin.y;
  }

  /* stoping ? */
  if(screen.epoch > MAX_TIME) {
#ifdef __HOGEHOGE__
    /* 全く動かない＝情報が届いていない */
    if(Fx==0.0 && Fy==0.0 && Phai==0.0) {
      tmp = sqrt( (double)sqr(target_x - (int)Obj->jusin.x)
		 + (double)sqr(target_y - (int)Obj->jusin.y) );
      if(tmp > (CTR_FIELD/2)*CELL_SIZE) return(-1);
    }
#endif
    /* ほとんど動かない＝LIMITステップ前の座標と０．５セル分も変わらない */
    tmp = sqrt( sqr(Obj->before[LIMIT-1].x - Obj->jusin.x)
	       + sqr(Obj->before[LIMIT-1].y - Obj->jusin.y) );
    if(tmp < 0.5 * CELL_SIZE){
#ifdef __HOGEHOGE__
      tmp = sqrt( (double)sqr(target_x - (int)Obj->jusin.x)
		 + (double)sqr(target_y - (int)Obj->jusin.y) );
#endif
      if(tmp > (CTR_FIELD/2)*CELL_SIZE) {
/*
	fprintf(stderr," ... tyau iti!! (kyori%5.2lf)\n",tmp);
	for(i=LIMIT-1;i>=0;i--) 
	  fprintf(stderr,"%8dstep(%7.3lf, %7.3lf)\n",
		  screen.epoch-i-1,Obj->before[i].x,Obj->before[i].y);
	tmp = sqrt( sqr(Obj->before[LIMIT-1].x - Obj->jusin.x)
		   + sqr(Obj->before[LIMIT-1].y - Obj->jusin.y) );
	fprintf(stderr,"%8dstep(%7.3lf,%7.3lf)<%lf %lf %lf>%lf\n",
		screen.epoch,Obj->jusin.x,Obj->jusin.y,Fx,Fy,Phai,tmp);
*/	return(-2);
      }
    }
  }
#ifdef __CELLapist__
  if(screen.epoch % 5 == 0) drawsquare(*Obj);
#endif /* __CELLapist__ */
  return(0); /* moving */
}
