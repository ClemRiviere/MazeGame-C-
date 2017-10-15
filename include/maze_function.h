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
 * @version     1.0.2 - 16-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

#ifndef __MAZE_FUNCTION_H
#define __MAZE_FUNCTION_H


/**
 * @file maze_function.h
 *
 * @brief All the functions needed to interact with the maze for the maze generator program.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <stdarg.h>
 #include <ncurses.h>

 #include "../include/display.h"

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
  * @brief Position of a element in a maze.
  *
  * The coords of any element of the maze
  */
 typedef struct{
     int x;    /**< The X position : the row */
     int y;    /**< The Y position : the col */
 } Position;

 /**
  * @brief The maze structure.
  *
  * The grid and the dimensions of the maze.
  */
 typedef struct{
     int ** grid;       /**< The 2D int tab that corresponds to the maze grid */
     Dimensions d;      /**< The dimensions of the maze */
     Position * walls;  /**< The walls in the maze */
     int n_walls;       /**< The number of center walls (without the contour) */
 } Maze;

 /**
  * @brief Request the dimensions of the maze.
  *
  * @param d a pointer on the dimension struct of the maze.
  * @todo adding controls on entries
  */
 void getDimensions(Display display, Dimensions *d);

 /**
  * @brief Allocate memory for the maze row*col int tab.
  *
  * @param d the dimensions of the maze.
  * @return maze the allocated maze tab.
  */
 Maze createMaze(Dimensions d);

 /**
  * @brief Free the maze allocated memory
  *
  * @param maze the maze tab that needs to bee free
  */
 void destroyMaze(Maze *maze);

 /**
  * @brief Inititalize the maze : set the WALL and BLANK case
  *
  * @param maze the maze tab that needs to bee initialized
  */
 void initMaze(Maze *maze);

 /**
  * @brief Display the maze
  *
  * @param maze the displayed maze
  */
 void displayMaze(Display display,Maze maze);

 /**
  * @brief Generate a perfect maze from an initialized one
  *
  * @param maze the maze that will be transformed.
  */
 void generateMaze(Maze *maze);

 /**
  * @brief The process of one generation step
  *
  * @param maze the maze that will be transformed.
  * @param nb_broken the number of broken walls
  * @return 0 if the generation is not finished yet.
  */
 int processMazeGeneration(Maze *maze,int *nb_broken);

 /**
  * @brief Test if the generation is finished
  *
  * @param maze the displayed maze
  * @param nb_broken the number of broken walls
  * @return an int at 1 if it's finished, otherwise at 0
  * @todo improve the if conditions
  */
 int generation_end(Maze maze,int nb_broken);

 /**
  * @brief Delete a wall that have been broken from the maze walls tab
  *
  * @param maze the maze that will be transformed.
  * @param pos the position of the wall to destroy in the walls tab.
  */
 void delete_wall(Maze *maze, int pos);

 /**
  * @brief Fill id of adjacent cells
  *
  * @param maze the maze that will be transformed.
  * @param pos the position of the current cell
  * @todo improve the if conditions
  */
 void fill_id(Maze *maze, Position pos);


#endif
