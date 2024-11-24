#ifndef __MACROS_H__

#define MIN(x,y) ((x)>(y)?(y):(x))
#define MAX(x,y) ((x)<(y)?(y):(x))
#define ABS(x)   ((x)>0?(x):(-(x)))
#define POW2(x)	 ((x)*(x))

#define pos(X,Y)  ((int)((Y)*screen.x+(X)))
#define pos_x(P)  ((int)((P)%screen.y))
#define pos_y(P)  ((int)((P)/screen.y))

#define MASK(x)   (1 << (x))

#define __MACROS_H__
#endif /* ! __MACROS_H__ */

