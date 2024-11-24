#include "Conveyor.h"

#include "globals.h"

/* Lookup table */
extern int conveyor_forward[];
extern int conveyor_right[];
extern int conveyor_backward[];
extern int conveyor_left[];
extern int conveyor_Lrotate[];
extern int conveyor_Rrotate[];

/* Below defined conveyorRule4MOD.c */
extern long GetRelativeNeighbour(long state,long neighbour);
extern int countsignal(int neighbour);
extern int stateAllowForward(int neighbour);
extern int stateAllowCenter(int neighbour);
extern int stateAllowOPP(int neighbour);
extern int stateAllowCCW(int neighbour);
extern int CantAllocateNum(int neighbour);
extern int stateLeftBySignal(int neighbour);
extern int isOPPsignal(int neighbour);

#define conveyorCheckRegion(x,y,dx,dy) (((x)+(dx)>=0 && (x)+(dx)<screen.x)&&((y)+(dy)>=0 && (y)+(dy)<screen.y))

unsigned long conveyorVacumNewstateFujita(int);

/* when flag == TRUE use GA mask */
unsigned long conveyorNeighbourStateFujita(CELL *celluar,int neighbour,int flag)
{
  int x,y,state=0;
  
  x=celluar->x; y=celluar->y;
  
  state |= conveyorCheckANDStateFujita(x,y, 0,-1,CONVEYOR_UP   ,flag);
  state |= conveyorCheckANDStateFujita(x,y,+1, 0,CONVEYOR_RIGHT,flag);
  state |= conveyorCheckANDStateFujita(x,y, 0,+1,CONVEYOR_DOWN ,flag);
  state |= conveyorCheckANDStateFujita(x,y,-1, 0,CONVEYOR_LEFT ,flag);
  
  if(neighbour==8)
  {
    state |= conveyorCheckANDStateFujita(x,y,+1,-1,CONVEYOR_UP_RIGHT  ,flag);
    state |= conveyorCheckANDStateFujita(x,y,-1,-1,CONVEYOR_UP_LEFT   ,flag);
    state |= conveyorCheckANDStateFujita(x,y,+1,+1,CONVEYOR_DOWN_RIGHT,flag);
    state |= conveyorCheckANDStateFujita(x,y,-1,+1,CONVEYOR_DOWN_LEFT ,flag);
  }
  return(state);
}

int conveyorCheckANDStateFujita(int x,int y,int dx,int dy,int direction,int flag)
{
  unsigned long state;
  int i;
  int now_pos,neighbour_pos;
  int signal=NO_SIGNAL;
  extern unsigned long signal_mask;

  now_pos=pos(x,y);
  neighbour_pos=pos(x+dx,y+dy);
  if(conveyorCheckRegion(x,y,dx,dy))
    if(flag==TRUE) /* when GA rule */
    {
/* Not implemented
      if( (Cell[position].state & signal_mask) != 0)
      {
        return(direction);
      }
 */      
    }
    else
    {
      if( (Cell[neighbour_pos].state & CONVEYOR_MOVE_MASK) != 0)
      {
        if( conveyor_backward[Cell[neighbour_pos].state] == direction ) 
          signal = LOOKING;
        else
          signal = SIGNAL;
      }
      else if( Cell[neighbour_pos].state & CONVEYOR_CANT_ALLOC )
        signal = CANT_ALLOC;

      /* shift-up signal */
      for(i=1;i<direction/CONVEYOR_UP;(i <<= 1))
        signal <<= SIG_LENGTH;
      return(signal);
    }
  return(0);
}


void conveyorUpdateCellState4Fujita(CELL *celluar)
{
  int neighbour,neighbour_state;
  
  celluar->isUpdated = TRUE;

  neighbour=conveyorNeighbourStateFujita(celluar,4,FALSE);
  
  switch(celluar->state)
    {
     case CONVEYOR_VACUM:
     case CONVEYOR_SENSOR:
      celluar->newstate = conveyorVacumNewstateFujita(neighbour);
      break;
     case CONVEYOR_CONTROL:
     case CONVEYOR_CONTROL|CONVEYOR_SENSOR:
      celluar->newstate = CONVEYOR_CONTROL;
      break;
     default:
      celluar->newstate = celluar->state;
      break;
    }
  
#ifdef __CELLapist__
  if(celluar->newstate & CONVEYOR_MOVE_MASK)
    celluar->color=1;
#endif /* __CELLapist */
}  

int stateAllowState(int neighbour)
{
  int i;
  int tmp;
  
  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) == SIGNAL )
      tmp = (1 << i+2);
  }

  switch( tmp )
    {
     case CONVEYOR_UP:
      return(Cell[pos(x  ,y-1)].state);
      break;
     case CONVEYOR_RIGHT:
      return(Cell[pos(x+1,y  )].state);
      break;
     case CONVEYOR_DOWN:
      return(Cell[pos(x  ,y+1)].state);
      break;
     case CONVEYOR_LEFT:
      return(Cell[pos(x+1,y  )].state);
      break;
      
    }

  state |= conveyorCheckANDStateFujita(x,y, 0,-1,CONVEYOR_UP   ,flag);
  state |= conveyorCheckANDStateFujita(x,y,+1, 0,CONVEYOR_RIGHT,flag);
  state |= conveyorCheckANDStateFujita(x,y, 0,+1,CONVEYOR_DOWN ,flag);
  state |= conveyorCheckANDStateFujita(x,y,-1, 0,CONVEYOR_LEFT ,flag);
  
  return(   );
}


unsigned long conveyorVacumNewstateFujita(int neighbour)
{
#ifdef __DEBUG__
  fprintf(stderr,"[%2x %1d]",neighbour,countsignal(neighbour));
#endif /* __DEBUG__ */
  
  switch(countsignal(neighbour))
    {
     case 1:
      return( stateAllowState(neighbour) );
      break;
     case 2:
      if( isOPPsignal(neighbour) )
      {
        return( stateOPPSstate(neighbour) );
/*
        if( (rand() % 501) / 500.0 > 0.5 )
          return( stateAllowOPP(neighbour) );
        else
          return( conveyor_backward[stateAllowOPP(neighbour)] );
 */
/*        
        if( CantAllocateNum(neighbour) )
          return( stateAllowOPP(neighbour) );
        else
          return( conveyor_backward[stateAllowOPP(neighbour)] );
 */          
      }
      else
      {
        switch( CantAllocateNum(neighbour) )
        {
         case 0:
          return( stateAllowCCW(neighbour) );
          break;
         case 1: /* Must Test Test Test !! */
/*
          if( stateLeftBySignal(neighbour) == CANT_ALLOC )
          {
            return( stateAllowCCW(neighbour) );
          }
          else
          {
            return( conveyor_right[stateAllowCCW(neighbour)] );
          }
 */
          return( conveyor_right[stateAllowCCW(neighbour)] );
          break;
         case 2:
          return( conveyor_right[stateAllowCCW(neighbour)] );
         default:
          fprintf(stderr,"Why so much CA's?\n");
          break;
        }
      }
      break;
     case 3:
      return( stateAllowCenter(neighbour) );
      break;
     case 4:
      return( CONVEYOR_DOWN );
      break;
     default:
      return(CONVEYOR_VACUM);
      break;
    }
}

