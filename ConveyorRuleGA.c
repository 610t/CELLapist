#include "Conveyor.h"

#include "globals.h"

void
  conveyorUpdateCellStateGA(CELL *cell)
{
  extern RuleTbl *ruleT;
  int neighbour;
  
  cell->isUpdated = TRUE;
  neighbour=(conveyorNeighbourState(cell,8,TRUE) >> 2);

  cell->newstate = ruleT[((cell->state & (MASK(6)-1)) << 8) | neighbour];

  cell->newstate &= ~CONVEYOR_SENSOR;
}
