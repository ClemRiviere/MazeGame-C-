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
 * @version     1.0.0 - 16-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

#ifndef __DISPLAY_H
#define __DISPLAY_H


/**
 * @file display.h
 *
 * @brief All the functions needed to display ncurses windows on the screen.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/ioctl.h>
 #include <locale.h>
 #include <ncurses.h>

 #include "../include/maze_function.h"
 /**
  * @brief The ncurses display
  *
  * The two windows of our display
  */
 typedef struct{
   WINDOW *main_window;           /**< The main window */
   WINDOW *secondary_window;      /**< The secondary_window */
   struct winsize terminal_size;  /**< The size of the terminal */
   Maze *maze;
 } Display;

 /**
  * @brief Initialize the display struct.
  * @param display the display that needs to be initialized.
  */
 void initDisplay(Display *display);

 /**
  * @brief Clear the windows of the display
  * @param display the display that needs to be cleared.
  */
 void clearDisplay(Display display);

 /**
  * @brief Print the ascii title in the main window
  * @param display the display that needs to be displayed.
  */
 void printTitle(Display display);

 /**
  * @brief Request the dimensions of the maze.
  *
  * @param display the display in which we are displaying indications
  * @param d a pointer on the dimension struct of the maze.
  * @todo adding controls on entries
  */
 void getDimensions(Display display, Dimensions *d);

 /**
  * @brief Display the maze
  *
  * @param display the displayed display struct
  */
 void displayMaze(Display display);

 /**
  * @brief Activate the highlighting for the next printed element
  * @param display the display that needs to be modified.
  */
 void activateHighlight(Display display);

 /**
  * @brief Stoping the highlighting for the next printed element
  * @param display the display that needs to be modified.
  */
 void stopHighlight(Display display);

 /**
  * @brief Refresh the ncurses display
  * @param display the display that needs to be refreshed
  */
 void refreshDisplay(Display display);

 /**
  * @brief Print a text in the main window at the selected position
  * @param display the display that needs to be printed
  * @param x the x position of the text
  * @param y the y position of the text
  * @param text the text the printed text.
  */
 void printMain(Display display, int x, int y, char *text);

 /**
  * @brief Prints a message in the second window
  * @param display the display that needs to be printed
  * @param text the printed message.
  */
 void printMessage(Display display, char *text);

 /**
  * @brief Get an int input from the display
  * @param display the display in which the question is answered.
  * @param var a pointer of the target variable.
  */
 void getIntInput(Display display, int *var);

 /**
  * @brief Get a string input from the display
  * @param display the display in which the question is answered.
  * @param pattern the pattern of the answer
  * @param var a pointer of the target variable.
  */
 void getStringInput(Display display,char *pattern, char *var);

 /**
  * @brief Deleting windows and ending the display.
  * @param display the display that needs to be ended.
  */
 void finishDisplay(Display display);

 /**
  * @brief Load a maze into the display struct.
  * @param display the display that needs to be modified.
  * @param maze the loaded maze.
  */
 void loadMaze(Display *display,Maze *maze);

#endif
