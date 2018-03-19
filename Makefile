################################################################################
# These are variables for the GBA toolchain build
# You can add others if you wish to
# ***** YOUR NAME HERE *****
################################################################################

# The name of your desired GBA game
# This should be a just a name i.e MyFirstGBAGame
# No SPACES AFTER THE NAME.
PROGNAME = DANKSOULS

# The object files you want to compile into your program
# This should be a space (SPACE!) separated list of .o files
OFILES = main.o mylib.o atk1.o atk2.o atk3.o atk4.o atk5.o atk6.o atk7.o atk8.o atk9.o atk10.o roll1.o roll2.o roll3.o roll4.o roll5.o stand.o run1.o run2.o run3.o fstand.o fwalk1.o fstance1.o fstance2.o fstance3.o fstance4.o fatk1.o fatk2.o fatk3.o fatk4.o fatk5.o fatk6.o start.o youdied.o bg.o bgbot.o win.o

# The header files you have created.
# This is necessary to determine when to recompile for files.
# This should be a space (SPACE!) separated list of .h files
HFILES = mylib.h atk1.h atk2.h atk3.h atk4.h atk5.h atk6.h atk7.h atk8.h atk9.h atk10.h roll1.h roll2.h roll3.h roll4.h roll5.h stand.h run1.h run2.h run3.h fstand.h fwalk1.h fstance1.h fstance2.h fstance3.h fstance4.h fatk1.h fatk2.h fatk3.h fatk4.h fatk5.h fatk6.h start.h youdied.h bg.h bgbot.h win.h

################################################################################
# These are various settings used to make the GBA toolchain work
# DO NOT EDIT BELOW.
################################################################################

TOOLDIR  = /usr/local/cs2110-tools
ARMLIB   = $(TOOLDIR)/arm-thumb-eabi/lib
CFLAGS   = -Wall -Werror -std=c99 -pedantic -Wextra
CFLAGS   += -mthumb-interwork -mlong-calls -nostartfiles -MMD -MP -I $(TOOLDIR)/include
LDFLAGS = -L $(TOOLDIR)/lib \
		  -L $(TOOLDIR)/lib/gcc/arm-thumb-eabi/4.4.1/thumb \
		  -L $(ARMLIB) \
		  --script $(ARMLIB)/arm-gba.ld
CDEBUG   = -g -DDEBUG
CRELEASE = -O2 
CC       = $(TOOLDIR)/bin/arm-thumb-eabi-gcc
AS       = $(TOOLDIR)/bin/arm-thumb-eabi-as
LD       = $(TOOLDIR)/bin/arm-thumb-eabi-ld
OBJCOPY  = $(TOOLDIR)/bin/arm-thumb-eabi-objcopy
GDB      = $(TOOLDIR)/bin/arm-thumb-eabi-gdb
CFILES   = $(OFILES:.o=.c)

################################################################################
# These are the targets for the GBA build system
################################################################################

all : CFLAGS += $(CRELEASE)
all : $(PROGNAME).gba
	@echo "[FINISH] Created $(PROGNAME).gba"

.PHONY : all clean

$(PROGNAME).gba : $(PROGNAME).elf
	@echo "[LINK] Linking objects together to create $(PROGNAME).gba"
	@$(OBJCOPY) -O binary $(PROGNAME).elf $(PROGNAME).gba

$(PROGNAME).elf : crt0.o $(OFILES)
	@$(LD) $(LDFLAGS) -o $(PROGNAME).elf $^ -lgcc -lc -lgcc $(LDDEBUG)
	@rm -f *.d

crt0.o : $(ARMLIB)/crt0.s
	@$(AS) -mthumb-interwork $^ -o crt0.o

%.o : %.c
	@echo "[COMPILE] Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o : %.s                                                                        
	@echo "[ASSEMBLE] Assembling $<"                                               
	@$(AS) $< -o $@ -mthumb -mthumb-interwork

clean :
	@echo "[CLEAN] Removing all compiled files"
	@rm -f *.o *.elf *.gba *.d

vba : CFLAGS += $(CRELEASE)
vba : $(PROGNAME).gba
	@echo "[EXECUTE] Running Emulator VBA-M"
	@vbam $(VBAOPT) $(PROGNAME).gba > /dev/null 2> /dev/null

med : CFLAGS += $(CRELEASE)
med : $(PROGNAME).gba
	@echo "[EXECUTE] Running emulator Mednafen"
	@mednafen $(PROGNAME).gba > /dev/null 2>&1

-include $(CFILES:%.c=%.d)

