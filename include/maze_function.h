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
 * @todo Implement the maze struct
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
  * @brief The maze structure.
  *
  * The grid and the dimensions of the maze.
  */
 typedef struct{
     int ** grid;     /**< The 2D int tab that corresponds to the maze grid */
     Dimensions d;  /**< The dimensions of the maze */
 } Maze;

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
 Maze createMaze(Dimensions d);

 /**
  * @brief Free the maze allocated memory
  *
  * @param maze the maze tab that needs to bee free
  * @param d the dimensions of the maze
  * @see Dimensions
  */
 void destroyMaze(Maze *maze);

 /**
  * @brief Inititalize the maze : set the WALL and BLANK case
  *
  * @param maze the maze tab that needs to bee initialized
  * @param d the dimensions of the maze
  * @see Dimensions
  */
 void initMaze(Maze *maze);

 /**
  * @brief Display the maze
  *
  * @param maze the displayed maze
  * @param d the dimensions of the maze
  * @see Dimensions
  */
 void displayMaze(Maze maze);

 /**
  * @brief Generate a perfect maze from an initialized one.
  *
  * @param maze the maze that will be transformed.
  * @param d the dimensions of the maze
  * @see Dimensions
  */
 /* void generateMaze(Maze maze); */


#endif
