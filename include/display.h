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

 /**
  * @brief The ncurses display
  *
  * The two windows of our display
  */
 typedef struct{
   WINDOW *main_window;           /**< The main window */
   WINDOW *secondary_window;      /**< The secondary_window */
   struct winsize terminal_size;  /**< The size of the terminal */
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
  * @brief Refresh the ncurses display
  * @param display the display that needs to be refreshed
  */
 void refreshDisplay(Display display);

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
  * @brief Deleting windows and ending the display.
  * @param display the display that needs to be ended.
  */
 void finishDisplay(Display display);

#endif
