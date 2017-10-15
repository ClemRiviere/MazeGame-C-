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

#ifndef __MAIN_H
#define __MAIN_H


/**
 * @file main.h
 *
 * @brief The main function of the mazeGame program.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "../include/maze_function.h"
 #include "../include/menu.h"
 #include "../include/display.h"

 /**
  * @brief The main function of the program
  * Gets the dimensions of the maze
  * Creates the maze
  * Initializes the maze with walls
  * Displays the maze
  * Destroys the maze
  * @return 0 if the program have been well executed
  */
 int main(void);


#endif
