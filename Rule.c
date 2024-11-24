#include <stdio.h>
#include <stdlib.h>
  /* This is temporary code for avoiding "stdlib.h" error*/
#include <math.h>

#undef __CELLapist__

#include "types.h"
#include "Rule.h"
#if defined(__GA_FIX__)
#include "GAFix.h"
#else
#include "GA.h"
#endif

unsigned long signal_mask;
RuleTbl *
#if defined(__GA_FIX__)
  setRule(GenoData *genome)
{
  RuleTbl *rule;
  unsigned long i;

  extern void *xmalloc( size_t );
  void Locus2Rule(RuleTbl *,unsigned char,int);
  void printAllRule(FILE *,RuleTbl *,int);

  rule=(RuleTbl *)xmalloc(sizeof(RuleTbl)*(1 << (genome->states+NEIGHBOUR)));

  for(i=0;i<LOCUS_NUM;i++)
    Locus2Rule(rule,i,genome->locus[i]);

  return(rule);
}
#else /*__GA_FIX__*/
  setRule(GenoData *genome)
{
  Locus *tmp;
  RuleTbl *rule;
  
  extern void *xmalloc( size_t );
  void initRule(RuleTbl *,int);
  void Locus2Rule(RuleTbl *,Locus *,int);
  void printAllRule(FILE *,RuleTbl *,int);
  
  signal_mask = genome->mask;
  rule=(RuleTbl *)xmalloc(sizeof(RuleTbl)*(1 << (genome->states+NEIGHBOUR)));

  initRule(rule,genome->states);

  tmp=genome->head;
  while(tmp!=NULL)
  {
    Locus2Rule(rule,tmp,genome->states);
    tmp=tmp->next;
  }
/*  printAllRule(stdout,rule,genome->states); */
  return(rule);
}
#endif

#if defined(__GA_FIX__)
void
  Locus2Rule(RuleTbl *rule,unsigned char state,int pos)
{
  rule[pos] = state;
}
#else /* __GA_FIX__ */
#if defined(__GA_ROTATE__)
#include "Conveyor.h"
void
  RealLocus2Rule(RuleTbl *rule,Locus *loc,int state_num)
{
  int i,neighbour,next_state,state;

  int bitcount(unsigned long,int);
  void printRule(FILE *,RuleTbl *,unsigned long ,int );
  void LocusPrint(FILE *,Locus *,unsigned long);
  long GetRealState(long,long);
  long GetRealNeighbour(long,long);
  
  loc->wildcard = 0;
/*
  fprintf(stderr,"Locus:");
  LocusPrint(stderr,loc,6);

  fprintf(stderr,"Rule:\n");
 */
  for(i=CONVEYOR_UP;i<CONVEYOR_BROKEN;i<<=1)
  {
    state = GetRealState(i,(loc->bit >> NEIGHBOUR));
    neighbour = GetRealNeighbour(i,(loc->bit & ((1 << NEIGHBOUR) - 1)));
    next_state = GetRealState(i,loc->state);
    
    rule[((state << NEIGHBOUR) | neighbour)] = next_state;
/*
    printRule(stderr,rule,((state << NEIGHBOUR) | neighbour),state_num);
 */
  }
}

long
  GetRealState(long self,long state)
{
  long real=0;

  real = state & ((1 << 2) - 1);

  switch(self)
  {
  case CONVEYOR_UP:
    if( (state & CONVEYOR_UP) != 0 )
      real |= CONVEYOR_UP;
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_DOWN;
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_RIGHT;
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= CONVEYOR_LEFT;
    break;
  case CONVEYOR_DOWN:
    if( (state & CONVEYOR_UP) != 0 )
      real |= CONVEYOR_DOWN;
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_UP;
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_LEFT;
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= CONVEYOR_RIGHT;
    break;
  case CONVEYOR_RIGHT:
    if( (state & CONVEYOR_UP) != 0 )
      real |= CONVEYOR_RIGHT;
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_LEFT;
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_DOWN;
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= CONVEYOR_UP;
    break;
  case CONVEYOR_LEFT:
    if( (state & CONVEYOR_UP) != 0 )
      real |= CONVEYOR_LEFT;
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_RIGHT;
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_UP;
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= CONVEYOR_DOWN;
    break;
  case CONVEYOR_UP_RIGHT:
    if( (state & CONVEYOR_UP) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_RIGHT);
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_LEFT);
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_RIGHT);
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_LEFT);
    break;
  case CONVEYOR_DOWN_RIGHT:
    if( (state & CONVEYOR_UP) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_RIGHT);
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_LEFT);
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_LEFT);
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_RIGHT);
    break;
  case CONVEYOR_UP_LEFT:
    if( (state & CONVEYOR_UP) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_LEFT);
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_RIGHT);
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_RIGHT);
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_LEFT);
    break;
  case CONVEYOR_DOWN_LEFT:
    if( (state & CONVEYOR_UP) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_LEFT);
    if( (state & CONVEYOR_DOWN) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_RIGHT);
    if( (state & CONVEYOR_RIGHT) != 0 )
      real |= (CONVEYOR_UP | CONVEYOR_LEFT);
    if( (state & CONVEYOR_LEFT) != 0 )
      real |= (CONVEYOR_DOWN | CONVEYOR_RIGHT);
    break;
  }

  return(real);
}

long
  GetRealNeighbour(long self,long neighbour)
{
  long real=0;

  neighbour <<= 2;
  
  switch(self)
  {
  case CONVEYOR_UP:
    real = CONVEYOR_UP;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_DOWN;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
       real |= CONVEYOR_RIGHT;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_LEFT;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
      real |= CONVEYOR_UP_RIGHT;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_UP_LEFT;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    break;
  case CONVEYOR_DOWN:
    real = CONVEYOR_DOWN;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_UP;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_LEFT;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_RIGHT;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
      real |= CONVEYOR_UP_LEFT;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_UP_RIGHT;
    break;
  case CONVEYOR_RIGHT:
    real = CONVEYOR_RIGHT;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_LEFT;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_DOWN;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_UP;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_UP_RIGHT;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_UP_LEFT;
    break;
  case CONVEYOR_LEFT:
    real = CONVEYOR_LEFT;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_RIGHT;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_UP;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_DOWN;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
       real |= CONVEYOR_UP_LEFT;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
       real |= CONVEYOR_UP_RIGHT;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    break;
  case CONVEYOR_UP_RIGHT:
    real = CONVEYOR_UP_RIGHT;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_UP_LEFT;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
       real |= CONVEYOR_RIGHT;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
       real |= CONVEYOR_DOWN;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_UP;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_LEFT;
    break;
  case CONVEYOR_DOWN_LEFT:
    real = CONVEYOR_DOWN_LEFT;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_UP_RIGHT;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_UP_LEFT;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
       real |= CONVEYOR_LEFT;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
       real |= CONVEYOR_UP;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_DOWN;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_RIGHT;
    break;
  case CONVEYOR_DOWN_RIGHT:
    real = CONVEYOR_DOWN_RIGHT;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_UP_LEFT;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_UP_RIGHT;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
       real |= CONVEYOR_DOWN;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
       real |= CONVEYOR_LEFT;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_RIGHT;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_UP;
    break;
  case CONVEYOR_UP_LEFT:
    real = CONVEYOR_UP_LEFT;
    if( (neighbour  & CONVEYOR_DOWN) != 0 )
      real |= CONVEYOR_DOWN_RIGHT;
    if( (neighbour & CONVEYOR_RIGHT) != 0 )
      real |= CONVEYOR_UP_RIGHT;
    if( (neighbour  & CONVEYOR_LEFT)   != 0 )
      real |= CONVEYOR_DOWN_LEFT;
    if( (neighbour  & CONVEYOR_UP_RIGHT) != 0 )
       real |= CONVEYOR_UP;
    if( (neighbour & CONVEYOR_DOWN_RIGHT) != 0 )
       real |= CONVEYOR_RIGHT;
    if( (neighbour  & CONVEYOR_UP_LEFT) != 0 )
      real |= CONVEYOR_LEFT;
    if( (neighbour & CONVEYOR_DOWN_LEFT) != 0 )
      real |= CONVEYOR_DOWN;
    break;
  }
  return(real>>2);
}
#endif /* __GA_ROTATE__ */
void
  Locus2Rule(RuleTbl *rule,Locus *loc,int state)
{
  int i,j,k,bits,count;
  unsigned long code;
#if defined(__GA_ROTATE__)
  Locus tmp;

  void RealLocus2Rule(RuleTbl *,Locus *,int state);
#endif

  int bitcount(unsigned long,int);
  void printRule(FILE *,RuleTbl *,unsigned long ,int );
  
  bits=bitcount(loc->wildcard,state+NEIGHBOUR);
  
  for(i=0;i<MASK(bits);i++)
  {
    code = loc->bit & ~(loc->wildcard);

    for(j=0;j<bits;j++)
    {
      if( (i & MASK(j)) != 0 )
      {
        count=0;
        for(k=0;k<state+NEIGHBOUR && count <= j;k++)
          if((loc->wildcard & MASK(k))!=0) count++;
        code |= (1 << (k-1));
      }
    } 
#if defined(__GA_ROTATE__)
    tmp.wildcard = 0;
    tmp.bit = code;
    tmp.state = loc->state;
    RealLocus2Rule(rule,&tmp,state);
#else
    rule[code] = loc->state;
#endif
/*    printRule(stderr,rule,code,state);*/
  }
}
#endif

int bitcount(unsigned long data,int length)
{
  unsigned long tmp;
  int count=0,i;
  
  for(i=0;i<length;i++)
    if( ( data & MASK(i) ) != 0 ) count++;

  return(count);
}

#if !defined(__GA_FIX__)
void
  initRule(RuleTbl *rule,int state)
{
  unsigned long tmp;
  int i,j;
  
  for(i=0;i<(1 << state);i++)
  {
    tmp = i << NEIGHBOUR;
    for(j=0;j<(1 << NEIGHBOUR);j++)
    {
      rule[tmp|j] = i;
    }
  }
}
#endif

void
  loadAllRule(FILE *fp,RuleTbl *rule,int state)
{
  int i;
  
  void loadARule(FILE *,RuleTbl *,unsigned long ,int );

  for(i=0;i<(1 << (state + NEIGHBOUR) );i++)
  {
    loadARule(fp,rule,i,state);
  }
}


void
  printAllRule(FILE *fp,RuleTbl *rule,int state)
{
  unsigned long i;

  void printRule(FILE *,RuleTbl *,unsigned long ,int );
  
  for(i=0;i<(1 << (state + NEIGHBOUR) );i++)
  {
    printRule(fp,rule,i,state);
  }
}

void
  loadARule(FILE *fp,RuleTbl *rule,unsigned long rule_num,int state)
{
  unsigned long inner_state;
  unsigned long j;
  int flag=TRUE;
  char c[2];
  
  void loadBinary(FILE *,unsigned long *,int);

  /* skip right hand */
  while(flag==TRUE)
  {
    fscanf(fp,"%1s",&c);
    switch(c[0])
    {
    case '>':
      flag=FALSE;
      break;
    default:
      break;
    }      
  }     

  /* read transition */
  loadBinary(fp,&(rule[rule_num]),state);
}

void
  printRule(FILE *fp,RuleTbl *rule,unsigned long rule_num,int state)
{
  unsigned long j;

  void printBinary(FILE *,unsigned long,int);
  
  printBinary(fp,(rule_num>>NEIGHBOUR),state);
  fprintf(fp,":");
  printBinary(fp,rule_num,NEIGHBOUR);

  fprintf(fp,"->");

  printBinary(fp,rule[rule_num],state);
  fprintf(fp,"\n");
}

void 
  printBinary(FILE *fp,unsigned long num,int length)
{
  int i;
  
  for(i=0;i<length;i++)
  {
    if( (MASK(length-i-1) & num) !=0 )
      fprintf(fp,"1");
    else
      fprintf(fp,"0");
  }
}

void
  loadBinary(FILE *fp,unsigned long *num,int length)
{
  int i;
  char c[2];
  
  *num=0;
  
  for(i=0;i<length;i++)
  {
    fscanf(fp,"%1s",&c);
    switch(c[0])
    {
    case '0':
      break;
    case '1':
      *num |= MASK(length-i-1);
      break;
    default:
      fprintf(stderr,"%c is not a binary\n",c);
      break;
    }
  }  
}


RuleTbl *
  loadRule(FILE *fp)
{
  extern unsigned long signal_mask;
  int length;
  RuleTbl *rule;
  
  extern void *xmalloc( size_t );

  fscanf(fp,"%d",&length);
  loadBinary(fp,&(signal_mask),length);
  rule=  (RuleTbl *)xmalloc(sizeof(RuleTbl)*(1 << (length+NEIGHBOUR)));
  loadAllRule(fp,rule,length);
  return(rule);
}

#if !defined(__GA_FIX__)
void
  SaveRule(char *filename,RuleTbl *rule,GenoData *genome)
{
  FILE *fp;

  if((fp = fopen(filename,"w"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    return;
  }
  fprintf(fp,"%d\n",genome->states);
  printBinary(fp,genome->mask,genome->states);
  fprintf(fp,"\n");
  printAllRule(fp,rule,genome->states);
  fclose(fp);
}
#endif

void *xmalloc( size_t size )
{
  void *ptr = NULL;
  
  if( (ptr = malloc(size)) == NULL )
  {
    fprintf(stderr,"Memory can't allocate.\n");
    exit(1);
  }
  return(ptr);
}
