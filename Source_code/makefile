#==============================================================================================
# Makefile for the circle packaging simulation program.
# Author: Dmitry Safonov
# Date: 24.08.2020
#==============================================================================================

CC = gcc
CFLAGS = -c -Wall -Wextra -Wsign-conversion -pedantic-errors -g -o
LFLAGS = -o
SDIR = src
ODIR = build/obj
DDIR = data
EDIR = build
IDIR = include
LDIR = lib
LIBS = -luser32 -lgdi32

all: Directories Data Program

#==============================================================================================
# Rule for creating neccessary directories
#==============================================================================================

.PHONY: Directories
Directories:
	mkdir -p build
	mkdir -p build/obj
	mkdir -p build/data

#==============================================================================================
# Rule for copying data files to the ./build/data directory
#==============================================================================================

.PHONY: Data
Data: $(DDIR)
	cp -u $(DDIR)/*.* $(EDIR)/data/

#==============================================================================================
# Dependences (for further creating the object *.o files):
#==============================================================================================

# Module for the win32 platform (creating the window with win32API)
_DEPS_win32_platform = utils.h simulation.h input_treatment.h simulation_constants.h
DEPS_win32_platform = $(patsubst %,$(IDIR)/%,$(_DEPS_win32_platform))

# Module for the work with input treatment (from mouse and keyboard):
_DEPS_input_treatment = input_treatment.h utils.h
DEPS_input_treatment = $(patsubst %,$(IDIR)/%,$(_DEPS_input_treatment))

# Module for the software rendering functions
_DEPS_software_rendering = software_rendering.h utils.h file_io.h simulation_constants.h
DEPS_software_rendering = $(patsubst %,$(IDIR)/%,$(_DEPS_software_rendering))

# Module for the file_io (working with files)
_DEPS_file_io = file_io.h utils.h stb_image.h
DEPS_file_io = $(patsubst %,$(IDIR)/%,$(_DEPS_file_io))

# Module for the font
_DEPS_font = font.h utils.h file_io.h software_rendering.h simulation_constants.h
DEPS_font = $(patsubst %,$(IDIR)/%,$(_DEPS_font))

# Module for the misc functions
_DEPS_misc = misc.h utils.h
DEPS_misc = $(patsubst %,$(IDIR)/%,$(_DEPS_misc))

# Module for the simualtion class
_DEPS_simualtion = simulation.h software_rendering.h utils.h input_treatment.h file_io.h \
font.h dbg.h debug_console.h simulation_constants.h
DEPS_simualtion = $(patsubst %,$(IDIR)/%,$(_DEPS_simualtion))

# Module for the debug console
_DEPS_debug_console = debug_console.h utils.h software_rendering.h font.h simulation_constants.h
DEPS_debug_console = $(patsubst %,$(IDIR)/%,$(_DEPS_debug_console))

#==============================================================================================
# Rules for compilation of the object *.o files:
#==============================================================================================

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS_%) 
	$(CC) $(CFLAGS) $@ $< -I$(IDIR)

#==============================================================================================
# Rules for the linker:
#==============================================================================================

_OBJ = win32_platform.o input_treatment.o software_rendering.o file_io.o font.o misc.o \
simulation.o debug_console.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

Program: $(OBJ)
	$(CC) $(LFLAGS) $(EDIR)/$@ $^ -L$(LDIR) $(LIBS)
# use flag -s for stipping the executable (to reduce the size)

#==============================================================================================
# Rules for the clean the build firectory:
#==============================================================================================

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o
