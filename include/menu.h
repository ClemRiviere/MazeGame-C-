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

#ifndef __MENU_H
#define __MENU_H


/**
 * @file menu.h
 *
 * @brief All the mazeGame menu fonctions.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include <dirent.h>

 #include "../include/interface.h"
 #include "../include/const.h"
 #include "../include/menuProcess.h"

 /**
  * @brief Get the x position of the next printed menu option
  * @param row the row number of the terminal
  * @param i the id of the menu option
  */
 int getPosX(int row,int i);

 /**
  * @brief Initialize the game menu.
  * @param interface the ncurses interface.
  * @param list the option list with their descriptions
  */
 void initMenu(Interface *interface,char * list[4][2]);

 /**
  * @brief Waiting for a menu selection.
  * @param interface the ncurses interface.
  * @param list the option list with their descriptions
  *
  * @return an int corresponding to the selected option
  */
 int selectMenu(Interface interface,char * list[4][2]);

 /**
  * @brief Processing the selected menu option.
  * @param interface the ncurses interface.
  * @param select the selected option.
  */
 void interactMenu(Interface interface,int select);

 /**
  * @brief Launch the game menu.
  * @param interface the ncurses interface.
  */
 void launchMenu(Interface interface);

 #endif
