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

 #include "../include/interface.h"
 #include "../include/directions.h"

 /**
  * @brief Checking if the player can go in a defined direction.
  * @param interface the ncurses interface containing the maze.
  * @param player the game player.
  * @param dir the selected direction.
  */
 int checkDir(Interface interface,Player player,Directions dir);

 /**
  * @brief Check if the game is finish.
  * @param interface the ncurses interface containing the loaded maze.
  * @param player the game player.
  */
 int gameFinish(Interface interface,Player player);

 /**
  * @brief Process the game (mooves of the player ...).
  * @param interface the ncurses interface containing the loaded maze.
  * @param player the game player.
  * @return an int to specify if the player wants to get back to menu or exit the game.
  */
 int gameProcess(Interface interface, Player *player);

 /**
  * @brief Init the game process.
  * @param interface the ncurses interface containing the loaded maze.
  * @param player the game player.
  */
 void initGame(Interface interface,Player *player);

 /**
  * @brief Launch the game from a loaded interface.
  * @param interface the ncurses interface containing the loaded maze.
  * @return an int to specify if the player wants to get back to menu or exit the game.
  */
 int launchGame(Interface interface);

#endif
