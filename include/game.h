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
 * @version     1.0.0 - 18-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

#ifndef __GAME_H
#define __GAME_H


/**
 * @file game.h
 *
 * @brief The mazeGame game functions.
 */

 #include <stdio.h>
 #include <stdlib.h>

 #include "../include/display.h"

 void waiter(Display display);

 /**
  * @brief Init the game process.
  * @param display the ncurses display containing the loaded maze.
  */
 void initGame(Display display);

 /**
  * @brief Launch the game from a loaded display.
  * @param display the ncurses display containing the loaded maze.
  */
 void launchGame(Display display);

#endif
