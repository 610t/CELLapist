#include "Conveyor.h"

#include "globals.h"
  
extern conveyorNeighbourState(CELL*,int,int);

void 
  conveyorUpdateCellState8Fujita(CELL *celluar)
{
  int neighbour,neighbour_state;
  int tmp;
  
  celluar->isUpdated = TRUE;

  if(celluar->state & CONVEYOR_CONTROL ||
     celluar->state & 
     (CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT) ||
     celluar->state & CONVEYOR_BROKEN)
    {
      celluar->newstate 
        = celluar->state & 
          (CONVEYOR_CONTROL|CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT|CONVEYOR_BROKEN);
      return;
    }
  
  neighbour=conveyorNeighbourState(celluar,8,FALSE);
  
#ifdef __CELLapist__
  if(neighbour)
    celluar->color=1;
#endif /* __CELLapist */
  
  celluar->newstate = CONVEYOR_VACUM;
  
  switch(neighbour)
    {
/******
  1 information (8) 
******/
     case CONVEYOR_UP:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_UP;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_DOWN;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT:
      tmp = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_RIGHT;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_LEFT;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT:
      tmp = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_UP_RIGHT;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_UP_LEFT;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_DOWN_RIGHT;
      else
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == CONVEYOR_CONTROL )
        celluar->newstate = CONVEYOR_DOWN_LEFT;
      else
        celluar->newstate = tmp;
      break;
      
/******
  2 information (28) 
******/
      /*      neighbour (8) */
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
      
      /*  non-neighbour (20)*/
      /*     1 space (8) */
     case CONVEYOR_UP|CONVEYOR_RIGHT:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_LEFT:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_RIGHT:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        celluar->newstate = tmp;
      else
     case CONVEYOR_DOWN|CONVEYOR_LEFT:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;

      /*     2 space (8) */
     case CONVEYOR_UP|CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_UP_RIGHT:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_UP_RIGHT:
      tmp = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
      
      /*     3 space(opposite) (4) */
     case CONVEYOR_UP|CONVEYOR_DOWN:
      tmp = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_LEFT:
      tmp = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        celluar->newstate = tmp;
      break;
      
      
/******
  3 information (56) 
******/
      /*   full neighbour (8) */
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
      
      /*   2 neighbour (32) */
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
      
      /*  non-neighbour (16) */
      /*    1-1space(8) */
     case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN_LEFT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
      
      /*    2-2space(8) */
     case CONVEYOR_UP|CONVEYOR_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_LEFT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN_LEFT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          celluar->newstate = tmp;
      break;
      
/******
  4 information (70) 
******/
      /*   full neighbour (8) */
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;

      /* 3 neighbour (24)*/
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
      
      /* 2-1-1 neighbour(24) */
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT|CONVEYOR_UP|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT|CONVEYOR_LEFT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN_LEFT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
      
      /* 2-2 neighbour(12) */
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;

     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            celluar->newstate = tmp;
      break;
      
      /* non-neighbour(2) */
     case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            celluar->newstate = tmp;
      break;
      
/******
  5 information (56) 
******/
      /*   full neighbour (8) */
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
      
      
      /*   4 neighbour (16) */
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
      /*   3 neighbour (24) */
      /*    3-2 (16)*/
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_UP_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_UP|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_DOWN_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

       
      /*    3-1-1 (8)*/
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_UP|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
      
      /* 2-2-1 (8) */
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
      CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT|
      CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
      CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT|
      CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;
      
     case CONVEYOR_UP|CONVEYOR_UP_RIGHT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
      CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT|
      CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_LEFT|CONVEYOR_UP_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
      CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

       
     case CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT|CONVEYOR_UP_RIGHT|CONVEYOR_RIGHT|
      CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              celluar->newstate = tmp;
      break;

      
/******
  6 information (28) 
******/
      /*   full neighbour (8) */
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;

       /*   5 neighbour (8) */
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;

       /*   4 neighbour (8) */
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_RIGHT|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_LEFT|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;

       /*   3 neighbour (4) */
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
                celluar->newstate = tmp;
      break;

/******
  7 information (8)
******/
      /* full neighbour(8) */
     case CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|
       CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT:
      tmp  = Cell[pos(celluar->x  ,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|
       CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT:
      tmp  = Cell[pos(celluar->x+1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
                if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|
       CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN:
      tmp  = Cell[pos(celluar->x+1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
                if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT|
       CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT:
      tmp  = Cell[pos(celluar->x+1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
                if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_UP|CONVEYOR_UP_LEFT|CONVEYOR_LEFT|
       CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT:
      tmp  = Cell[pos(celluar->x  ,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
          if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
                if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_UP_LEFT|CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|
       CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT:
      tmp  = Cell[pos(celluar->x-1,celluar->y-1)].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
        if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
                if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|
       CONVEYOR_DOWN_RIGHT|CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP:
      tmp  = Cell[pos(celluar->x-1,celluar->y  )].state;
      if( tmp == Cell[pos(celluar->x-1,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
              if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
                if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
                  celluar->newstate = tmp;
      break;
     case CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
                if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                  celluar->newstate = tmp;
      break;

/******
  8 information (1)
******/
     case CONVEYOR_LEFT|CONVEYOR_DOWN_LEFT|CONVEYOR_DOWN|CONVEYOR_DOWN_RIGHT|
       CONVEYOR_RIGHT|CONVEYOR_UP_RIGHT|CONVEYOR_UP|CONVEYOR_UP_LEFT:
      tmp  = Cell[pos(celluar->x-1,celluar->y+1)].state;
      if( tmp == Cell[pos(celluar->x  ,celluar->y+1)].state )
        if( tmp == Cell[pos(celluar->x+1,celluar->y+1)].state )
          if( tmp == Cell[pos(celluar->x+1,celluar->y  )].state )
            if( tmp == Cell[pos(celluar->x+1,celluar->y-1)].state )
              if( tmp == Cell[pos(celluar->x  ,celluar->y-1)].state )
                if( tmp == Cell[pos(celluar->x-1,celluar->y-1)].state )
                  if( tmp == Cell[pos(celluar->x-1,celluar->y  )].state )
                    celluar->newstate = tmp;
      break;
    }
}  
