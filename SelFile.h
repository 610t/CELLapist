#include "X_include.h"

extern int XsraSelFile(Display *display, unsigned char *prompt, unsigned char   *ok, unsigned char *cancel, char *init_path, int (*show_entry)(), char **path_return);
extern void SFdrawList(int n, int doScroll);
extern void SFinitFont(void);
extern void SFcreateGC(void);
extern void SFsetText(char *path); 
extern void SFupdatePath(void);
extern int SFchdir(char *path);


/*
SFchdir
*/
