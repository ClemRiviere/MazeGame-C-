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

#ifndef __INTERFACE_H
#define __INTERFACE_H


/**
 * @file interface.h
 *
 * @brief All the functions needed to interface ncurses windows on the screen.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/ioctl.h>
 #include <locale.h>
 #include <ncurses.h>
 #include <math.h>

 #include "../include/maze.h"
 #include "../include/player.h"
 #include "../include/const.h"
 /**
  * @brief The ncurses interface
  *
  * The two windows of our interface
  */
 typedef struct{
   WINDOW *main_window;           /**< The main window */
   WINDOW *secondary_window;      /**< The secondary_window */
   struct winsize terminal_size;  /**< The size of the terminal */
   Maze maze;
   int init;
 } Interface;

 /**
  * @brief Initialize the interface struct.
  * @param interface the interface that needs to be initialized.
  */
 void initInterface(Interface *interface);

 /**
  * @brief Clear the windows of the interface
  * @param interface the interface that needs to be cleared.
  */
 void clearInterface(Interface interface);

 /**
  * @brief Print the ascii title in the main window
  * @param interface the interface that needs to be interfaceed.
  */
 void printTitle(Interface interface);


 /**
  * @brief Prints the current loaded maze
  * @param interface the interface that needs to be updated.
  */
 void printLoadedMaze(Interface interface);

 /**
  * @brief Request the dimensions of the maze.
  *
  * @param interface the interface in which we are interfaceing indications
  * @param d a pointer on the dimension struct of the maze.
  * @todo adding controls on entries
  */
 void getDimensions(Interface interface, Dimensions *d);

 /**
  * @brief Display the maze
  *
  * @param interface the interfaceed interface struct
  */
 void displayMaze(Interface interface);

 /**
  * @brief Clear the player on screen.
  *
  * @param interface the interfaceed interface struct
  * @param player the mazeGame player.
  */
 void clearPlayer(Interface interface, Player player);

 /**
  * @brief Display the player.
  *
  * @param interface the interface struct
  * @param player the mazeGame player.
  */
 void displayPlayer(Interface interface, Player player);

 /**
  * @brief Print the player score.
  *
  * @param interface the interface struct
  * @param player the mazeGame player.
  */
 void printScore(Interface interface, Player player);

 /**
  * @brief Activate the highlighting for the next printed element
  * @param interface the interface that needs to be modified.
  */
 void activateHighlight(Interface interface);

 /**
  * @brief Stoping the highlighting for the next printed element
  * @param interface the interface that needs to be modified.
  */
 void stopHighlight(Interface interface);

 /**
  * @brief Refresh the ncurses interface
  * @param interface the interface that needs to be refreshed
  */
 void refreshInterface(Interface interface);

 /**
  * @brief Print a text in the main window at the selected position
  * @param interface the interface that needs to be printed
  * @param x the x position of the text
  * @param y the y position of the text
  * @param text the text the printed text.
  */
 void printMain(Interface interface, int x, int y, char *text);

 /**
  * @brief Prints a message in the second window
  * @param interface the interface that needs to be printed
  * @param text the printed message.
  */
 void printMessage(Interface interface, char *text);

 /**
  * @brief Get an int input from the interface
  * @param interface the interface in which the question is answered.
  * @param var a pointer of the target variable.
  */
 void getIntInput(Interface interface, int *var);

 /**
  * @brief Get a string input from the interface
  * @param interface the interface in which the question is answered.
  * @param pattern the pattern of the answer
  * @param var a pointer of the target variable.
  */
 void getStringInput(Interface interface,char *pattern, char *var);

 /**
  * @brief Wait for a user entry while printing texts.
  * @param interface the listened interface.
  * @param mainText the text to display in the main window.
  * @param secondaryText the text to display in the secondary window.
  * @return an int to specify if the player pressed the exit key or the entry key.
  */
 int waiterInterface(Interface interface, char *mainText, char *secondaryText);

 /**
  * @brief Display the scoreboard
  * @param interface the ncurses interface.
  * @param player the game player.
  * @param pos the position of the player in the scoreboard.
  *
  * @return an int to specify if the player pressed the exit key or the entry key.
  */
 int displayScoreboard(Interface interface, Player player, int pos);

 /**
  * @brief Deleting windows and ending the interface.
  * @param interface the interface that needs to be ended.
  */
 void finishInterface(Interface interface);

#endif
