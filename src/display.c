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
   if (display.terminal_size.ws_row >= 40){
     int i;
     char * ascii_title[6] = {"███╗   ███╗ █████╗ ███████╗███████╗ ██████╗  █████╗ ███╗   ███╗███████╗",
                              "████╗ ████║██╔══██╗╚══███╔╝██╔════╝██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
                              "██╔████╔██║███████║  ███╔╝ █████╗  ██║  ███╗███████║██╔████╔██║█████╗  ",
                              "██║╚██╔╝██║██╔══██║ ███╔╝  ██╔══╝  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
                              "██║ ╚═╝ ██║██║  ██║███████╗███████╗╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
                              "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"};
     for (i=0;i<6;i++){
       /* Displays the ascii_art */
       printMain(display,i+6,(display.terminal_size.ws_col-71)/2,ascii_title[i]);
     }
     refreshDisplay(display);
   }
 }

 void getDimensions(Display display, Dimensions *d){
     int ch_keyboard;
     int error = 0;
     int enter = 0;
     clearDisplay(display);
     printTitle(display);
     echo();
     /* ROW */
     do{
       if (error == 1){
         enter = 0;
         printMessage(display,"Incorrect ! (Entrée pour recommencer)");
         while(enter == 0 && (ch_keyboard=wgetch(display.secondary_window))!='q'){
           switch(ch_keyboard){
             case 10:
                enter = 1;
                break;
           }
         }
       }
       printMessage(display,"Entrez le nombre de lignes de votre labyrinthe : ");
       getIntInput(display,&d->row);
       error = 1;
     }while(d->row%2 != 1 || d->row < 0 || d->row > display.terminal_size.ws_row - 7);

     /* COL */
     error = 0;
     do{
       if (error == 1){
         enter = 0;
         printMessage(display,"Incorrect ! (Entrée pour recommencer)");
         while(enter == 0 && (ch_keyboard=wgetch(display.secondary_window))!='q'){
           switch(ch_keyboard){
             case 10:
                enter = 1;
                break;
           }
         }
       }
       printMessage(display,"Entrez le nombre de colonnes de votre labyrinthe : ");
       getIntInput(display,&d->col);
       error = 1;
     }while(d->col%2 != 1 || d->col < 0 || d->col > (display.terminal_size.ws_col - 4)/2);
 }

 void displayMaze(Display display){
     int i,j;
     int cpt = 0;
     for (i=0;i<display.maze.d.row;i++){
         for (j=0;j<display.maze.d.col;j++){
             if (display.maze.grid[i][j]==WALL){
                 printMain(display,i+1,(j+1)*2,"██");
                 /*printf("#");*/
             }
             else {
                 cpt += 1;
                 printMain(display,i+1,(j+1)*2,"  ");
                 /*printf(" ");*/
             }
         }
         /*printf("\n");*/
     }
     /* VERIF PRINTS
     for (i=0;i<maze.n_walls;i++){
       printf("[X : %d | Y : %d]\n",maze.walls[i].x,maze.walls[i].y);
     }
     printf("N_WALLS : %d\n",maze.n_walls);
     printf("%d\n",cpt);
     printf("%d\n",(maze.d.row/2)*(maze.d.col/2));*/
 }

 void activateHighlight(Display display){
   wattron(display.main_window,A_STANDOUT);
 }

 void stopHighlight(Display display){
   wattroff(display.main_window,A_STANDOUT);
 }

 void refreshDisplay(Display display){
   wrefresh(display.main_window); /* update the terminal screen */
   wrefresh(display.secondary_window);
 }

 void printMain(Display display, int x, int y, char *text){
   mvwprintw(display.main_window, x, y, "%s", text);
   refreshDisplay(display);
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

 void getStringInput(Display display, char *pattern,char *var){
   wscanw(display.secondary_window,pattern,var);
 }

 void finishDisplay(Display display){
   delwin(display.main_window); /* delete the window */
   delwin(display.secondary_window);
   endwin(); /* ending the display */
 }
