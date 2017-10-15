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
 * @version     1.0.1 - 16-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

/**
 * @file menu.c
 *
 * @brief The mazeGame menu fonctions.
 */

#include "../include/menu.h"

 void create(Display display){
   Dimensions dim;
   Maze maze;
   getDimensions(display,&dim);
   finishDisplay(display);
   printf("ROW : %d | COL : %d\n",dim.row,dim.col);
   /*maze = createMaze(dim);
   initMaze(&maze);
   generateMaze(&maze);
   displayMaze(display,maze);*/
 }

 void launchMenu(Display display){
   int ch_keyboard;
   int i;
   int enter;
   char str_desc[50];

   char * list[4][2] = {
                        {"--   Charger   --","Charger un labyrinthe à partir d'un fichier."},
                        {"--    Créer    --","Créer un labyrinthe avec vos propres dimensions."},
                        {"--    Jouer    --","Jouer sur le labyrinthe chargé."},
                        {"--   Quitter   --","Quitter l'application."}
                      };

   printTitle(display);
   for (i=0;i<4;i++){
     if (i==0){
       wattron(display.main_window,A_STANDOUT);
       mvwprintw(display.secondary_window, 1, 2, "%s", list[i][1]);
     }
     mvwprintw(display.main_window, ((i*2)+6+6+10), (display.terminal_size.ws_col-17)/2, "%s", list[i][0]);
     wattroff(display.main_window,A_STANDOUT);
   }

   refreshDisplay(display);

   noecho(); /* disable echoing of characters on the screen (user entry)*/
   keypad(display.main_window, TRUE ); /* enable keyboard input for the window. */
   curs_set(0); /* hide the default screen cursor. */

   i = 0;
   enter = 0;

   while(enter == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
     /* When a key is pushed, we delete the highlight */
     mvwprintw(display.main_window,((i*2)+6+6+10), (display.terminal_size.ws_col-17)/2, "%s", list[i][0]);
     /* If it's key_up or key_down, we are changing the value of selected menus */
     switch(ch_keyboard){
       case KEY_UP:
          i--;
          i = ( i<0 ) ? 3 : i;
          break;
       case KEY_DOWN:
          i++;
          i = ( i>3 ) ? 0 : i;
          break;
       case 10:
          enter = 1;
          break;
     }
     /* We highlights the selected menu (same then before if it was another key than up or down) */
     wattron(display.main_window, A_STANDOUT);
     mvwprintw(display.main_window, ((i*2)+6+6+10), (display.terminal_size.ws_col-17)/2, "%s", list[i][0]);
     wattroff(display.main_window, A_STANDOUT);

     /* Displays the description in the little window */
     sprintf(str_desc, "%-50s",  list[i][1]);
     printMessage(display,str_desc);
   }

   switch (i){
     case 0:
        printf("Charger");
        finishDisplay(display);
        break;
     case 1:
        create(display);
        break;
     case 2:
        printf("Jouer");
        finishDisplay(display);
        break;
     case 3:
        printf("Quitter");
        finishDisplay(display);
        break;
   }
 }
