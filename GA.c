#include <stdio.h>
/* #include <stdlib.h>*/
#include <math.h>

#if defined( __CELLapist__ )
#include "X_include.h"
#endif /* __CELLapist */

#include "types.h"
#include "GA.h"
#include "Rule.h"

typedef struct _LinkHead
{
  void *top;
  void *tail;
} LinkHead;

extern RuleTbl *ruleT;

extern float get_fitness(GenoData *);
extern void LocusPrint( FILE *,Locus *,unsigned long );
extern void LocusPrintAll( FILE *,GenoData * );
extern void *xmalloc(size_t);

void
  deleteLocus( Locus *tmp )
{
  Locus *next;
  
  for( tmp = tmp->next; tmp != NULL;)
  {
    next = tmp->next;
    free(tmp);
    tmp = next;
  }
}


void
  appendLocus(LinkHead *ent,Locus *link)
{
  Locus *top  = (Locus*)ent->top;
  Locus *tail = (Locus*)ent->tail;
  
  if( ent->top == NULL )
  {
    ent->tail=ent->top=link;
  }
  else
    ((Locus*)ent->tail)->next=link;
  ent->tail=link;
  ((Locus*)ent->tail)->next = NULL;
}

#if !defined( __CELLapist__ )
int
  Locus_init(GenoData *data,unsigned long bits)
{
  int i,length;
  Locus *link;
  LinkHead ent;

  ent.top=NULL;
  
/*  length=(rand() % ((1<<MAX_GENOME_LENGTH)-1)) +1; */
  length = MIN_GENOME_LENGTH;
  
  for(i=0;i<length;i++)
  {
    link=(Locus *)xmalloc(sizeof(Locus));

    link->bit           = rand() % ( (1<<(bits+NEIGHBOUR))-1 );
    link->wildcard      = rand() % ( (1<<(bits+NEIGHBOUR))-1 );
    link->state         = rand() % ( (1<<(bits))-1 );
    
    appendLocus(&ent,link);
  }

  data->head = ent.top;
  
  return(length);
}

float
  Genome_data_init(Genome *gene)
{
  GenoData *data;
  
  data = gene->data = (GenoData *)xmalloc(sizeof(GenoData));
  
  data->mask          = rand() % ((1 << STATE_NUM) -1 );
  data->states        = STATE_NUM;
  data->head          = NULL;
  data->geno_length   = Locus_init(data,data->states);
  data->total_fitness = get_fitness(data);
  data->lifetime      = 1;

  return(REAL_FITNESS(data));
}

Genome **
  Genome_init( int pops, int flag )
{
  int i;
  Genome **gene=NULL;
  Genome *link;
  
  void Genome_remove( Genome **, unsigned long );

  if(pops < 1)
  {
    fprintf(stderr,"No populations.\n");
    exit(1);
  }
  
  gene=(Genome **)xmalloc(sizeof(Genome*) * pops);

  for(i=0;i<pops;i++)
  {
    gene[i] = (Genome *)xmalloc(sizeof(Genome));
    if(flag == TRUE)
    {
      gene[i]->isDead = FALSE;
#if defined( __PUTaLOAD__ )|| defined( __FixedTarget__ )
      Genome_data_init(gene[i]);
#else
      while( Genome_data_init(gene[i]) == 0.0 )
      {
        Genome_remove( gene ,i );
      }
#endif /* !__PUTaLOAD__ */
    }
    else
    {
      gene[i]->isDead = TRUE;
    }
  }

  return(gene);
}

void
  Locus_remove( GenoData *data )
{
  Locus *tmp;
  
  for(tmp = data->head; tmp != NULL;)
  {
    data->head = tmp->next;
    free(tmp);
    tmp=data->head;
  }
}

void
  Genome_remove( Genome **gene, unsigned long i )
{
  Locus_remove( gene[i]->data );
  
  free(gene[i]->data);
}

Locus *
  Genome_copy_part(Locus *source,unsigned long length)
{
  Locus *object;
  Locus *tmp_so,*tmp_obj;
  Locus *tmp;
  unsigned long i=1;

  if(source == NULL)
    return((Locus *)NULL);

  object = (Locus *)xmalloc(sizeof(Locus));
  tmp_obj = object;
  while( source!=NULL && i < length )
  {
    /* Data Copy */
    tmp_obj->wildcard   = source->wildcard;
    tmp_obj->bit        = source->bit;
    tmp_obj->state      = source->state;

    /* Locus inclement */
    source = source->next;

    if(source != NULL)
      tmp_obj->next = (Locus *)xmalloc(sizeof(Locus));
    else
      tmp_obj->next = NULL;

    tmp_obj = tmp_obj->next;
    i++;
  }
  /* Last data copy */
  if(source != NULL)
  {
    tmp_obj->wildcard   = source->wildcard;
    tmp_obj->bit        = source->bit;
    tmp_obj->state      = source->state;
  }
  tmp_obj->next = NULL;

  return(object);
}


GenoData *
  Genome_copy(GenoData *source)
{
  GenoData *object;
  Locus *tmp_so,*tmp_obj;
  
  if(source == NULL) 
    return((GenoData *)NULL);

  object = (GenoData *)xmalloc(sizeof(GenoData));
  object->mask          = source->mask;
  object->geno_length   = source->geno_length;
  object->states        = source->states;
  object->total_fitness = source->total_fitness;
  object->lifetime      = source->lifetime;
  
  tmp_obj = object->head = (Locus *)xmalloc(sizeof(Locus));

  tmp_so  = source->head;
  while(tmp_so != NULL)
  {
    /* Data Copy */
    tmp_obj->wildcard   = tmp_so->wildcard;
    tmp_obj->bit        = tmp_so->bit;
    tmp_obj->state      = tmp_so->state;

    /* Locus inclement */
    tmp_so = tmp_so->next;

    if(tmp_so != NULL)
      tmp_obj->next = (Locus *)xmalloc(sizeof(Locus));
    else
      tmp_obj->next = NULL;

    tmp_obj = tmp_obj->next;
  }

  return(object);
}

unsigned long
  worstGenome( Genome **gene ,int pops)
{
  int i,min_no=0,tmp_no=0;
  int min_life=~0;
  float min_fit = OVER_FITNESS;
  float tmp_fit = OVER_FITNESS;

  for(i=0;i<pops;i++)
    if( gene[i]->isDead == FALSE )
    {
      if( min_fit > REAL_FITNESS(gene[i]->data) )
      {
        min_no = i;
        min_fit = REAL_FITNESS(gene[i]->data);
      }
    }
  
/*
      if( gene[i]->data->lifetime > LEAST_LIFETIME )
      {
        if( min_fit > REAL_FITNESS(gene[i]->data) )
        {
          min_no = i;
          min_fit = REAL_FITNESS(gene[i]->data);
        }
      }
      else
      {
        if( tmp_fit > REAL_FITNESS(gene[i]->data) )
        {
          tmp_no        = i;
          tmp_fit       = REAL_FITNESS(gene[i]->data);
          min_life      = gene[i]->data->lifetime;
        }
        else if( tmp_fit == REAL_FITNESS(gene[i]->data)
                && min_life > gene[i]->data->lifetime )
        {
          tmp_no        = i;
          min_life      = gene[i]->data->lifetime;
        }
      }      
  if( min_fit == OVER_FITNESS )
    min_no = tmp_no;
  else if( min_fit > tmp_fit )
    min_no = tmp_no;
*/
  return(min_no);
}

void
  Genome_delete( Genome **gene ,int num,int pops )
{
  int i;
  int worst;

  /* Delete bad num genomes */
  for( i=0;i<num;i++ )
  {
    worst = worstGenome( gene ,pops );
    Genome_remove( gene, worst );
    gene[worst]->isDead = TRUE;
  }
}

int
  Genome_add( Genome **gene, GenoData *new_gene, int pops )
{
  int i;
  Locus *tmp;

  for(i=0;i<pops && gene[i]->isDead == FALSE;i++) 
    ; /* get Dead gene */
  gene[i]->data                 = new_gene;
  gene[i]->isDead               = FALSE;
  printf("# S:%d(%f)\n",i,REAL_FITNESS(gene[i]->data));

  return(i);
}

void
  Genome_crossover( Genome **gene ,int pops )
{
  int num;
  GenoData *son1,*son2;
  LinkHead ent;
  unsigned long i,j,min_no;
  float min_fit;
  
  void crossing(GenoData *,GenoData *);

  /* Make crossover children */
  /* Get papa */
  do
  {
    i=rand()%(pops);
  } while(gene[i]->isDead==TRUE);
  son1 = Genome_copy( gene[i]->data );
  printf("#CB D:%d(%f) ",i,REAL_FITNESS(gene[i]->data) );
  
  /* Get mama */
  do
  {
    i=rand()%(pops);
  } while(gene[i]->isDead==TRUE);
  son2 = Genome_copy( gene[i]->data );
  printf("M:%d(%f)\n",i,REAL_FITNESS(gene[i]->data));
  
  crossing( son1,son2 );
  
  num = Genome_add( gene, son1, pops );
  gene[num]->data->total_fitness  = get_fitness(gene[num]->data);
  gene[num]->data->lifetime       = 1;

  num = Genome_add( gene, son2, pops );
  gene[num]->data->total_fitness  = get_fitness(gene[num]->data);
  gene[num]->data->lifetime       = 1;
}

void
  crossing(GenoData *papa,GenoData *mama)
{
  int papa_cut,mama_cut;
  int i,j;
  Locus *papa_tmp,*mama_tmp,*tmp;
  void crossLocus(Locus *,Locus *,int);

  /* crossing locus */
  papa_cut = rand() % papa->geno_length;
  papa_tmp=papa->head;
  for(i=1;i<papa_cut;i++)
    papa_tmp=papa_tmp->next;
  
  mama_cut = rand() % mama->geno_length;
  mama_tmp=mama->head;
  for(i=1;i<mama_cut;i++)
    mama_tmp=mama_tmp->next;

  /* caluculate new lengthes */
  j = papa_cut + mama->geno_length - mama_cut;
  mama->geno_length = mama_cut + papa->geno_length - papa_cut;
  papa->geno_length = j;

  if( papa_cut == 0 )
  {
    if( mama_cut == 0 )
    {
      tmp        = papa->head;
      papa->head = mama->head;
      mama->head = tmp;
    }
    else
    {
      tmp            = mama_tmp->next;
      mama_tmp->next = papa->head;
      papa->head     = tmp;
    }
  } 
  else if( mama_cut == 0 )
  {
    tmp            = mama->head;
    mama->head     = papa_tmp->next;
    papa_tmp->next = tmp;
  }
  else  
  {
    tmp           =papa_tmp->next;
    papa_tmp->next=mama_tmp->next;
    mama_tmp->next=tmp;
  }
  
  crossLocus(papa_tmp,mama_tmp,papa->states);
}

void
  crossLocus(Locus *papa,Locus *mama,int state)
{
  int cutpoint;
  unsigned long mask;
  unsigned long papa_code ,mama_code;
  
  cutpoint = rand() % (2 * state + NEIGHBOUR + 1);
  
  if(cutpoint < state + NEIGHBOUR) /* cut at left hands */
  {
    mask = ((1 << (cutpoint)) - 1) << (state+NEIGHBOUR-cutpoint);

    /* for wildcard */
    papa_code = (papa->wildcard &  mask) | (mama->wildcard & ~mask);
    mama_code = (papa->wildcard & ~mask) | (mama->wildcard &  mask);
    papa->wildcard = papa_code;
    mama->wildcard = mama_code;
  
    /* for bits */
    papa_code = (papa->bit &  mask) | (mama->bit & ~mask);
    mama_code = (papa->bit & ~mask) | (mama->bit &  mask);
    papa->bit = papa_code;
    mama->bit = mama_code;

    papa_code = papa->state;
    papa->state = mama->state;
    mama->state = papa_code;
  }
  else /* cut at right hands */
  {
    mask = ((1 << (cutpoint-(state+NEIGHBOUR))) - 1) 
             << (state - (cutpoint-(state+NEIGHBOUR)));
    /* for state */
    papa_code = (papa->state &  mask) | (mama->state & ~mask);
    mama_code = (papa->state & ~mask) | (mama->state &  mask);
    papa->state = papa_code;
    mama->state = mama_code;
  }
}

void
  deficiency( GenoData *son )
{
  Locus *pre,*post;
  Locus *tmp;
  unsigned long head,tail,count=1;
  int i;
  
  head = rand() % ( son->geno_length );

  if( head != 0 )
  {
    tail = rand() % ( son->geno_length - head ) + 1 ;
    for(pre=son->head; count<head; pre=pre->next,count++)
      ; /* NULL line */
    for(post=pre;count<(head+tail); post=post->next,count++)
      ; /* NULL line */

    if( post != NULL )
    {
      tmp=pre->next;
      pre->next = post->next;
    }
    else
    {
      fprintf(stderr,"Is it okay?\n");
      tmp=pre;
      pre->next = NULL;
    }
  }
  else
  {
    tail = rand() % ( son->geno_length - head - 1 ) + 1;
    for(post=son->head; count<tail; post=post->next,count++)
      ; /* NULL line */

    tmp=son->head;
    if( post != NULL )
    {      
      son->head = post->next;
    }
    else
    {
      fprintf(stderr,"Is it okay?\n");
      son->head = NULL;
    }
  }

  if( post != NULL)
  {
    post->next = NULL;
  }
  
  /* Delete locus */
  deleteLocus( tmp );

  son->geno_length -= tail;
}

void
  Genome_deficiency( Genome **gene , int pops )
{
  int i;
  GenoData *son;
  int num;
  Locus *tmp;
  
  /* select deficiency genome */
  do
  {
    i=rand()%(pops);
  } while(gene[i]->isDead==TRUE);
  son = Genome_copy( gene[i]->data );

  deficiency( son );
  
  /* Add new genome */
  num = Genome_add( gene, son, pops );
  gene[num]->data->total_fitness  = get_fitness(gene[num]->data);
  gene[num]->data->lifetime       = 1;
}

void
  duplicate( GenoData *son )
{
  Locus *pre,*part,*tmp,*insp;
  unsigned long head,tail,ins,count=1;
  int i;
  
  head = rand() % ( son->geno_length  );
  tail = rand() % ( son->geno_length - head ) + 1;
  
  for(pre=son->head; count<head && pre!=NULL;pre=pre->next,count++)
    ; /* NULL line */

  /* Copy part */
  part = Genome_copy_part( pre , tail );

  ins = rand() % (son->geno_length + 1);
  if(ins != 0)
  {
    /* Search insert position by insp */
    for(insp=son->head,count=1;
        count<ins && insp!=NULL;insp=insp->next,count++)
      ; /* NULL line */
    tmp=insp->next;
    insp->next=part;
  }
  else
  {
    tmp=son->head;
    son->head=part;
  }

  for(;part->next!=NULL;part=part->next)
    ;

  part->next=tmp;
  
  son->geno_length += tail;
}

void
  Genome_duplicate( Genome **gene , int pops )
{
  int i;
  int num;
  GenoData *son;
  
  /* select duplicate genome */
  do
  {
    i=rand()%(pops);
  } while(gene[i]->isDead==TRUE);
  son = Genome_copy( gene[i]->data );

  duplicate( son );
  
  /* Add new genome */
  num = Genome_add( gene, son, pops );
  gene[num]->data->total_fitness  = get_fitness(gene[num]->data);
  gene[num]->data->lifetime       = 1;
}

void
  Genome_rotation( Genome **gene ,int pops )
{
  Genome *source,*tmp;
  GenoData *son;
  int i;
  int num;
  
  void rotate(GenoData *);

  /* select rotation genome */
  do
  {
    i=rand()%(pops);
  } while(gene[i]->isDead==TRUE);
  son = Genome_copy( gene[i]->data );
  printf("#R D:%d(%f) ",i,REAL_FITNESS(gene[i]->data));
  
  rotate( son );

  /* Add new genome */
  num = Genome_add( gene, son, pops );
  gene[num]->data->total_fitness  = get_fitness(gene[num]->data);
  gene[num]->data->lifetime       = 1;
}

void
  rotate(GenoData *son)
{
  Locus *tmp;
  void rotateLocus(Locus *,int,int);
  int shiftnum;

  shiftnum = rand()%7+1;

  for(tmp=son->head;tmp!=NULL;tmp=tmp->next)
    rotateLocus(tmp,son->states,shiftnum);
}

void 
  rotateLocus(Locus *locus,int length,int snum)
{
  float rnd;
  int i;
  unsigned long m_wild=0,m_bit=0,m_state=0,m_tmp;
  unsigned long source,object;
  
  /* for wildcard */
  source = locus->wildcard & ( (1 << NEIGHBOUR) -1 );
  object = (((source << snum) |(source >> (NEIGHBOUR - snum)))
            & ( (1 << NEIGHBOUR) -1 ));
  locus->wildcard = (locus->wildcard & 
                     (((1<<NEIGHBOUR+length)-1)^((1<<NEIGHBOUR)-1))
                     | object);

  /* for bit */
  source = locus->bit & ( (1 << NEIGHBOUR) -1 );
  object = (((source << snum) |(source >> (NEIGHBOUR - snum)))
            & ( (1 << NEIGHBOUR) -1 ));
  locus->bit = (locus->bit & 
                     (((1<<NEIGHBOUR+length)-1)^((1<<NEIGHBOUR)-1))
                     | object);
}

void
  Genome_mutation( Genome **gene ,int pops )
{
  Genome *source,*tmp;
  GenoData *son;
  int i;
  int num;
  
  void mutate(GenoData *);
  
  /* select mutation genome */
  do
  {
    i=rand()%(pops);
  } while(gene[i]->isDead==TRUE);
  son = Genome_copy( gene[i]->data );
  printf("#M D:%d(%f) ",i,REAL_FITNESS(gene[i]->data));

  mutate( son );
  
  /* Add new genome */
  num = Genome_add( gene, son, pops );
  gene[num]->data->total_fitness  = get_fitness(gene[num]->data);
  gene[num]->data->lifetime       = 1;
}

void
  mutate(GenoData *son)
{
  Locus *tmp;
  int i;

  void mutateLocus(Locus *,int);
  void mutateMask(GenoData *,int);
  
  /* mutate mask */
  mutateMask(son,son->states);
  
  for(tmp=son->head;tmp!=NULL;tmp=tmp->next)
    mutateLocus(tmp,son->states);
}

void
  mutateMask(GenoData *son,int length)
{
  extern float MutRate;
  int i;
  float rnd;
  unsigned long mask,bitxor,newcode;

  for(i=0;i<length;i++)
  {
    rnd = rand() % 65536 /65536.0;
    if(rnd < MutRate)
      mask |= (1 << i);
  }
  bitxor  = ( son->mask &  mask) ^ mask;
  newcode = ( son->mask & ~mask) | bitxor;
  son->mask = newcode;
}

void 
  mutateLocus(Locus *locus,int length)
{
  extern float MutRate;
  float rnd;
  int i;
  unsigned long m_wild=0,m_bit=0,m_state=0,m_tmp;
  unsigned bitxor,newcode;
  
  /* for wildcard & bits */
  for(i=0;i<length+NEIGHBOUR;i++)
  {
    rnd = (rand() % 65536) / 65535.0;
    if(rnd <= MutRate)
    {
      m_tmp = (1 << i );
      if( locus->wildcard & m_tmp ) /* this wildcard is up */
      {
        m_wild |= (1 << i);
        switch(rand() % 2)
        {
        case 0: m_bit |= (1 << i); break;
        case 1:                    break;
        }
      }
      else
        switch(rand() % 2)
        {
        case 0: m_wild |= (1 << i); break;
        case 1: m_bit  |= (1 << i); break;
        }
    }
  }
  bitxor  = ( locus->wildcard &  m_wild ) ^ m_wild;
  newcode = ( locus->wildcard & ~m_wild ) | bitxor;
  locus->wildcard = newcode;

  bitxor  = ( locus->bit &  m_bit) ^ m_bit;
  newcode = ( locus->bit & ~m_bit) | bitxor;
  locus->bit = newcode;

  /* for state */
  for(i=0;i<length;i++)
  {
    rnd = rand() % 65536 /65536.0;
    if(rnd < MutRate)
      m_state |= (1 << i);
  }
  bitxor  = ( locus->state &  m_state) ^ m_state;
  newcode = ( locus->state & ~m_state) | bitxor;
  locus->state = newcode;
}

void
  GenomeNumElite( Genome **source,Genome **dist,int pops,int e_pops)
{
  int i,j;
  int *selected;
  float max_fit=0.0;
  int max_num=0;
  
  if(e_pops == 0)
    return;

  selected = (int *)xmalloc(sizeof(int) * pops);
  
  for(i=0;i<pops;i++)
  {
    selected[i]=FALSE;
    if( max_fit < REAL_FITNESS(source[i]->data))
    {
      max_fit=REAL_FITNESS(source[i]->data);
      max_num=i;
    }       
  }
  Genome_add( dist, Genome_copy(source[max_num]->data), pops );
  fprintf(stderr,"F:%f\n",max_fit);
  selected[max_num]=TRUE;
  e_pops--;

  for(;e_pops>0;e_pops--)
  {
    max_fit=REAL_FITNESS(source[0]->data);
    max_num=0;

    for(i=1;i<pops;i++)
    {
      if( max_fit < REAL_FITNESS(source[i]->data) 
         && selected[i] != TRUE )
      {
        max_fit = REAL_FITNESS(source[i]->data);
        max_num = i;
      }
    }
    selected[max_num]=TRUE;
    Genome_add( dist, Genome_copy(source[max_num]->data), pops );
    fprintf(stderr,"F:%f\n",max_fit);
  }
  free(selected);
}

void
  GenomeNumCrossover( Genome **source,Genome **dist,int pops,int c_pops)
{
  int i,num;
  GenoData *son1,*son2;
  
  for(i=0;i<(int)(c_pops/2);i++)
  {
    do
    {
      num=rand()%(pops);
    } while( source[num]->data->geno_length <= 1 );
    
    son1 = Genome_copy( source[num]->data );
    printf("#CB D:%d(%f) ",i,REAL_FITNESS(source[num]->data) );
    
    do
    {
      num=rand()%(pops);
    } while( source[num]->data->geno_length <= 1 );

    son2 = Genome_copy( source[num]->data );
    printf("M:%d(%f)\n",i,REAL_FITNESS(source[num]->data));
    
    crossing( son1,son2 );
    
    num = Genome_add( dist, son1, pops );
    dist[num]->data->total_fitness  = get_fitness(dist[num]->data);
    dist[num]->data->lifetime       = 1;
    
    num = Genome_add( dist, son2, pops );
    dist[num]->data->total_fitness  = get_fitness(dist[num]->data);
    dist[num]->data->lifetime       = 1;
  }
}

void
  GenomeNumMutation( Genome **source,Genome **dist,int pops,int m_pops)
{
  int num;
  int i;
  GenoData *son;
    
  for(i=0;i<m_pops;i++)
  {
    num=rand()%(pops);
    son = Genome_copy( source[num]->data );
  
    mutate( son );
  
    /* Add new genome */
    num = Genome_add( dist, son, pops );
    dist[num]->data->total_fitness  = get_fitness(dist[num]->data);
    dist[num]->data->lifetime       = 1;
  }
}

void
  GenomeNumDeficiency( Genome **source,Genome **dist,int pops,int d_pops)
{
  int i;
  int num;
  GenoData *son;

  void GenomePrint(GenoData *);
  
  for(i=0;i<d_pops;i++)
  {
    do
    {
      num=rand()%(pops);
    } while( source[num]->data->geno_length <= 1 );
    son = Genome_copy( source[num]->data );
    deficiency( son );

    /* Add new genome */
    num = Genome_add( dist, son, pops );
    dist[num]->data->total_fitness  = get_fitness(dist[num]->data);
    dist[num]->data->lifetime       = 1;
  }
}

void
  GenomeNumDuplicate( Genome **source,Genome **dist,int pops,int d_pops)
{
  int i;
  int num;
  GenoData *son;

  for(i=0;i<d_pops;i++)
  {
    num=rand()%(pops);
    son = Genome_copy( source[i]->data );
    
    duplicate( son );
    
    /* Add new genome */
    num = Genome_add( dist, son, pops );
    dist[num]->data->total_fitness  = get_fitness(dist[num]->data);
    dist[num]->data->lifetime       = 1;
  }
}


#endif /* ! __CELLapist__ */

