#
# Makefile
#
# @author Clément Rivière <criviere@ecole.ensicaen.fr>
#
# ENSICAEN
# 6, boulevard Maréchal Juin
# F-14050 Caen cedex
#
# Compile the mazeGame program.

APP = mazeGame
CC = gcc
RM = rm
RMFLAGS = -rf
CPPFLAGS = -Wall -Wextra
CCFLAGS = -ansi
LDFLAGS = -lncursesw

# All directories of files.
INCLUDE_DIR = ./include
SRC_DIR = ./src
LIB_DIR = ./lib
BIN_DIR = ./bin
DOC_DIR = ./doc
OBJ_DIR = ./src/obj

DOXYFILE = doxyfile
HTML = YES
LATEX = NO
RTF = NO

SOURCES  := $(wildcard $(SRC_DIR)/*.c)
OBJECTS  := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean distclean docclean

all: createObjectTree $(APP)

$(APP): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $(BIN_DIR)/$@

createObjectTree:
	mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/interface.h
$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/maze.h
$(OBJ_DIR)/main.o: $(INCLUDE_DIR)/menu.h

$(OBJ_DIR)/display.o: $(INCLUDE_DIR)/maze.h

$(OBJ_DIR)/menu.o: $(INCLUDE_DIR)/interface.h
$(OBJ_DIR)/menu.o: $(INCLUDE_DIR)/menuProcess.h

$(OBJ_DIR)/menuProcess.o: $(INCLUDE_DIR)/interface.h
$(OBJ_DIR)/menuProcess.o: $(INCLUDE_DIR)/maze.h
$(OBJ_DIR)/menuProcess.o: $(INCLUDE_DIR)/game.h

$(OBJ_DIR)/game.o: $(INCLUDE_DIR)/interface.h

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h $(INCLUDE_DIR)/const.h
	$(CC) $(CPPFLAGS) $(CCFLAGS) -c -I $(INCLUDE_DIR) -o $@ $<

clean:
	$(RM) $(RMFLAGS) $(OBJ_DIR)

distclean: clean
	$(RM) $(RMFLAGS) $(BIN_DIR)/$(APP)
	$(RM) $(RMFLAGS) $(DOC_DIR)/$(DOXYFILE)

docclean:
	$(RM) $(RMFLAGS) $(DOC_DIR)/*

doxysetup:
	-touch $(DOC_DIR)/$(DOXYFILE)
	-echo PROJECT_NAME = "$(APP)" > $(DOC_DIR)/$(DOXYFILE)
	-echo EXCLUDE = >> $(DOC_DIR)/$(DOXYFILE)
	-echo INPUT = $(SRC_DIR) $(INCLUDE_DIR) >> $(DOC_DIR)/$(DOXYFILE)
	-echo FILE_PATTERNS = *.h *.c >> $(DOC_DIR)/$(DOXYFILE)
	-echo GENERATE_LATEX = $(LATEX) >> $(DOC_DIR)/$(DOXYFILE)
	-echo GENERATE_HTML = $(HTML) >> $(DOC_DIR)/$(DOXYFILE)
	-echo GENERATE_RTF = $(RTF) >> $(DOC_DIR)/$(DOXYFILE)
	-echo OUTPUT_DIRECTORY = $(DOC_DIR) >> $(DOC_DIR)/$(DOXYFILE)

doc: doxysetup createObjectTree $(APP)
	-doxygen $(DOC_DIR)/$(DOXYFILE)
