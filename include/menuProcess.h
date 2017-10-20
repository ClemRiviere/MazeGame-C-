/* -*- c-basic-offset: 3 -*-
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students.
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */

/**
 * @author Clément Rivière <criviere@ecole.ensicaen.fr>
 * @version     1.0.1 - 16-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

#ifndef __MENU_PROCESS_H
#define __MENU_PROCESS_H


/**
 * @file menuProcess.h
 *
 * @brief All the mazeGame menu functions processes.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include <dirent.h>

 #include "../include/interface.h"
 #include "../include/const.h"
 #include "../include/maze.h"
 #include "../include/game.h"

 /**
  * @brief Launch the creation of a new maze.
  * @param interface the ncurses interface.
  *
  * @return 0 if the creation have been well executed.
  */
 int createProcess(Interface *interface);

 /**
  * @brief Get the new maze name from user.
  * @param interface the ncurses interface.
  */
 void getMazeName(Interface *interface);

 /**
  * @brief Ask if the user wants to overwrite a maze called the same name.
  * @param interface the ncurses interface.
  */
 int getOverwrite(Interface *interface);

 /**
  * @brief Load a maze.
  * @param interface the ncurses interface.
  *
  * @return 0 if the loading have been well executed.
  */
 int loadProcess(Interface *interface);

 /**
  * @brief Get the number of saved maze.
  *
  * @return the number of save files.
  */
 int getSavesNumber();

 /**
  * @brief Files the list with the save files names.
  * @param list the string list containing file names.
  */
 void fillSaveList(char **list);

 /**
  * @brief Waiting for the user to choose a maze to load.
  * @param interface the ncurses interface.
  * @param list the list of save files.
  * @param nSaves the number of save files.
  *
  * @return 1 if a maze have been selected, 0 if the program have been exited.
  */
 int selectMaze(Interface *interface, char **list, int nSaves);

 #endif
