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
 * @version     1.0.0 - 11-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

/**
 * @file main.c
 *
 * @brief The main function of the maze generator program.
 * First version of the program, only create the maze, initialize the walls, and display.
 * There is no generation of maze for the moment, it's just a tab.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/maze_function.h"

/**
 * @brief The main function of the program
 * Gets the dimensions of the maze
 * Creates the maze
 * Initializes the maze with walls
 * Displays the maze
 * Destroys the maze
 */
int main(void){
    Dimensions dim;
    Maze maze;
    int res;
    int nb_broken = 0;
    getDimensions(&dim);
    maze = createMaze(dim);
    initMaze(&maze);
    do{
      res = generateMaze(&maze,&nb_broken);
    }while(res == 0);
    displayMaze(maze);
    destroyMaze(&maze);
    return 0;
}
