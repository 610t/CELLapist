#include "Conveyor.h"
#include "globals.h"
#include "conveyorLookup.h"

#if defined(__LargeLoad__)
#  include "largeload.h"
#endif

#define conveyorCheckRegion(x,y,dx,dy) (((x)+(dx)>=0 && (x)+(dx)<screen.x)&&((y)+(dy)>=0 && (y)+(dy)<screen.y))

/* Private関数の定義 */
void conveyorSensor();
void conveyorMoveSensor(CELL *);
void conveyorSetState(void);
void conveyorSetCellState(CELL *);
int conveyorGetState(int,int,int,int);
unsigned long conveyorNeighbourState(CELL *,int,int);
int conveyorCheckANDState(int,int,int,int,int,int);
/*
   int conveyorCheckRegion(int,int,int,int);
   */
int conveyorRealMove(int,int,int,int);

/* conveyorRule*.c */
void conveyorUpdateCellState4(CELL *);
void conveyorUpdateCellState4Rand(CELL *);
void conveyorUpdateCellState4MOD(CELL *);
void conveyorUpdateCellState8(CELL *);
void conveyorUpdateCellState8New(CELL *);
void conveyorUpdateCellState8Fujita(CELL *);
void conveyorUpdateCellStateGA(CELL *);

#ifdef __CELLapist__
extern void conveyorSetCursor(int,int,int);
extern void conveyorDrawCell(Drawable,float,float,int,int,int);
#endif /* __CELLapist__ */

long tmpcount;

/*
   公開されている関数
   */

/* destoractor (Delete) */
#if !defined(__LargeLoad__)
void
deleteINITIAL(INITIAL *load)
{
  INITIAL *tmp,*tmp2;

  tmp=load;
  while(tmp!=NULL)
  {
    tmp2=tmp->next;
    free(tmp);
    tmp=tmp2;
  }
}

void
deleteLOAD(CELL *celluar)
{
  deleteINITIAL(celluar->load->head);
  free(celluar->load->head);
  deleteINITIAL(celluar->load->headNew);
  free(celluar->load->headNew);
  deleteINITIAL(celluar->load->tail);
  free(celluar->load->tail);
  deleteINITIAL(celluar->load->tailNew);
  free(celluar->load->tailNew);
  
  free(celluar->load);
}

void
conveyorLoadDelete()
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      deleteLOAD(&(Cell[pos(x,y)]));
    }
}
#endif /* !__LargeLoad__ */

void 
conveyorDelete()
{
#if !defined(__LargeLoad__)
  conveyorLoadDelete();
#endif /* !__LargeLoad__ */

#ifdef __CELLapist__
{
  XGCValues gcv;

  gcv.function=GXcopy;
  XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);
}
#endif /* __CELLapist__ */

#if defined(__LargeLoad__)
  Obj_cnt=0;
#endif
  return;
}
/* セルの初期化 (New) */
#if !defined(__LargeLoad__)
void
putLoad(CELL *celluar,int epoch)
{
  INITIAL *tmp;

#if defined(__GA__)
  sensor_num++;
#endif /* __GA__ */

  if(celluar->load->head == NULL)
  {
    celluar->load->head = celluar->load->tail 
      = (INITIAL *)malloc(sizeof(INITIAL));
  }
  else
  {
    tmp                         = celluar->load->head;
    celluar->load->head         = (INITIAL *)malloc(sizeof(INITIAL));
    celluar->load->head->next   = tmp;
  }
  
  celluar->load->head->start_x     = celluar->x;
  celluar->load->head->start_y     = celluar->y;
  celluar->load->head->birth_epoch = epoch;

  celluar->load->tail->next        = NULL;
}

void
allocLoad(CELL *celluar,int flag,int epoch)
{
  LOAD *tmp;

  /* allocation of load */
  if((celluar->load=(LOAD *)malloc(sizeof(LOAD)))==NULL)
  {
    fprintf(stderr,"Can't allocate load\n");
    exit(-1);
  }
  
  celluar->load->tailNew    = NULL;
  celluar->load->headNew    = NULL;
  celluar->load->head       = NULL;
  celluar->load->tail       = NULL;

  if(flag==TRUE)
  {
    putLoad(celluar,epoch);
  }
}
#endif /* !__LargeLoad__ */

#ifdef __CELLapist__
void
ConveyorClearScreen()
{
  XGCValues gcv;

  gcv.function=GXcopy;
  XChangeGC(screen.disp,screen.gc,GCFunction,&gcv);

  /* clear screen with white color*/
  XSetForeground(XtDisplay(screen.field),screen.gc
                 ,WhitePixel(screen.disp,DefaultScreen(screen.disp)));
  XFillRectangle(XtDisplay(screen.field),screen.pix,screen.gc,
                 0,0,screen.x*screen.size,screen.y*screen.size);
}

void
conveyorAllocateColor()
{
  Colormap cmap;

  cmap=DefaultColormap(screen.disp,DefaultScreen(screen.disp));

  screen.Color[CONVEYOR_VACUM_COLOR].red  = 0;
  screen.Color[CONVEYOR_VACUM_COLOR].blue = 0;
  screen.Color[CONVEYOR_VACUM_COLOR].green= 0;

  screen.Color[CONVEYOR_CONTROL_COLOR].red  = 0;
  screen.Color[CONVEYOR_CONTROL_COLOR].blue = 0;
  screen.Color[CONVEYOR_CONTROL_COLOR].green= 0;
  
  screen.Color[CONVEYOR_UP_COLOR].red  = 65535;
  screen.Color[CONVEYOR_UP_COLOR].blue = 0;
  screen.Color[CONVEYOR_UP_COLOR].green= 0;

  screen.Color[CONVEYOR_RIGHT_COLOR].red  = 10000;
  screen.Color[CONVEYOR_RIGHT_COLOR].blue = 0;
  screen.Color[CONVEYOR_RIGHT_COLOR].green= 30000;
  
  screen.Color[CONVEYOR_DOWN_COLOR].red  = 0;
  screen.Color[CONVEYOR_DOWN_COLOR].blue = 30000;
  screen.Color[CONVEYOR_DOWN_COLOR].green= 30000;
  
  screen.Color[CONVEYOR_LEFT_COLOR].red  = 10000;
  screen.Color[CONVEYOR_LEFT_COLOR].blue = 30000;
  screen.Color[CONVEYOR_LEFT_COLOR].green= 0;

  screen.Color[CONV_UP_RIGHT_COLOR].red  = 27768;
  screen.Color[CONV_UP_RIGHT_COLOR].blue = 0;
  screen.Color[CONV_UP_RIGHT_COLOR].green= 15000;

  screen.Color[CONV_UP_LEFT_COLOR].red  = 27768;
  screen.Color[CONV_UP_LEFT_COLOR].blue = 15000;
  screen.Color[CONV_UP_LEFT_COLOR].green= 0;

  screen.Color[CONV_DOWN_LEFT_COLOR].red  = 5000;
  screen.Color[CONV_DOWN_LEFT_COLOR].blue = 30000;
  screen.Color[CONV_DOWN_LEFT_COLOR].green= 15000;

  screen.Color[CONV_DOWN_RIGHT_COLOR].red  = 5000;
  screen.Color[CONV_DOWN_RIGHT_COLOR].blue = 15000;
  screen.Color[CONV_DOWN_RIGHT_COLOR].green= 30000;

  screen.Color[CONVEYOR_BACKGROUND].red  = 65535;
  screen.Color[CONVEYOR_BACKGROUND].blue = 65535;
  screen.Color[CONVEYOR_BACKGROUND].green= 65535;

  XStoreColors(screen.disp,cmap,screen.Color,screen.colormax);
}
#endif /* __CELLapist__ */


void 
conveyorNew(int init_f)
{
  int x,y,position;

  screen.epoch=0;
#if defined(__CELLapist__)
  conveyorAllocateColor();
  showEpoch();
  ConveyorClearScreen();
#endif /* __CELLapist__ */

  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
    {
      position=pos(x,y);
      Cell[position].x                = x;
      Cell[position].y                = y;
      Cell[position].isUpdated        = FALSE;
#if !defined(__LargeLoad__)
      allocLoad(&(Cell[position]),FALSE,screen.epoch);
#endif /* !__LargeLoad__ */
      if( init_f )
      {
        Cell[position].state            = CONVEYOR_VACUM;
#if defined(__CELLapist__)
        Cell[position].color            = CONVEYOR_VACUM_COLOR;
#endif /* __CELLapist__ */
      }
#if defined(__CELLapist__)
      else
      {
        if( Cell[position].state != CONVEYOR_VACUM )
          Cell[position].color = 1;
        else
          Cell[position].color = CONVEYOR_VACUM_COLOR;
      }
      conveyorDrawCell(screen.pix
                       ,x,y,Cell[position].color,Cell[position].state
                       ,screen.size);
#endif /* __CELLapist__ */
      Cell[position].newstate         = Cell[position].state;
    }

#if defined(__LargeLoad__)
  Obj_cnt=0;
#endif /* __LargeLoad__ */

#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
  conveyorSetCursor(CONVEYOR_VACUM,CONVEYOR_VACUM_COLOR,0);
  screen.n_st=CONVEYOR_VACUM;
  screen.sp=pos(screen.x,screen.y);
#endif /* __CELLapist__ */
}

/* セル状態の更新 (Step) */
#ifdef __LargeLoad__
void
conveyorLargeLoad()
{
  int i;
  
  for(i=0;i<Obj_cnt;i++)
    if(Obj[i].flg == FALSE) 
    {
      int tmp;

      tmp = move_obj(&Obj[i]);

      switch(tmp)
      {
       case REACHED:
        /* reached */
        Obj[i].time = screen.epoch;
        Obj[i].flg  = TRUE;
        fprintf(stderr,"[Obj] time:%d,stpos(%f,%f),goal(%f,%f),delta(%f/%f)\n"
                ,Obj[i].time
                ,Obj[i].startPos.x,Obj[i].startPos.y
                ,target.x,target.y
                ,Obj[i].delta
                ,sqrt(POW2(Obj[i].startPos.x-Obj[i].jusin.x)
                      +POW2(Obj[i].startPos.y-Obj[i].jusin.y)));
        break;
       case STOP:
        /* stoping */
        Obj[i].flg  = TRUE;
        break;
       case NONE:               /* When does this code use? */
        Obj[i].flg  = TRUE;
        break;
       default:
        /* none */
        break;
      }
    }
}
#endif /* __LargeLoad__ */

void conveyorStep4(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellState4)(&Cell[pos(x,y)]);
      }
  
#ifndef __LargeLoad__
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  conveyorSetState();
}

void conveyorStep4Rand(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellState4Rand)(&Cell[pos(x,y)]);
      }
  
#ifndef __LargeLoad__
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  conveyorSetState();
}

void conveyorStep4MOD(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellState4MOD)(&Cell[pos(x,y)]);
      }
  
#ifndef __LargeLoad__
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  tmpcount=0;
  conveyorSetState();
  /*
     fprintf(stderr,"[Total:(%d+%d) %d (%d)]\n",tmpcount,goal,goal+tmpcount,sensor_num);
     */
}

void conveyorStep8(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellState8)(&Cell[pos(x,y)]);
      }

#ifndef __LargeLoad__
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  conveyorSetState();
}

void conveyorStep8New(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellState8New)(&Cell[pos(x,y)]);
      }
  
#ifndef __LargeLoad__
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  conveyorSetState();
}

void conveyorStep8Fujita(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellState8Fujita)(&Cell[pos(x,y)]);
      }
  
#ifndef __LargeLoad__
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  conveyorSetState();
}

void conveyorStepGA(void)
{
  int x,y;
  
  for(y=0;y<screen.y;y++)
    for(x=0;x<screen.x;x++)
      if(Cell[pos(x,y)].isUpdated==FALSE)
      {
        (conveyorUpdateCellStateGA)(&Cell[pos(x,y)]);
      }
  
#if !defined(__LargeLoad__)
  conveyorSensor();
#else
  conveyorLargeLoad();
#endif /* __LargeLoad__ */
  conveyorSetState();
}


/* ランダムに初期化 (Random) */
#ifdef __CELLapist__
void 
conveyorRandom(Widget w,int *dense,caddr_t call_data)
#endif /* __CELLapist */
#ifdef __GA__
  void 
  conveyorRandom(int dense,int mode)
#endif /* __GA__ */
{
  int x,y,s;
  unsigned long position;
#ifdef __CELLapist__
  int mode;

  extern Widget StateDistButton[];
  extern Widget StateTop;
  extern int dense,width;

  mode = *(int *)XawToggleGetCurrent(StateDistButton[1]);
#endif /* __CELLapist__ */
  
#if !defined(__LargeLoad__)
  if(Cell[0].load!=NULL)
    conveyorLoadDelete();
#endif /* !__LargeLoad__ */

#ifdef __CELLapist__
  ConveyorClearScreen();
#endif /* __CELLapist__ */

  switch(mode)
  {
   case 0:
    for(y=0;y<screen.y;y++)
      for(x=0;x<screen.x;x++)
      {
        position=pos(x,y);
        if(rand()%100>=dense)
        {
          Cell[position].isUpdated = FALSE;
#ifdef __NoAlloc__
          Cell[position].state = CONVEYOR_VACUM;
          Cell[position].newstate = CONVEYOR_VACUM;
# if !defined(__LargeLoad__)
          allocLoad(&(Cell[position]),FALSE,screen.epoch);
# endif /* !__LargeLoad__ */
#else
          Cell[position].state = CONVEYOR_SENSOR;
          Cell[position].newstate = CONVEYOR_SENSOR;
# if !defined(__LargeLoad__)
          allocLoad(&(Cell[position]),TRUE,screen.epoch);
# endif /* !__LargeLoad__ */
#endif /* !__NoAlloc__ */
#ifdef __CELLapist__
          Cell[position].color = 1;
#endif /* __CELLapist */
        }
        else
        {
          Cell[position].isUpdated = CONVEYOR_BROKEN;
          Cell[position].state = CONVEYOR_BROKEN;
#ifdef __CELLapist__
          Cell[position].color  = CONVEYOR_BROKEN_COLOR;
#endif /* __CELLapist */
# if !defined(__LargeLoad__)
          allocLoad(&(Cell[position]),FALSE,screen.epoch);
# endif /* !__LargeLoad__ */
#ifdef __GA__ 
          broken_num++;
#endif /* __GA__ */
        }
      }
    break;
   case 1:
    break;
   default:
    break;
  }

  /* Center of field is control */
#ifdef __GA__
  position = st_pos;
#else  /* !__GA__*/
  position = pos(screen.x/2,screen.y/2);
#endif /* !__GA__*/

#ifdef __DEBUG__
  fprintf(stderr,"(%d %d):",st_pos%CELL_Y,st_pos/CELL_Y);
#endif /* __DEBUG__ */
  if(Cell[position].isUpdated==CONVEYOR_BROKEN)
  {
    Cell[position].isUpdated=FALSE;
#ifdef __GA__ 
    broken_num--;
#endif /* __GA__ */
  }
  else
  {
#if !defined(__NoAlloc__) || !defined(__LargeLoad__)
    free(Cell[position].load->head);
    Cell[position].load->head = Cell[position].load->tail =NULL;
#ifdef __GA__ 
    sensor_num--;
#endif /* __GA__ */
#endif
  }
  
  screen.epoch=0;

  Cell[position].state    = CONVEYOR_CONTROL;
  Cell[position].newstate = CONVEYOR_CONTROL;
#ifdef __CELLapist__
  Cell[position].color    = CONVEYOR_CONTROL_COLOR;
  conveyorRefresh();
  showEpoch();
#endif /* __CELLapist */
}

/*
   Private関数
   */
int conveyorGetState(int x,int y,int dx,int dy)
{
  
  if(conveyorCheckRegion(x,y,dx,dy))
    return(Cell[pos((x+dx),(y+dy))].state);
  else
    return(0);
}

/* when flag == TRUE use GA mask */
unsigned long conveyorNeighbourState(CELL *celluar,int neighbour,int flag)
{
  int x,y,state=0;
  
  x=celluar->x; y=celluar->y;
  
  state |= conveyorCheckANDState(x,y, 0,-1,CONVEYOR_UP   ,flag);
  state |= conveyorCheckANDState(x,y, 0,+1,CONVEYOR_DOWN ,flag);
  state |= conveyorCheckANDState(x,y,-1, 0,CONVEYOR_LEFT ,flag);
  state |= conveyorCheckANDState(x,y,+1, 0,CONVEYOR_RIGHT,flag);
  
  if(neighbour==8)
  {
    state |= conveyorCheckANDState(x,y,+1,-1,CONVEYOR_UP_RIGHT  ,flag);
    state |= conveyorCheckANDState(x,y,-1,-1,CONVEYOR_UP_LEFT   ,flag);
    state |= conveyorCheckANDState(x,y,+1,+1,CONVEYOR_DOWN_RIGHT,flag);
    state |= conveyorCheckANDState(x,y,-1,+1,CONVEYOR_DOWN_LEFT ,flag);
  }
  return(state);
}


int conveyorCheckANDState(int x,int y,int dx,int dy,int direction,int flag)
{
  unsigned long state;
  int position;
  extern unsigned long signal_mask;

  position=pos(x+dx,y+dy);
  if(conveyorCheckRegion(x,y,dx,dy))
    if(flag==TRUE)              /* when GA rule */
    {
      if( (Cell[position].state & signal_mask) != 0)
      {
        return(direction);
      }
    }
    else
    {
      if( (Cell[position].state & CONVEYOR_MOVE_MASK) != 0)
        return(direction);
    }

  return(0);
}
/*
   int conveyorCheckRegion(int x,int y,int dx,int dy)
   {
     int nowX,nowY;
  
     nowX=x+dx;
     nowY=y+dy;
  
     if(nowX>=0 && nowX<screen.x)
       if(nowY>=0 && nowY<screen.y)
         return(TRUE);
  
     return(FALSE);
   }
   */
void conveyorSetState(void)
{
  int x,y;
  unsigned long position;

  for(y=0;y<screen.y;y++)
  {
    for(x=0;x<screen.x;x++)
    {
      position = pos(x,y);
      conveyorSetCellState(&Cell[position]);
#ifdef __DEBUG__
      fprintf(stderr,"%3x ",Cell[position].state );
#endif /* __DEBUG__ */

#if !defined(__LargeLoad__)
      /* Delete loads at Control */
      if( (Cell[position].state & CONVEYOR_CONTROL) != 0 )
      {
        while( Cell[position].load->head != NULL )
        {
# ifdef __GA__ 
          if( st_pos == position )
          {
            goal++;
            total_time
              +=((screen.epoch - Cell[position].load->head->birth_epoch)/
                 (ABS(Cell[position].load->head->start_x - screen.x/2)
                  +ABS(Cell[position].load->head->start_y - screen.y/2)));
          }
          else
            miss_num++;
# endif /* __GA__ */          
          Cell[position].load->tail=Cell[position].load->head->next;
          free(Cell[position].load->head);
          Cell[position].load->head=Cell[position].load->tail;
        }
      }
#endif /* !__LargeLoad__ */          
    }

#ifdef __DEBUG__
    fprintf(stderr,"\n");
#endif /* __DEBUG__ */
  }
#ifdef __DEBUG__
  fprintf(stderr,"\n");
#endif /* __DEBUG__ */
  
#ifdef __CELLapist__
  exposeField(screen.field,NULL,NULL);
#endif /* __CELLapist__ */
}

void conveyorSetCellState(CELL *celluar)
{
#if !defined(__LargeLoad__)
  /* for small Load */
  if( celluar->load->headNew != NULL )
    celluar->newstate |= CONVEYOR_SENSOR;
  else
    celluar->newstate &= ~CONVEYOR_SENSOR;

  celluar->load->head = celluar->load->headNew;
  celluar->load->tail = celluar->load->tailNew;
  celluar->load->headNew=celluar->load->tailNew=NULL;
#endif /* !__LargeLoad__ */
  
  if( (celluar->isUpdated & CONVEYOR_BROKEN) == 0 )
    celluar->isUpdated=FALSE;
  else      
    return;
  
  if( celluar->state == celluar->newstate
     && ( celluar->state & CONVEYOR_SENSOR ) == 0 )
  {
    celluar->newstate=CONVEYOR_VACUM;
    return;
  }

#ifdef __CELLapist__
  conveyorDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,
                   celluar->state,screen.size);
  conveyorDrawCell(screen.pix,
                   celluar->x,celluar->y,celluar->color,
                   celluar->newstate,screen.size);
#endif /* __CELLapist__ */
  celluar->state=celluar->newstate;

  celluar->newstate=CONVEYOR_VACUM;
}

#if !defined(__LargeLoad__)
void conveyorSensor()
{
  int x,y;
  
  for(x=0;x<screen.x;x++)
    for(y=0;y<screen.y;y++)
      if( Cell[pos(x,y)].load->head != NULL )
        conveyorMoveSensor(&Cell[pos(x,y)]);
}


int 
conveyorRealMove(int x,int y,int dx,int dy)
{
  unsigned long position;
  
  if(conveyorCheckRegion(x,y,dx,dy))
  {
    position = pos(x+dx,y+dy);

    if(Cell[pos(x,y)].load->head == NULL)
    {
      fprintf(stderr,"Why can you move a sensor?\n");
      return(TRUE);
    }
      
    if( Cell[position].load->headNew != NULL)
    {
      Cell[position].load->tailNew->next = Cell[pos(x,y)].load->head;
      Cell[position].load->tailNew       = Cell[pos(x,y)].load->tail;
    }
    else
    {
      Cell[position].load->headNew = Cell[pos(x,y)].load->head;
      Cell[position].load->tailNew = Cell[pos(x,y)].load->tail;
    }
    return(TRUE);
  }
  else
  {
    position=pos(x,y);

    while( Cell[position].load->head != NULL )
    {
#ifdef __GA__ 
      miss_num++;
#endif /* __GA__ */
      Cell[position].load->tail=Cell[position].load->head->next;
      free(Cell[position].load->head);
      Cell[position].load->head=Cell[position].load->tail;
    }

    return(FALSE);
  }
}

void conveyorMoveSensor(CELL *celluar)
{
  int x,y;
  
  x=celluar->x;
  y=celluar->y;
  
  switch( celluar->state & ~ CONVEYOR_SENSOR )
  {
    /* move distance 1 cell */
   case CONVEYOR_UP:
   case CONVEYOR_UP|CONVEYOR_RIGHT|CONVEYOR_LEFT:
    conveyorRealMove(x,y, 0,-1);
    break;
   case CONVEYOR_DOWN:
   case CONVEYOR_DOWN|CONVEYOR_RIGHT|CONVEYOR_LEFT:
    conveyorRealMove(x,y, 0, 1);
    break;
   case CONVEYOR_RIGHT:
   case CONVEYOR_RIGHT|CONVEYOR_UP|CONVEYOR_DOWN:
    conveyorRealMove(x,y, 1, 0);
    break;
   case CONVEYOR_LEFT:
   case CONVEYOR_LEFT|CONVEYOR_UP|CONVEYOR_DOWN:
    conveyorRealMove(x,y,-1, 0);
    break;
    /* move distance 2 cell */
   case CONVEYOR_UP|CONVEYOR_RIGHT:
    conveyorRealMove(x,y, 1,-1);
    break;
   case CONVEYOR_UP|CONVEYOR_LEFT:
    conveyorRealMove(x,y,-1,-1);
    break;
   case CONVEYOR_DOWN|CONVEYOR_RIGHT:
    conveyorRealMove(x,y, 1, 1);
    break;
   case CONVEYOR_DOWN|CONVEYOR_LEFT:
    conveyorRealMove(x,y,-1, 1);
    break;

    /* destination */
   case CONVEYOR_CONTROL:
    conveyorRealMove(x,y,0,0);
    break;
   default:
    conveyorRealMove(x,y,0,0);
    return;
    break;
  }
}
#endif /* !__LargeLoad__ */
