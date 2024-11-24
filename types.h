#ifndef __TYPES_H__
  
typedef struct _RULE 
{
  int RuleNum;       /* $B%;%k$N%"%k%4%j%:%`$NDj5A(B */
  char *RuleName;       /* $B%k!<%k$NL>A0(B */
    
  /* $B0J2<$O%;%k$NA`:n4X?t(B */
  void (*New)();
  void (*Delete)();
  void (*Step)();
  void (*Random)();
#ifdef __CELLapist__    /* window$B$rMQ$$$k;~$KI,MW$H$J$k4X?t(B */
  void (*Button)();
  void (*Refresh)();
#endif /* __CELLapist__ */
} RULE;

typedef struct _CELL_WINDOW 
{
#ifdef __CELLapist__
  /* X window $B4X78(B */
  Widget toplevel;      /* $B2hLL$N%H%C%W%l%Y%k%&%$%8%'%C%H(B */
  Display *disp;        /* $B2hLL$KBP$9$k%G%#%9%W%l%$9=B$BN(B */
  Widget field;         /* $B%;%k$r=q$/%U%#!<%k%I(B */
  Pixmap pix;           /* $B%;%kMQ$N%T%C%/%9%^%C%W(B */
  XColor Color[256];    /* $B%+%i!<$N(Bpixel$BCM(B */
  unsigned long cells[COLOR_MAX];
  GC     gc;            /* GC */
  XtIntervalId  Run_timeout; 
  XFontStruct   *font;
  /* X window$BMQ$NJQ?t72(B */
  int depth;            /* $B2hLL$N?<$5(B */
  int colormax;         /* $B8=:_3NJ]$7$F$$$k%+%i!<$N:GBgCM(B */
  int size;             /* 1$B%;%k$NBg$-$5(B(pixel) */
  int time;             /* $B99?7;~4V(B (msec) */
  /* Cursor variable */
  unsigned long sp;
  unsigned long n_st;
#endif /* __CELLapist__ */
  int x;                /* x$B<4J}8~$N%;%k$N?t(B */
  int y;                /* y$B<4J}8~$N%;%k$N?t(B */
  int epoch;            /* $B@$Be(B */
  int rules;            /* $B8=:_$"$k%k!<%k$N?t(B */
  int rule_num;         /* $B8=:_;H$C$F$$$k%k!<%k(B */
  RULE *rule;
} CELL_WINDOW;

/* for load */
typedef struct _INITIAL 
{
  int birth_epoch;
  int start_x,start_y;
  struct _INITIAL *next;
} INITIAL;

typedef struct _LOAD 
{
  INITIAL *head;
  INITIAL *headNew;
  INITIAL *tail;
  INITIAL *tailNew;
} LOAD;

/* $B3F%;%k$NDj5A(B */
typedef struct _CELL 
{
#ifdef __CELLapist__
  int color;
#endif /* __CELLapist__ */
  int x,y;
  unsigned long state;
  unsigned long newstate;
  int isUpdated;
#if !defined(__LargeLoad__)
  LOAD *load;
#endif /* __LargeLoad__ */
} CELL;

typedef unsigned long RuleTbl;

#define __TYPES_H__
#endif /* __TYPES_H__ */
