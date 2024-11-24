#include "Conveyor.h"

#include "globals.h"

#define MY_RAND(x,y) ((((rand()%10001)/10000.0)>=0.5)?(x):(y))
                      
void conveyorUpdateCellState4Rand(CELL *celluar)
{
  int neighbour,neighbour_state;
  
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

  neighbour=conveyorNeighbourState(celluar,4,FALSE);
  
#ifdef __CELLapist__
  if(neighbour)
    celluar->color=1;
#endif /* __CELLapist */

  switch(neighbour)
    {
/* from 1-direction */
        case CONVEYOR_UP:
      celluar->newstate = CONVEYOR_UP;
      break;
        case CONVEYOR_DOWN:
      celluar->newstate = CONVEYOR_DOWN;
      break;
        case CONVEYOR_RIGHT:
      celluar->newstate = CONVEYOR_RIGHT;
      break;
        case CONVEYOR_LEFT:
      celluar->newstate = CONVEYOR_LEFT;
      break;

/* from 2-direction */
        case CONVEYOR_UP|CONVEYOR_DOWN:
      celluar->newstate = MY_RAND(CONVEYOR_UP,CONVEYOR_DOWN);
      break;
        case CONVEYOR_RIGHT|CONVEYOR_LEFT:
      celluar->newstate = MY_RAND(CONVEYOR_RIGHT,CONVEYOR_LEFT);
      break;

        case CONVEYOR_UP|CONVEYOR_RIGHT:
      celluar->newstate = MY_RAND(CONVEYOR_UP,CONVEYOR_RIGHT);
      break;
        case CONVEYOR_UP|CONVEYOR_LEFT:
      celluar->newstate = MY_RAND(CONVEYOR_LEFT,CONVEYOR_UP);
      break;
        case CONVEYOR_DOWN|CONVEYOR_RIGHT:
      celluar->newstate = MY_RAND(CONVEYOR_RIGHT,CONVEYOR_DOWN);
      break;
        case CONVEYOR_DOWN|CONVEYOR_LEFT:
      celluar->newstate = MY_RAND(CONVEYOR_DOWN,CONVEYOR_LEFT);
      break;

/* from 3-direction */
        case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT:
      celluar->newstate = CONVEYOR_RIGHT;
      break;
        case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_LEFT:
      celluar->newstate = CONVEYOR_LEFT;
      break;
        case CONVEYOR_UP|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      celluar->newstate = CONVEYOR_UP;
      break;
        case CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      celluar->newstate = CONVEYOR_DOWN;
      break;

/* from 4-direction */
        case CONVEYOR_UP|CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
      celluar->newstate
        = MY_RAND(
                  MY_RAND(CONVEYOR_DOWN,CONVEYOR_UP),
                  MY_RAND(CONVEYOR_RIGHT,CONVEYOR_LEFT));
      break;
    }
}  
