#include "Pattern.h"

#include "globals.h"

/* Private関数の定義 */
static void patternUpdateState(int);
static void patternSensor();
extern void patternMoveSensor(CELL *);
extern void patternUpdateCellState(CELL *);
static void patternSetState(void);
static void patternSetCellState(CELL *);
extern int patternGetState(int,int,int,int);
extern pattern_score patternNeighbourState(CELL *);
static void patternCheckANDState(int,int,int,int,pattern_score *);
extern int patternCheckRegion(int,int,int,int);
extern int patternRealMove(int,int,int,int);

#ifdef __CELLapist__
extern void patternSetCursor(int,int,int);
extern void patternDrawCell(Drawable,float,float,int,int,int);
#endif /* __CELLapist__ */

/*
        公開されている関数
*/

/* destoractor (Delete) */
void patternDelete()
{
  return;
}

/* セルの初期化 (New) */
void patternNew(int init_f)
{
  int x,y,position;

  screen.epoch=0;
#ifdef __CELLapist__
  showEpoch();
#endif /* __CELLapist__ */

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        position=pos(x,y);
	Cell[position].x                = x;
	Cell[position].y                = y;
        Cell[position].isUpdated        = FALSE;
        Cell[position].state            = PATTERN_VACUM;
        Cell[position].newstate         = PATTERN_VACUM;
#ifdef __CELLapist__
        Cell[position].color            = PATTERN_VACUM_COLOR;
        patternDrawCell(screen.pix,
                         x,y,PATTERN_VACUM_COLOR,PATTERN_VACUM,screen.size);
#endif /* __CELLapist__ */
      }
#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
  patternSetCursor(PATTERN_VACUM,PATTERN_VACUM_COLOR,0);
  screen.n_st=PATTERN_VACUM;
  screen.sp=pos(screen.x,screen.y);
#endif /* __CELLapist__ */
}

/* セル状態の更新 (Step) */
void patternStep(void)
{
  patternUpdateState(8);
  patternSensor();
  patternSetState();
}

/* ランダムに初期化 (Random) */
#ifdef __CELLapist__
void patternRandom(Widget w,int *dense,caddr_t call_data)
{
  int x,y,s;
  extern Widget StateDistButton[];
  extern Widget StateTop;
  extern int dense,width;
/*
  XtDestroyWidget(StateTop);
 */
  s = *(int *)XawToggleGetCurrent(StateDistButton[1]);
  
  switch(s)
    {
        case 0:
      for(y=0;y<screen.y;y++)
        for(x=0;x<screen.x;x++)
          {
            if(rand()%100>=dense)
              {
                Cell[pos(x,y)].state = PATTERN_VACUM;
                Cell[pos(x,y)].newstate = PATTERN_VACUM;
                Cell[pos(x,y)].color = PATTERN_VACUM_COLOR;
              }
            else
              {
                Cell[pos(x,y)].color = 1;
                switch(rand()%4)
                  {
                   case 0:
                    Cell[pos(x,y)].state = PATTERN_UP;
                    Cell[pos(x,y)].newstate = PATTERN_UP;
                    break;
                   case 1:
                    Cell[pos(x,y)].state = PATTERN_DOWN;
                    Cell[pos(x,y)].newstate = PATTERN_DOWN;
                    break;
                   case 2:
                    Cell[pos(x,y)].state = PATTERN_RIGHT;
                    Cell[pos(x,y)].newstate = PATTERN_RIGHT;
                    break;
                   case 3:
                    Cell[pos(x,y)].state = PATTERN_LEFT;
                    Cell[pos(x,y)].newstate = PATTERN_LEFT;
                    break;
                  }
              }
          }
      break;
        case 1:
      break;
        default:
      break;
    }
  patternRefresh();
  screen.epoch=0;
  showEpoch();
}
#else /* !__CELLapist__ */
void patternRandom(int dense,int mode)
{
  int x,y;
  
  switch(mode)
    {
        case 0:
      sensor_num=0;
      broken_num=0;

      for(y=0;y<screen.y;y++)
        for(x=0;x<screen.x;x++)
          {
            if(rand()%100>=dense)
              {
                Cell[pos(x,y)].state = PATTERN_SENSOR;
                Cell[pos(x,y)].newstate = PATTERN_SENSOR;
                sensor_num++;

                head[pos(x,y)] = tail[pos(x,y)]
                  = (INITIAL *)malloc(sizeof(INITIAL));
                head[pos(x,y)]->start_x=x;
                head[pos(x,y)]->start_y=y;
                tail[pos(x,y)]->next=NULL;
              }
            else
              {
                Cell[pos(x,y)].state = PATTERN_BROKEN;
                Cell[pos(x,y)].newstate = PATTERN_BROKEN;
                broken_num++;

                head[pos(x,y)] = tail[pos(x,y)] = NULL;
              }
          }
      break;
        case 1:
      break;
        default:
      break;
    }
  if(Cell[pos(screen.x/2,screen.y/2)].state==PATTERN_BROKEN)
    broken_num--;
  else
    {
      free(head[pos(screen.x/2,screen.y/2)]);
      head[pos(screen.x/2,screen.y/2)] 
        = tail[pos(screen.x/2,screen.y/2)] = NULL;
      sensor_num--;
    }
  
  Cell[pos(screen.x/2,screen.y/2)].state = PATTERN_CONTROL;
  Cell[pos(screen.x/2,screen.y/2)].newstate = PATTERN_CONTROL;
}
#endif /* ! __CELLapist__ */

/*
        Private関数
*/

void patternUpdateState(int neighbour)
{
  int x,y;

  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
        (patternUpdateCellState)(&Cell[pos(x,y)]);
}

int patternGetState(int x,int y,int dx,int dy)
{

  if(patternCheckRegion(x,y,dx,dy))
    return(Cell[pos((x+dx),(y+dy))].state);
  else
    return(0);
}

pattern_score patternNeighbourState(CELL *celluar)
{
  pattern_score state;
  int x,y;

  state.up=0;
  state.down=0;
  state.right=0;
  state.left=0;

  x=celluar->x; y=celluar->y;
  
  patternCheckANDState(x,y, 0, 0,&state);

  patternCheckANDState(x,y, 0,-1,&state);
  patternCheckANDState(x,y, 0,+1,&state);
  patternCheckANDState(x,y,-1, 0,&state);
  patternCheckANDState(x,y,+1, 0,&state);

  patternCheckANDState(x,y,+1,-1,&state);
  patternCheckANDState(x,y,-1,-1,&state);
  patternCheckANDState(x,y,+1,+1,&state);
  patternCheckANDState(x,y,-1,+1,&state);

  return(state);
}


void patternCheckANDState(int x,int y,int dx,int dy,pattern_score *result)
{
  int state;

  if(!patternCheckRegion(x,y,dx,dy))
    return;

  state = (Cell[pos((x+dx),(y+dy))].state & PATTERN_MOVE_MASK);

  switch(state)
    {
     case PATTERN_UP:
      result->up++;
      break;
     case PATTERN_DOWN:
      result->down++;
      break;
     case PATTERN_RIGHT:
      result->right++;
      break;
     case PATTERN_LEFT:
      result->left++;
      break;
     case PATTERN_UP_RIGHT:
      result->up++;
      result->right++;
      break;
     case PATTERN_UP_LEFT:
      result->up++;
      result->left++;
      break;
     case PATTERN_DOWN_RIGHT:
      result->down++;
      result->right++;
      break;
     case PATTERN_DOWN_LEFT:
      result->down++;
      result->left++;
      break;
     case PATTERN_CONTROL:
      switch(dx)
        {
         case -1:
          result->left  +=PATTERN_CONTROL_SCORE;
          break;
         case 0:
          break;
         case +1:
          result->right +=PATTERN_CONTROL_SCORE;
          break;
        }
      switch(dy)
        {
         case -1:
          result->up    +=PATTERN_CONTROL_SCORE;
          break;
         case 0:
          break;
         case +1:
          result->down  +=PATTERN_CONTROL_SCORE;
          break;
        }
      break;
    }
}

int patternCheckRegion(int x,int y,int dx,int dy)
{
  int nowX,nowY;
  
  nowX=x+dx;
  nowY=y+dy;

  if(nowX>=0 && nowX<screen.x)
    if(nowY>=0 && nowY<screen.y)
      return(TRUE);

  return(FALSE);
}

void patternSetState(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      {
        patternSetCellState(&Cell[pos(x,y)]);
      }
#ifdef __CELLapist__
           exposeField(screen.field,NULL,NULL);
#endif /* __CELLapist__ */
}

void patternSetCellState(CELL *celluar)
{
  celluar->isUpdated=FALSE;

  if(celluar->state==celluar->newstate )
    {
      celluar->newstate=PATTERN_VACUM;
      return;
    }
  celluar->state=celluar->newstate;
#ifdef __CELLapist__
  patternDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,celluar->state,screen.size);
#endif /* __CELLapist__ */
  celluar->newstate=PATTERN_VACUM;
}

void patternSensor()
{
  int x,y;

  for(x=0;x<screen.x;x++)
    for(y=0;y<screen.y;y++)
      if((Cell[pos(x,y)].state & PATTERN_SENSOR))
        patternMoveSensor(&Cell[pos(x,y)]);
}


int patternRealMove(int x,int y,int dx,int dy)
{
  if(patternCheckRegion(x,y,dx,dy))
    {
      Cell[pos(x+dx,y+dy)].newstate |= PATTERN_SENSOR;
#ifndef __CELLapist__
      if(head[pos(x,y)]==NULL) return(1);
      if(headNew[pos(x+dx,y+dy)]!=NULL)
        {
          tailNew[pos(x+dx,y+dy)]->next = head[pos(x,y)];
          tailNew[pos(x+dx,y+dy)] = tail[pos(x,y)];
        }
      else
        {
          headNew[pos(x+dx,y+dy)] = head[pos(x,y)];
          tailNew[pos(x+dx,y+dy)] = tail[pos(x,y)];
        }      
#endif /* ! __CELLapist__ */
      return(1);
    }
  else
    {
      return(0);
    }
}



void patternMoveSensor(CELL *celluar)
{
  int x,y,check=FALSE;
  
  x=celluar->x;
  y=celluar->y;
  
  switch(celluar->state ^ PATTERN_SENSOR)
    {
/* 1 direction */
        case PATTERN_UP:
      check=patternRealMove(x,y, 0,-1);
      break;
        case PATTERN_DOWN:
      check=patternRealMove(x,y, 0, 1);
      break;
        case PATTERN_RIGHT:
      check=patternRealMove(x,y, 1, 0);
      break;
        case PATTERN_LEFT:
      check=patternRealMove(x,y,-1, 0);
      break;
/* 2 direction */
        case PATTERN_UP|PATTERN_RIGHT:
      check=patternRealMove(x,y, 1,-1);
      break;
        case PATTERN_UP|PATTERN_LEFT:
      check=patternRealMove(x,y,-1,-1);
      break;
        case PATTERN_DOWN|PATTERN_RIGHT:
      check=patternRealMove(x,y, 1, 1);
      break;
        case PATTERN_DOWN|PATTERN_LEFT:
      check=patternRealMove(x,y,-1, 1);
      break;
/* destination */
        case PATTERN_CONTROL:
      patternRealMove(x,y,0,0);
      celluar->newstate = PATTERN_CONTROL;
      check=TRUE;
      break;
        default:
      patternRealMove(x,y,0,0);
      return;
      break;
    }
#ifdef __CELLapist__
  if(check)
    patternDrawCell(screen.pix,x,y,celluar->color,celluar->state,screen.size);
#endif /*  __CELLapist__ */
}
