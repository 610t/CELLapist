#include "Pattern.h"

#include "globals.h"
  
pattern_score patternNeighbourState(CELL *);

  void patternUpdateCellState(CELL *celluar)
{
  pattern_score neighbour;
  int direction;
  int max_num=0,max_count=0;
  
  celluar->isUpdated = TRUE;

  if(celluar->state == PATTERN_CONTROL)
    {
      celluar->newstate = celluar->state;
      return;
    }  
  neighbour=patternNeighbourState(celluar);

  if(neighbour.up > max_num)
    {
      max_num=neighbour.up;
      direction=PATTERN_UP;
      max_count=0;
    }
  else if(neighbour.up==max_num)
    {
      max_count++;
    }
    
  if(neighbour.down>max_num)
    {
      max_num=neighbour.down;
      direction=PATTERN_DOWN;
      max_count=0;
    }
  else if(neighbour.down==max_num)
    {
      max_count++;
    }

  if(neighbour.right>max_num)
    {
      max_num=neighbour.right;
      direction=PATTERN_RIGHT;
      max_count=0;
    }
  else if(neighbour.right==max_num)
    {
      max_count++;
    }

  if(neighbour.left>max_num)
    {
      max_num=neighbour.left;
      direction=PATTERN_LEFT;
      max_count=0;
    }
  else if(neighbour.left==max_num)
    {
      max_count++;
    }

  if(max_num!=0 && max_count==0)
    celluar->newstate=direction;
  else
    celluar->newstate=celluar->state;
}  
