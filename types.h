#ifndef __TYPES_H__
  
typedef struct _RULE 
{
  int RuleNum;       /* セルのアルゴリズムの定義 */
  char *RuleName;       /* ルールの名前 */
    
  /* 以下はセルの操作関数 */
  void (*New)();
  void (*Delete)();
  void (*Step)();
  void (*Random)();
#ifdef __CELLapist__    /* windowを用いる時に必要となる関数 */
  void (*Button)();
  void (*Refresh)();
#endif /* __CELLapist__ */
} RULE;

typedef struct _CELL_WINDOW 
{
#ifdef __CELLapist__
  /* X window 関係 */
  Widget toplevel;      /* 画面のトップレベルウイジェット */
  Display *disp;        /* 画面に対するディスプレイ構造体 */
  Widget field;         /* セルを書くフィールド */
  Pixmap pix;           /* セル用のピックスマップ */
  XColor Color[256];    /* カラーのpixel値 */
  unsigned long cells[COLOR_MAX];
  GC     gc;            /* GC */
  XtIntervalId  Run_timeout; 
  XFontStruct   *font;
  /* X window用の変数群 */
  int depth;            /* 画面の深さ */
  int colormax;         /* 現在確保しているカラーの最大値 */
  int size;             /* 1セルの大きさ(pixel) */
  int time;             /* 更新時間 (msec) */
  /* Cursor variable */
  unsigned long sp;
  unsigned long n_st;
#endif /* __CELLapist__ */
  int x;                /* x軸方向のセルの数 */
  int y;                /* y軸方向のセルの数 */
  int epoch;            /* 世代 */
  int rules;            /* 現在あるルールの数 */
  int rule_num;         /* 現在使っているルール */
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

/* 各セルの定義 */
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
