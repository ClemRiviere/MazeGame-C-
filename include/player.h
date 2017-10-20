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

 typedef struct{
   Position pos;
   char *name;
 }Player;

 /**
  * @brief Initialize the player.
  * @param player the player that needs to be initialized.
  */
void initPlayer(Player *player);

/**
 * @brief Initialize the player.
 * @param player the player that needs to be mooved.
 * @param dir the direction where to moove.
 */
void moovePlayer(Player *player, Directions dir);

#endif
