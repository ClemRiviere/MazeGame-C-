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
 * @version     0.0.1 - 10-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

#ifndef __MAZE_FUNCTION_H
#define __MAZE_FUNCTION_H


/**
 * @file maze_function.h
 *
 * All the functions needed to interact with the maze for the maze generator program.
 */

 #include <stdio.h>
 #include <stdlib.h>

 /* Define the id of walls to 0. */
 #define WALL 0

 /**
  * @brief Dimensions of a 2D tab.
  *
  * The rows and cols of a 2 dimensions tab.
  */
 typedef struct{
     int row;    /**< Rows number */
     int col;    /**< Cols number */
 } Dimensions;

 /**
  * @brief Request the dimensions of the maze.
  *
  * @param d a pointer on the dimension struct of the maze.
  */
 void getDimensions(Dimensions *d);

 /**
  * @brief Allocate memory for the maze row*col int tab.
  *
  * @param d the dimensions of the maze.
  * @return maze the allocated maze tab.
  * @see Dimensions
  */
 int ** createMaze(Dimensions d);

 /**
  * @brief Free the maze allocated memory
  *
  * @param maze the maze tab that needs to bee free
  * @param d the dimensions of the maze
  * @see Dimensions
  */
 void destroyMaze(int ** maze,Dimensions d);

 /**
  * @brief Inititalize the maze : set the WALL and BLANK case
  *
  * @param maze the maze tab that needs to bee initialized
  * @param d the dimensions of the maze
  * @see Dimensions
  */
 void initMaze(int ** maze,Dimensions d);

 /**
  * @brief Display the maze
  *
  * @param maze the displayed maze
  */
 void displayMaze(int ** maze,Dimensions d);

#endif
