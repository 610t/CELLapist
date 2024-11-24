#define MAX_STATE_NUM           20
#define MAX_GENOME_LENGTH       10
#define MIN_GENOME_LENGTH       10
#define OVER_FITNESS            100.0
#define STATE_NUM               6
#define MAX_POPULATION          10
#define LEAST_LIFETIME          10
#define NEIGHBOUR               8
#define TRUE                    1
#define FALSE                   0

#if defined(__FixedTarget__)
# define REAL_FITNESS(GENEDAT)   ((GENEDAT)->total_fitness)
#else
# define REAL_FITNESS(GENEDAT)   ((GENEDAT)->total_fitness/(GENEDAT)->lifetime)
#endif /* !__FixedTarget__ */
typedef struct _Locus
{
  unsigned long wildcard; 
  unsigned long bit;
  unsigned long state;
  
  struct _Locus *next;
} Locus;

typedef struct _GenoData
{
  Locus *head;
  unsigned long mask;
  int geno_length;
  int states;
  float total_fitness;
#if defined(__LargeLoad__)
  float speed_fitness;
  float dist_fitness;
#endif /* __LargeLoad__ */
  long lifetime;
} GenoData;

typedef struct _Genome 
{
  struct _GenoData *data;
  int isDead;

} Genome;

