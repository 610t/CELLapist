#include <stdio.h>

void skipline(FILE *fp)
{
  char c;

  while( c != '\n' )
    c = getc(fp);
}

char *getline(FILE *fp)
{
  int i,j;
  char c;
  static char line[1024];

  
  c=getc(fp);
  while( c == '#' )
  {
    skipline(fp);
    c = getc(fp);
  }
  
  for(i=0;c!='\n';c=getc(fp),i++)
    line[i] = c;

  return(&(line[0]));
}

