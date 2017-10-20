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

#ifndef __DIRECTIONS_H
#define __DIRECTIONS_H


/**
 * @file directions.h
 *
 * @brief Playable directions.
 */

 #include <stdio.h>
 #include <stdlib.h>

 /**
  * @brief Directions selected by the player.
  *
  * The 4 playable directions.
  */
  typedef enum{
    INVALID = 0, UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4
  } Directions;

#endif
