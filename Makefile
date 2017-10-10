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
CPPFLAGS = -Wall -Wextra
CCFLAGS = -ansi

# All directories of files.
INCLUDE_DIR = ./include
SRC_DIR = ./src
LIB_DIR = ./lib
BIN_DIR = ./bin
DOC_DIR = ./doc

.PHONY: all clean distclean

all: $(APP)

$(APP): $(SRC_DIR)/main.o $(SRC_DIR)/maze_function.o
	$(CC) $(LDFLAGS) $^ -o $(BIN_DIR)/$@

# When the .h name is different than the target, we need to define the dependences here
#
# Exemple :
# A.o : B.h
# Here, when B.h will change, A.o will be recompilated.

main.o : maze_function.h

# When the .h name is the same than the target one, we just use %
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h
	$(CC) $(CPPFLAGS) $(CCFLAGS) -c -I $(INCLUDE_DIR) -o $@ $<

clean:
	$(RM) $(SRC_DIR)/*.o

distclean: clean
	$(RM) $(BIN_DIR)/$(APP)

docclean:
	$(RM) -rf $(DOC_DIR)/html/
	$(RM) -rf $(DOC_DIR)/latex/

doxyfile.inc:
	echo INPUT = ./include ./src > $(DOC_DIR)/doxyfile.inc
	echo FILE_PATTERNS = *.h *.c >> $(DOC_DIR)/doxyfile.inc
	echo OUTPUT_DIRECTORY = $(DOC_DIR) >> $(DOC_DIR)/doxyfile.inc

doc: doxyfile.inc $(APP)
	doxygen $(DOC_DIR)/doxyfile.mk
