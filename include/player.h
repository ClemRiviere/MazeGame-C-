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
 * @version     1.0.0 - 19-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

#ifndef __PLAYER_H
#define __PLAYER_H


/**
 * @file player.h
 *
 * @brief The mazeGame player.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "../include/position.h"
 #include "../include/directions.h"
 #include "../include/maze.h"

 /**
  * @brief A mazeGame player.
  *
  * The position, name and score of the player.
  */
 typedef struct{
   Position pos;  /**< The position of the player */
   char *name;    /**< The name of the player */
   int score;     /**< The current score of the player */
 }Player;

 /**
  * @brief Initialize the player.
  * @param player the player that needs to be initialized.
  * @param maze the maze.
  */
void initPlayer(Player *player, Maze maze);

/**
 * @brief Initialize the player.
 * @param maze the maze.
 * @param player the player that needs to be mooved.
 * @param dir the direction where to moove.
 */
void moovePlayer(Player *player, Maze *maze, Directions dir);

#endif
