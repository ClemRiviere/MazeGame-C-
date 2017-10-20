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

#ifndef __POSITION_H
#define __POSITION_H


/**
 * @file position.h
 *
 * @brief The maze Position struct.
 */

 #include <stdio.h>
 #include <stdlib.h>

 /**
  * @brief Position of a element in a maze.
  *
  * The coords of any element of the maze
  */
 typedef struct{
     int x;    /**< The X position : the row */
     int y;    /**< The Y position : the col */
 } Position;

#endif
