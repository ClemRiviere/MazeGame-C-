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

/**
 * @file display.c
 *
 * @brief The mazeGame display functions.
 */

 #include "../include/display.h"

 void initDisplay(Display *display){
   ioctl(0, TIOCGWINSZ, &display->terminal_size);
   /* Necessary to print utf-8 chars */
   setlocale(LC_ALL, "");
   /* Initialize ncurses */
   initscr();

   display->main_window = newwin(display->terminal_size.ws_row-5,display->terminal_size.ws_col-2,1,1);
   box(display->main_window,0,0);
   display->secondary_window = newwin(3,display->terminal_size.ws_col-2,display->terminal_size.ws_row-4,1);
   box(display->secondary_window,0,0);
 }

 void clearDisplay(Display display){
   wclear(display.main_window);
   wclear(display.secondary_window);
   box(display.main_window,0,0);
   box(display.secondary_window,0,0);
   refreshDisplay(display);
 }

 void printTitle(Display display){
   int i;
   char * ascii_title[6] = {"███╗   ███╗ █████╗ ███████╗███████╗ ██████╗  █████╗ ███╗   ███╗███████╗",
                            "████╗ ████║██╔══██╗╚══███╔╝██╔════╝██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
                            "██╔████╔██║███████║  ███╔╝ █████╗  ██║  ███╗███████║██╔████╔██║█████╗  ",
                            "██║╚██╔╝██║██╔══██║ ███╔╝  ██╔══╝  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
                            "██║ ╚═╝ ██║██║  ██║███████╗███████╗╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
                            "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"};
   for (i=0;i<6;i++){
     /* Displays the ascii_art */
     mvwprintw(display.main_window, i+6, (display.terminal_size.ws_col-71)/2, "%s", ascii_title[i]);
   }
   refreshDisplay(display);
 }

 void refreshDisplay(Display display){
   wrefresh(display.main_window); /* update the terminal screen */
   wrefresh(display.secondary_window);
 }

 void printMessage(Display display, char *text){
   wclear(display.secondary_window);
   box(display.secondary_window,0,0);
   mvwprintw(display.secondary_window, 1, 2, "%s", text);
   refreshDisplay(display);
 }

 void getIntInput(Display display, int *var){
   wscanw(display.secondary_window,"%d",var);
 }

 void finishDisplay(Display display){
   delwin(display.main_window); /* delete the window */
   delwin(display.secondary_window);
   endwin(); /* ending the display */
 }
