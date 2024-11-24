#include "Conveyor.h"

#include "globals.h"

/* Lookup table */
extern int conveyor_forward[];
extern int conveyor_right[];
extern int conveyor_backward[];
extern int conveyor_left[];
extern int conveyor_Lrotate[];
extern int conveyor_Rrotate[];

#define conveyorCheckRegion(x,y,dx,dy) (((x)+(dx)>=0 && (x)+(dx)<screen.x)&&((y)+(dy)>=0 && (y)+(dy)<screen.y))

unsigned long conveyorVacumNewstate(int);

/* when flag == TRUE use GA mask */
unsigned long conveyorNeighbourStateMOD(CELL *celluar,int neighbour,int flag)
{
  int x,y,state=0;
  
  x=celluar->x; y=celluar->y;
  
  state |= conveyorCheckANDStateMOD(x,y, 0,-1,CONVEYOR_UP   ,flag);
  state |= conveyorCheckANDStateMOD(x,y,+1, 0,CONVEYOR_RIGHT,flag);
  state |= conveyorCheckANDStateMOD(x,y, 0,+1,CONVEYOR_DOWN ,flag);
  state |= conveyorCheckANDStateMOD(x,y,-1, 0,CONVEYOR_LEFT ,flag);
  
  if(neighbour==8)
  {
    state |= conveyorCheckANDStateMOD(x,y,+1,-1,CONVEYOR_UP_RIGHT  ,flag);
    state |= conveyorCheckANDStateMOD(x,y,-1,-1,CONVEYOR_UP_LEFT   ,flag);
    state |= conveyorCheckANDStateMOD(x,y,+1,+1,CONVEYOR_DOWN_RIGHT,flag);
    state |= conveyorCheckANDStateMOD(x,y,-1,+1,CONVEYOR_DOWN_LEFT ,flag);
  }
  return(state);
}

int conveyorCheckANDStateMOD(int x,int y,int dx,int dy,int direction,int flag)
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
        {
#ifdef __DEBUG__
          fprintf(stderr,"L");
#endif /* __DEBUG__ */
          signal = LOOKING;
        }
        else
        {
#ifdef __DEBUG__
          fprintf(stderr,"S");
#endif /* __DEBUG__ */
          signal = SIGNAL;
        }
      }
      else if( Cell[neighbour_pos].state & CONVEYOR_CANT_ALLOC )
      {
#ifdef __DEBUG__
        fprintf(stderr,"A");
#endif /* __DEBUG__ */
        signal = CANT_ALLOC;
      }

#ifdef __DEBUG__
      if(signal == NO_SIGNAL)
        fprintf(stderr," ");
#endif /* __DEBUG__ */

      /* shift-up signal */
      for(i=1;i<direction/CONVEYOR_UP;(i <<= 1))
      {
        signal <<= SIG_LENGTH;
      }
      return(signal);
    }
#ifdef __DEBUG__
  else
    fprintf(stderr," ");
#endif /* __DEBUG__ */
  
  return(0);
}

long GetRelativeNeighbour(long state,long neighbour)
{
  return(
         (((neighbour << conveyor_Lrotate[state]) &
           ~( (1 << conveyor_Lrotate[state])-1) )
          |
          ((neighbour >> conveyor_Rrotate[state]) &
           ( (1 << conveyor_Lrotate[state] )-1)))
         & ((1 << (SIG_LENGTH * 4)) -1) );
}

unsigned long conveyorDynamicState(long state,int neighbour)
{
  int relative_neighbour;
  int sens_flag=FALSE;
  
  state       &= ~CONVEYOR_SENSOR;
  
  relative_neighbour = GetRelativeNeighbour( state,neighbour );

  
  if(  (UP(relative_neighbour)          == CANT_ALLOC) 
     ||(UP(relative_neighbour)    == NO_SIGNAL)
     ||(UP(relative_neighbour)  == LOOKING))
/*
   ((UP(relative_neighbour)          == CANT_ALLOC) &&
       ((RIGHT(relative_neighbour)      == LOOKING) ||
        (LEFT(relative_neighbour)       == LOOKING)))
 */
  {
#ifdef __DEBUG2__
    fprintf(stderr,"(A)%x -> %x (%x)\n",neighbour,relative_neighbour,state);
#endif /* __DEBUG2__ */
    return(CONVEYOR_CANT_ALLOC); 
  }
  else if(/* ((LEFT(relative_neighbour)     == LOOKING
            && RIGHT(relative_neighbour) == NO_SIGNAL))
          || */
          ((LEFT(relative_neighbour)     == NO_SIGNAL
            && RIGHT(relative_neighbour) == LOOKING)))
  {
#ifdef __DEBUG2__
    fprintf(stderr,"(B)%x -> %x (%x)\n",neighbour,relative_neighbour,state);
#endif /* __DEBUG2__ */
    return(CONVEYOR_CANT_ALLOC);
  }
  else
  {
    return(state);
  }
}

void conveyorUpdateCellState4MOD(CELL *celluar)
{
  int neighbour,neighbour_state;
  
  celluar->isUpdated = TRUE;

  neighbour=conveyorNeighbourStateMOD(celluar,4,FALSE);
  
  switch(celluar->state)
    {
     case CONVEYOR_VACUM:
      celluar->newstate = conveyorVacumNewstate(neighbour);
#ifdef __DEBUG__
      if(celluar->x == 9) fprintf(stderr,"\n");
#endif /* __DEBUG__ */
      break;
     case CONVEYOR_SENSOR:
      celluar->newstate = conveyorVacumNewstate(neighbour);
#ifdef __DEBUG__
      if(celluar->x == 9) fprintf(stderr,"\n");
#endif /* __DEBUG__ */
      break;
     case CONVEYOR_CONTROL:
     case CONVEYOR_CONTROL|CONVEYOR_SENSOR:
      celluar->newstate = CONVEYOR_CONTROL;
#ifdef __DEBUG__
      fprintf(stderr,"[%2x S]",celluar->state);
#endif /* __DEBUG__ */
      break;
     case CONVEYOR_CANT_ALLOC:
     case CONVEYOR_CANT_ALLOC|CONVEYOR_SENSOR:
      celluar->newstate = CONVEYOR_VACUM;
#ifdef __DEBUG__
      fprintf(stderr,"[%2x A]",celluar->state);
#endif /* __DEBUG__ */
      break;
     default:
      celluar->newstate = conveyorDynamicState(celluar->state,neighbour);
#ifdef __DEBUG__
      fprintf(stderr,"[%2x S]",celluar->state);
#endif /* __DEBUG__ */
      break;
    }
  
#ifdef __CELLapist__
  if(celluar->newstate & CONVEYOR_MOVE_MASK)
    celluar->color=1;
#endif /* __CELLapist */
}  

int countsignal(int neighbour)
{
  int count=0;
  int i;
  
  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) == SIGNAL )
      count++;
  }
  
  return(count);
}

int stateAllowForward(int neighbour)
{
  int i;
  
  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) == SIGNAL )
      return( (1 << i+2) );
  }
}

int stateAllowCenter(int neighbour)
{
  int i;

  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) != SIGNAL )
    {
      return( conveyor_backward[(1 << (i+2))] );
    }
  }
}

int stateAllowOPP(int neighbour)
{
  int i;
  
  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) == SIGNAL)
      return( 1 << (i+2) );
  }
}

int stateAllowCCW(int neighbour)
{
  int i;
  
  if( UP(neighbour) == SIGNAL && LEFT(neighbour) == SIGNAL )
    return(CONVEYOR_LEFT);

  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) == SIGNAL )
      return( (1 << i+2) );
  }
}

int CantAllocateNum(int neighbour)
{
  int i;
  int count=0;
  
  for(i=0;i<4;i++)
    if( SHIFT(SIG_LENGTH*i,neighbour) == CANT_ALLOC)
      count++;

  return(count);
}

int stateLeftBySignal(int neighbour)
{
  int i;

  for(i=0;i<4;i++)
  {
    if( SHIFT(SIG_LENGTH*i,neighbour) == SIGNAL )
      break;
  }

  if( i=0 )
    return( SHIFT(SIG_LENGTH*3,neighbour) );
  else
    return( SHIFT(SIG_LENGTH*(i-1),neighbour) ); 
}


int isOPPsignal(int neighbour)
{
  if( (UP(neighbour) == SIGNAL && DOWN(neighbour) == SIGNAL)
     ||(RIGHT(neighbour) == SIGNAL && LEFT(neighbour) == SIGNAL))
    return(TRUE);
  else
  {
    return(FALSE);
  }
  
}
  
unsigned long conveyorVacumNewstate(int neighbour)
{
#ifdef __DEBUG__
  fprintf(stderr,"[%2x %1d]",neighbour,countsignal(neighbour));
#endif /* __DEBUG__ */
  
  switch(countsignal(neighbour))
    {
     case 1:
      return( stateAllowForward(neighbour) );
      break;
     case 2:
      if( isOPPsignal(neighbour) )
      {
        return( stateAllowOPP(neighbour) );
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

