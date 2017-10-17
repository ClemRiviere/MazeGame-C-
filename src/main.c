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

/**
 * @file main.c
 *
 * @brief The main function of the maze generator program.
 * First version of the program, only create the maze, initialize the walls, and display.
 * There is no generation of maze for the moment, it's just a tab.
 */

#include "../include/main.h"

int main(void){
    /*Dimensions dim;
    Maze maze;
    getDimensions(&dim);
    maze = createMaze(dim);
    initMaze(&maze);
    generateMaze(&maze);
    displayMaze(maze);
    destroyMaze(&maze);*/

    Display display;
    initDisplay(&display);
    launchMenu(display);
    return 0;
}
