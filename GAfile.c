#include <stdio.h>
/* #include <stdlib.h>*/
#include <math.h>

#include "getline.h"

#include "GA.h"
#include "Rule.h"

typedef struct _LinkHead
{
  void *top;
  void *tail;
} LinkHead;

void
  GenomePrintAll(Genome **gene,int pops,int epoch)
{
  static float epoch_max=0.0;
  int i;
  Genome *tmp;
  float max_fit = 0.0;
  int max_num   = 0;
  int max_flag;
  char f_name[256];
  
  void GenomePrint(GenoData *);
  void GenomeSave(char *,GenoData *);

  for(i=0;i<pops;i++)
  {
    printf("# Gene:%d ",i);
    GenomePrint(gene[i]->data);
    if( max_fit < REAL_FITNESS(gene[i]->data))
    {
      max_fit = REAL_FITNESS(gene[i]->data);
      max_num = i;
    }
  }

  fprintf(stderr,"******maxfit %f,epochmax %f*****",max_fit,epoch_max);
  max_flag=FALSE;
  if( max_fit > epoch_max )
  {
    epoch_max=max_fit;
    max_flag=TRUE;
  }
  
  if( (epoch % 10)==0 || max_flag == TRUE )
  {
    sprintf(f_name,"%08d-MF.gene",epoch);
    GenomeSave(f_name,gene[max_num]->data);
  }      
}

void
  GenomePrint(GenoData *data)
{
  printf(" F(%f) L(%d) T(%d)\n"
         ,REAL_FITNESS(data),data->geno_length,data->lifetime);
}

void
  LocusPrint( FILE *fp,Locus *loc,unsigned long length )
{
  unsigned long i;
  extern void printBinary(FILE *,unsigned long,int);
  
  /* print left hand */
  for(i=0;i<length+NEIGHBOUR;i++)
  {
    if(i==length) fprintf(fp,":");
    if(MASK(length+NEIGHBOUR - i - 1) & loc->wildcard)
      fprintf(fp,"*");
    else
      printBinary(fp,(loc->bit >> (length + NEIGHBOUR - i - 1)),1);
  }
  fprintf(fp,"->");
  printBinary(fp,loc->state,length);
  fprintf(fp,"\n");
}

void
  LocusPrintAll( FILE *fp,GenoData *genome )
{
  Locus *tmp;

  tmp = genome->head;
  while(tmp!=NULL)
  {
    LocusPrint(fp,tmp,genome->states);
    tmp=tmp->next;
  }
}

void LocusLoad(FILE *fp,LinkHead *ent,int length)
{
  int i,count;
  char c[2];
  unsigned long wildcard=0,bit=0,state=0;
  Locus *link;
  void printBinary(FILE *,unsigned long,int);
  
  
  /* load left hand */
  for(i=0,count=0;i<length+NEIGHBOUR+3;i++,count++)
  {
    fscanf(fp,"%1s",c);
    switch(c[0])
    {
    case '0':
      break;
    case '1':
      bit |= MASK(length+NEIGHBOUR - count - 1);
      break;
    case '*':
      wildcard |= MASK(length+NEIGHBOUR - count - 1);
      break;
    case ':':
      count--;
    case '-':
    case '>':
      break;
    default:
      fprintf(stderr,"%c is not genome character(LHE).\n",c[0]);
      break;
    }
  }

  /* load right hand */
  for(i=0;i<length;i++)
  {
    fscanf(fp,"%1s",c);
    switch(c[0])
    {
    case '0':
      break;
    case '1':
      state |= MASK(length - i - 1);
      break;
    default:
      fprintf(stderr,"%c is not genome character(RHE).\n",c[0]);
      break;
    }    
  }

  /* set locus */
  link=(Locus *)xmalloc(sizeof(Locus));
  link->wildcard = wildcard;
  link->bit = bit;
  link->state = state;
  link->next = NULL;
  appendLocus(ent,link);
}

void
  LocusLoadAll( FILE *fp,GenoData *genome )
{
  Locus *tmp;
  int i;
  LinkHead ent;
  
  ent.tail=ent.top=genome->head=NULL;
  for(i=0;i<genome->geno_length;i++)
  {
    LocusLoad(fp,&ent,genome->states);
  }
  genome->head = ent.top;
}

void GenomeSave(char *filename,GenoData *genome)
{
  FILE *fp;
  void printBinary(FILE *,unsigned long,int);
  
  if((fp = fopen(filename,"w"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    exit(1);
  }
  fprintf(fp,"%d %d\n",genome->states,genome->geno_length);
  printBinary(fp,genome->mask,genome->states);
  fprintf(fp,"\n");
  LocusPrintAll(fp,genome);
  fclose(fp);
}

void GenomeLoad(char *filename,GenoData *genome)
{
  FILE *fp;
  
  if((fp = fopen(filename,"r"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    exit(0);
  }

  sscanf( my_getline(fp) ,"%d %d",&(genome->states),&(genome->geno_length));

/*
  fscanf(fp,"%d %d",&(genome->states),&(genome->geno_length));
 */
  /*  fprintf(stderr,"%d %d\n",genome->states,genome->geno_length); */
  loadBinary(fp,&(genome->mask),genome->states);
  LocusLoadAll(fp,genome);
  fclose(fp);
}
