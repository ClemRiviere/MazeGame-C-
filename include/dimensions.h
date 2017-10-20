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

#ifndef __DIMENSIONS_H
#define __DIMENSIONS_H


/**
 * @file dimensions.h
 *
 * @brief The maze Dimensions struct.
 */

 #include <stdio.h>
 #include <stdlib.h>

 /**
  * @brief Dimensions of a 2D tab.
  *
  * The rows and cols of a 2 dimensions tab.
  */
 typedef struct{
     int row;    /**< Rows number */
     int col;    /**< Cols number */
 } Dimensions;

#endif
