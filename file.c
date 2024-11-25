#include "stdlib.h"

#include "SelFile.h"

#include "X_include.h"

#include "window.h"
#include "buttons.h"

#include "globals.h"
#include "macros.h"
#include "GA.h"

void
  LoadRule(Widget w,caddr_t client_data,caddr_t call_data)
{
  char *path;
  void File2Rule(char *);

  if(!XsraSelFile(screen.disp,
                  (unsigned char *) "Please set load file name:",
                  (unsigned char *) "Okay",
                  (unsigned char *) "Cancel",
                  (char *)NULL,
                  (int (*)())NULL,
                  &path))
  {
    File2Rule(path);
  }
  else
  {
    return;
  }
}


void 
  LoadState(Widget w,caddr_t client_data,caddr_t call_data)
{
  char *path;
  void File2State(char *);

  if(!XsraSelFile(screen.disp,
                  (unsigned char *) "Please set load file name:",
                  (unsigned char *) "Okay",
                  (unsigned char *) "Cancel",
                  (char *)NULL,
                  (int (*)())NULL,
                  &path))
  {
    File2State(path);
  }
  else
  {
    return;
  }
}

void 
  SaveState(Widget w,caddr_t client_data,caddr_t call_data)
{
  char *path;
  void State2File(char *);

  if(!XsraSelFile(screen.disp,
                  (unsigned char *) "Please set save file name:",
                  (unsigned char *) "Okay",
                  (unsigned char *) "Cancel",
                  (char *)NULL,
                  (int (*)())NULL,
                  &path))
  {
    State2File(path);
  }
  else
  {
    return;
  }
}

void State2File(char *filename)
{
  FILE *fp;
  int x,y;
  
  if((fp = fopen(filename,"w"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    return;
  }

  fprintf(fp,"%d\n",screen.rule_num);
  fprintf(fp,"%d x %d\n",screen.x,screen.y);

  for(y=0;y<screen.y;y++)
  {
    for(x=0;x<screen.x;x++)
    {
      fprintf(fp,"%d ",Cell[pos(x,y)].state);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}

void File2State(char *filename)
{
  FILE *fp;
  int x,y;

  void ruleNonNew(void);


  if((fp = fopen(filename,"r"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    return;
  }

  fscanf(fp,"%d\n",&(screen.rule_num));
  fscanf(fp,"%d x %d\n",&(screen.x),&(screen.y));

  free(Cell);
  Cell=(CELL *)malloc(sizeof(CELL)*screen.x*screen.y);
  XtDestroyWidget(f_screen);
  make_field();
  make_cellWidget();

  for(y=0;y<screen.y;y++)
  {
    for(x=0;x<screen.x;x++)
    {
      fscanf(fp,"%d",&(Cell[pos(x,y)].state));
    }
  }
  fclose(fp);

  
  ruleNonNew();
}

int
  getRuleNum(char *filename)
{
  int rulenum;
  char c;
  FILE *fp;

  if((fp = fopen(filename,"r"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    exit(0);
  }

  while( (c=getc(fp)) != 'R' );
  
  fscanf(fp,"%d",&rulenum);
  fclose(fp);

  return(rulenum);
}

void 
  File2Rule(char *filename)
{
/*
  FILE *fp;
 */
  GenoData genome;
  int rulenum;
  
  void GenomeLoad(char *,GenoData *);
  RuleTbl *setRule(GenoData *);
  
/*  
  RuleTbl *loadRule(FILE *fp);

  if((fp = fopen(filename,"r"))==NULL)
  {
    fprintf(stderr,"%s can't open\n",filename);
    return;
  }
 */

  rulenum = getRuleNum(filename);
  rule(screen.toplevel,&rulenum,(caddr_t)NULL);

/*
  rule(screen.toplevel,&(screen.rules),(caddr_t)NULL);
 */
  
  GenomeLoad(filename,&genome);
  ruleT = setRule(&genome);
  
/*  
  ruleT=loadRule(fp);

  fclose(fp);
 */
}


