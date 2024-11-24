/* Lookup table */
int conveyor_forward[] = 
{
  0,0,0,0,                              /* padding */
  CONVEYOR_UP,                          /* 4 */
  0,0,0,                                /* padding */
  CONVEYOR_RIGHT,                        /* 8 */
  0,0,0,0,0,0,0,                        /* padding */
  CONVEYOR_DOWN,                       /* 16 */
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* padding */
  CONVEYOR_LEFT,                        /* 32 */
};

int conveyor_right[] = 
{
  0,0,0,0,                              /* padding */
  CONVEYOR_RIGHT,                       /* 4 */
  0,0,0,                                /* padding */
  CONVEYOR_DOWN,                        /* 8 */
  0,0,0,0,0,0,0,                        /* padding */
  CONVEYOR_LEFT,                        /* 16 */
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* padding */
  CONVEYOR_UP,                          /* 32 */
};

int conveyor_backward[] = 
{
  0,0,0,0,                              /* padding */
  CONVEYOR_DOWN,                        /* 4 */
  0,0,0,                                /* padding */
  CONVEYOR_LEFT,                        /* 8 */
  0,0,0,0,0,0,0,                        /* padding */
  CONVEYOR_UP,                          /* 16 */
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* padding */
  CONVEYOR_RIGHT,                       /* 32 */
};
  
int conveyor_left[] = 
{
  0,0,0,0,                              /* padding */
  CONVEYOR_LEFT,                        /* 4 */
  0,0,0,                                /* padding */
  CONVEYOR_UP,                          /* 8 */
  0,0,0,0,0,0,0,                        /* padding */
  CONVEYOR_RIGHT,                       /* 16 */
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* padding */
  CONVEYOR_DOWN,                        /* 32 */
};

int conveyor_Lrotate[] = 
{
  0,0,0,0,                              /* padding */
  0,                                    /* 4 (UP)*/
  0,0,0,                                /* padding */
  6,                                    /* 8 (RIGHT)*/
  0,0,0,0,0,0,0,                        /* padding */
  4,                                    /* 16 (DOWN)*/
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* padding */
  2,                                    /* 32 (LEFT)*/
};

int conveyor_Rrotate[] = 
{
  0,0,0,0,                              /* padding */
  0,                                    /* 4 (UP)*/
  0,0,0,                                /* padding */
  2,                                    /* 8 (RIGHT)*/
  0,0,0,0,0,0,0,                        /* padding */
  4,                                    /* 16 (DOWN)*/
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* padding */
  6,                                    /* 32 (LEFT)*/
};
