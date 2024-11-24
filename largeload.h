#if !defined(__LargeLoad_H__)
#define __LargeLoad_H__

#define OBJECT_X        18     /* Require OBJECT_X > OBJECT_Y */
#define OBJECT_Y        12 
#define OBJECT_AREA     (OBJECT_X*OBJECT_Y)
#define OBJECT_RHO      1.0
#define OBJECT_CORNER   5
#define MAX_TIME 200
#define LIMIT 20   /* for Obj.before_*[] */

/* for check arrive to goal */
enum 
{
  NONE,REACHED,STOP,MOVING,
};

struct _pixel { double x, y; };
typedef struct _OBJECT
{
  struct _pixel startPos;
  struct _pixel jusin;
  struct _pixel pixel[OBJECT_CORNER];
  double delta;          /* Moving distance */
  int time,flg; 
} OBJECT;
#endif /* __LargeLoad__ */


