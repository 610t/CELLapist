#include "Rho.h"

#include "globals.h"

void
  rhoUpdateCellStateGA(CELL *cell)
{
  extern RuleTbl *ruleT;
  int neighbour;

  extern printAllRule(FILE *,RuleTbl *,int);
  
  cell->isUpdated = TRUE;
  neighbour=rhoNeighbourState(cell,8,TRUE);

/*
  fprintf(stderr,"%x->%x:",(cell->state & 1) | neighbour,ruleT[ (cell->state & 1) | neighbour]);
 */
  cell->newstate = ruleT[ (cell->state & 1) | neighbour];
}
