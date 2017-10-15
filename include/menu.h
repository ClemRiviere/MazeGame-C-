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

 #include "../include/maze_function.h"
 #include "../include/display.h"

 /**
  * @brief Launch the game menu.
  * @param display the ncurses display.
  */
 void launchMenu(Display display);

 /**
  * @brief Launch the creation of a new maze.
  * @param display the ncurses display.
  */
 void create(Display display);

 #endif
