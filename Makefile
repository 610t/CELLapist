# MACHINE = -DNEWS
MACHINE = -DFreeBSD -DMY_XAW3D
CFLAGS  = -g -D__CELLapist__  -D__NoAlloc__ -D__LargeLoad__ -I/usr/X11R6/include ${MACHINE} 
# -D__GA_ROTATE__
#		locate.c carry.c\
#		locateNew.c carryNew.c \
SRC	= main.c window.c buttons.c state.c field.c \
	getline.c \
	file.c Rule.c \
		SelFile.c Dir.c Path.c Draw.c \
	Wolfram.c WolframWin.c \
	Life.c \
	Diffuse.c \
	Conveyor.c ConveyorRule4.c ConveyorRule8.c ConveyorRuleGA.c ConveyorDraw.c \
	        ConveyorRule4Rand.c \
	        ConveyorRule4MOD.c \
	        ConveyorRule8New.c \
	        ConveyorRule8Fujita.c \
		GA.c GAfile.c\
		locateNew.c carryNew.c \
	2DRoad.c 2DRoadDraw.c\
	Rho.c RhoRuleGA.c RhoDraw.c \
	Pattern.c PatternRule.c PatternDraw.c \
	Spread.c 
HEADER 	=
OBJ	= ${SRC:.c=.o}
# LIB     =  -lXaw -lXmu -lXt -lX11 -lXext -lm  -L/usr/X11R5/lib
LIB     =  -lXaw3d -lXmu -lXt -lX11 -lSM -lICE -lXext -lX11 -lm  -L/usr/X11R6/lib
CC      = gcc
#CC      = gcc-sparc-sun-sunos4.1

CAs: ${OBJ} ${HEADER}
	${CC} -g -o $@ ${OBJ} ${LIB}
clean:
	\rm -f ${OBJ_DIR}*.o core ${SRC_DIR}*~

# DO NOT DELETE THIS LINE -- make depend depends on it.

2DRoad.o: 2DRoad.h /usr/include/stdio.h /usr/include/sys/types.h
2DRoad.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
2DRoad.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
2DRoad.o: /usr/include/math.h types.h constant.h macros.h globals.h
2DRoadDraw.o: 2DRoad.h /usr/include/stdio.h /usr/include/sys/types.h
2DRoadDraw.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
2DRoadDraw.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
2DRoadDraw.o: /usr/include/math.h types.h constant.h macros.h globals.h
2DRoadDraw.o: check.xbm
2DRoadRule.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
2DRoadRule.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
2DRoadRule.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
2DRoadRule.o: /usr/include/math.h types.h constant.h macros.h globals.h
buttons.o: X_include.h buttons.h constant.h types.h globals.h macros.h
callback.o: /usr/include/stdio.h /usr/include/sys/types.h
callback.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
callback.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
callback.o: /usr/include/sys/stat.h /usr/include/sys/time.h
callback.o: /usr/include/sys/time.h
carry.o: /usr/include/math.h /usr/include/sys/cdefs.h X_include.h constant.h
carry.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
carry.o: /usr/include/machine/endian.h /usr/include/machine/ansi.h
carry.o: /usr/include/machine/types.h types.h macros.h globals.h
Conveyor.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
Conveyor.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Conveyor.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Conveyor.o: /usr/include/math.h types.h constant.h macros.h globals.h
Conveyor.o: conveyorLookup.h
ConveyorDraw.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorDraw.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorDraw.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorDraw.o: /usr/include/math.h types.h constant.h macros.h globals.h
ConveyorDraw.o: check.xbm
ConveyorRule4.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorRule4.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorRule4.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorRule4.o: /usr/include/math.h types.h constant.h macros.h globals.h
ConveyorRule4Fujita.o: Conveyor.h /usr/include/stdio.h
ConveyorRule4Fujita.o: /usr/include/sys/types.h /usr/include/sys/cdefs.h
ConveyorRule4Fujita.o: /usr/include/machine/endian.h
ConveyorRule4Fujita.o: /usr/include/machine/ansi.h
ConveyorRule4Fujita.o: /usr/include/machine/types.h /usr/include/math.h
ConveyorRule4Fujita.o: types.h constant.h macros.h globals.h
ConveyorRule4MOD.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorRule4MOD.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorRule4MOD.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorRule4MOD.o: /usr/include/math.h types.h constant.h macros.h globals.h
ConveyorRule4Rand.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorRule4Rand.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorRule4Rand.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorRule4Rand.o: /usr/include/math.h types.h constant.h macros.h
ConveyorRule4Rand.o: globals.h
ConveyorRule8.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorRule8.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorRule8.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorRule8.o: /usr/include/math.h types.h constant.h macros.h globals.h
ConveyorRule8Fujita.o: Conveyor.h /usr/include/stdio.h
ConveyorRule8Fujita.o: /usr/include/sys/types.h /usr/include/sys/cdefs.h
ConveyorRule8Fujita.o: /usr/include/machine/endian.h
ConveyorRule8Fujita.o: /usr/include/machine/ansi.h
ConveyorRule8Fujita.o: /usr/include/machine/types.h /usr/include/math.h
ConveyorRule8Fujita.o: types.h constant.h macros.h globals.h
ConveyorRule8New.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorRule8New.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorRule8New.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorRule8New.o: /usr/include/math.h types.h constant.h macros.h globals.h
ConveyorRuleGA.o: Conveyor.h /usr/include/stdio.h /usr/include/sys/types.h
ConveyorRuleGA.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
ConveyorRuleGA.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
ConveyorRuleGA.o: /usr/include/math.h types.h constant.h macros.h globals.h
Diffuse.o: Diffuse.h /usr/include/stdio.h /usr/include/sys/types.h
Diffuse.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Diffuse.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Diffuse.o: /usr/include/math.h X_include.h types.h constant.h macros.h
Diffuse.o: globals.h
Dir.o: /usr/include/stdio.h /usr/include/sys/types.h /usr/include/sys/cdefs.h
Dir.o: /usr/include/machine/endian.h /usr/include/machine/ansi.h
Dir.o: /usr/include/machine/types.h SFinternal.h /usr/include/sys/dir.h
Dir.o: /usr/include/sys/dirent.h /usr/include/sys/stat.h
Dir.o: /usr/include/sys/time.h /usr/include/sys/time.h
Draw.o: /usr/include/stdio.h /usr/include/sys/types.h
Draw.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Draw.o: /usr/include/machine/ansi.h /usr/include/machine/types.h SFinternal.h
Draw.o: /usr/include/sys/stat.h /usr/include/sys/time.h
Draw.o: /usr/include/sys/time.h
field.o: field.h X_include.h types.h globals.h
file.o: X_include.h globals.h types.h macros.h GA.h
GA.o: /usr/include/stdio.h /usr/include/sys/types.h /usr/include/sys/cdefs.h
GA.o: /usr/include/machine/endian.h /usr/include/machine/ansi.h
GA.o: /usr/include/machine/types.h /usr/include/math.h types.h GA.h Rule.h
GA.o: macros.h
GAfile.o: /usr/include/stdio.h /usr/include/sys/types.h
GAfile.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
GAfile.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
GAfile.o: /usr/include/math.h getline.h GA.h Rule.h macros.h
getline.o: /usr/include/stdio.h /usr/include/sys/types.h
getline.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
getline.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Life.o: Life.h /usr/include/stdio.h /usr/include/sys/types.h
Life.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Life.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Life.o: /usr/include/math.h X_include.h types.h constant.h macros.h globals.h
locate.o: /usr/include/math.h /usr/include/sys/cdefs.h X_include.h constant.h
locate.o: globals.h types.h
main.o: /usr/include/stdio.h /usr/include/sys/types.h
main.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
main.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
main.o: /usr/include/math.h X_include.h buttons.h constant.h types.h
main.o: globals.h macros.h window.h Wolfram.h Life.h Conveyor.h 2DRoad.h
main.o: Diffuse.h Pattern.h Spread.h Rho.h
Path.o: /usr/include/stdio.h /usr/include/sys/types.h
Path.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Path.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Path.o: /usr/include/pwd.h SFinternal.h /usr/include/sys/stat.h
Path.o: /usr/include/sys/time.h /usr/include/sys/time.h
Pattern.o: Pattern.h /usr/include/stdio.h /usr/include/sys/types.h
Pattern.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Pattern.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Pattern.o: /usr/include/math.h X_include.h types.h constant.h macros.h
Pattern.o: globals.h
PatternDraw.o: Pattern.h /usr/include/stdio.h /usr/include/sys/types.h
PatternDraw.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
PatternDraw.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
PatternDraw.o: /usr/include/math.h X_include.h types.h constant.h macros.h
PatternDraw.o: globals.h check.xbm
PatternRule.o: Pattern.h /usr/include/stdio.h /usr/include/sys/types.h
PatternRule.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
PatternRule.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
PatternRule.o: /usr/include/math.h X_include.h types.h constant.h macros.h
PatternRule.o: globals.h
Rho.o: Rho.h /usr/include/stdio.h /usr/include/sys/types.h
Rho.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Rho.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Rho.o: /usr/include/math.h types.h constant.h macros.h globals.h
RhoDraw.o: Rho.h /usr/include/stdio.h /usr/include/sys/types.h
RhoDraw.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
RhoDraw.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
RhoDraw.o: /usr/include/math.h types.h constant.h macros.h globals.h
RhoRuleGA.o: Rho.h /usr/include/stdio.h /usr/include/sys/types.h
RhoRuleGA.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
RhoRuleGA.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
RhoRuleGA.o: /usr/include/math.h types.h constant.h macros.h globals.h
Rule.o: /usr/include/stdio.h /usr/include/sys/types.h
Rule.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Rule.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Rule.o: /usr/include/stdlib.h /usr/include/math.h types.h Rule.h macros.h
Rule.o: GA.h
SelFile.o: /usr/include/stdio.h /usr/include/sys/types.h
SelFile.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
SelFile.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
SelFile.o: /usr/include/sys/param.h /usr/include/sys/syslimits.h
SelFile.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
SelFile.o: /usr/include/machine/trap.h /usr/include/machine/param.h
SelFile.o: /usr/include/machine/limits.h SFinternal.h
Spread.o: Spread.h /usr/include/stdio.h /usr/include/sys/types.h
Spread.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Spread.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Spread.o: /usr/include/math.h X_include.h types.h constant.h macros.h
Spread.o: globals.h
state.o: state.h X_include.h types.h globals.h
window.o: X_include.h window.h constant.h types.h globals.h macros.h
Wolfram.o: Wolfram.h /usr/include/stdio.h /usr/include/sys/types.h
Wolfram.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Wolfram.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Wolfram.o: /usr/include/math.h X_include.h types.h constant.h macros.h
Wolfram.o: globals.h
WolframWin.o: WolframWin.h X_include.h types.h Wolfram.h /usr/include/stdio.h
WolframWin.o: /usr/include/sys/types.h /usr/include/sys/cdefs.h
WolframWin.o: /usr/include/machine/endian.h /usr/include/machine/ansi.h
WolframWin.o: /usr/include/machine/types.h /usr/include/math.h constant.h
WolframWin.o: macros.h globals.h
2DRoad.o: /usr/include/stdio.h /usr/include/sys/types.h
2DRoad.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
2DRoad.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
2DRoad.o: /usr/include/math.h types.h constant.h macros.h
buttons.o: constant.h types.h globals.h macros.h
Conveyor.o: /usr/include/stdio.h /usr/include/sys/types.h
Conveyor.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Conveyor.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Conveyor.o: /usr/include/math.h types.h constant.h macros.h
Diffuse.o: /usr/include/stdio.h /usr/include/sys/types.h
Diffuse.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Diffuse.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Diffuse.o: /usr/include/math.h X_include.h types.h constant.h macros.h
field.o: X_include.h types.h
globals.o: types.h
Life.o: /usr/include/stdio.h /usr/include/sys/types.h
Life.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Life.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Life.o: /usr/include/math.h X_include.h types.h constant.h macros.h
Pattern.o: /usr/include/stdio.h /usr/include/sys/types.h
Pattern.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Pattern.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Pattern.o: /usr/include/math.h X_include.h types.h constant.h macros.h
Rho.o: /usr/include/stdio.h /usr/include/sys/types.h /usr/include/sys/cdefs.h
Rho.o: /usr/include/machine/endian.h /usr/include/machine/ansi.h
Rho.o: /usr/include/machine/types.h /usr/include/math.h types.h constant.h
Rho.o: macros.h
Rule.o: macros.h
Spread.o: /usr/include/stdio.h /usr/include/sys/types.h
Spread.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Spread.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Spread.o: /usr/include/math.h X_include.h types.h constant.h macros.h
state.o: X_include.h types.h
window.o: constant.h types.h globals.h macros.h
Wolfram.o: /usr/include/stdio.h /usr/include/sys/types.h
Wolfram.o: /usr/include/sys/cdefs.h /usr/include/machine/endian.h
Wolfram.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
Wolfram.o: /usr/include/math.h X_include.h types.h constant.h macros.h
WolframWin.o: X_include.h types.h
