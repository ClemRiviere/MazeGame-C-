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
 * @file maze.h
 *
 * @brief All the functions needed to interact with the maze for the maze generator program.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <stdarg.h>
 #include <ncurses.h>
 #include <string.h>

 #include "../include/const.h"
 #include "../include/position.h"
 #include "../include/dimensions.h"

 /**
  * @brief The maze structure.
  *
  * The grid and the dimensions of the maze.
  */
 typedef struct{
     int **grid;        /**< The 2D int tab that corresponds to the maze grid */
     Dimensions d;      /**< The dimensions of the maze */
     Position *walls;   /**< The walls in the maze */
     int n_walls;       /**< The number of center walls (without the contour) */
     char *name;        /**< The name of the maze */
 } Maze;

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
  * @param maze the maze tab that needs to be initialized
  */
 void initMaze(Maze *maze);

 /**
  * @brief Check if a maze is not already saved to this name
  *
  * @param maze the maze needs to be checked
  * @return 1 if the maze exists, 0 if not.
  */
 int exist(Maze maze);

 /**
  * @brief Save a maze into a file
  *
  * @param maze the maze tab that needs to be saved
  * @return 0 if the save have been completed successfully.
  */
 int saveMaze(Maze maze);

 /**
  * @brief Read a maze from a file.
  *
  * @param name the file name.
  * @return the readed maze.
  */
 Maze readMaze(char *name);

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
  * @brief Generate objects such as chests and traps.
  *
  * @param maze the maze that will be transformed.
  * @param mode the generation mode (TRAP_MODE or CHEST_MODE)
  */
 void generateObject(Maze *maze, int mode);

 /**
  * @brief Test if the generation is finished
  *
  * @param maze the generated maze
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
