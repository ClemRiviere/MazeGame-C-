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
 * @version     1.0.0 - 12-10-2017
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

 void launchMenu(){
   int ch_keyboard;
   int i;
   char str_desc[50];

   /* Get the terminal dimensions */
   struct winsize terminal_size;
   ioctl(0, TIOCGWINSZ, &terminal_size);

   WINDOW *main_window;
   WINDOW *secondary_window;

   /* Necessary to print utf-8 chars */
   setlocale(LC_ALL, "");
   /* Initialize ncurses */
   initscr();

   /* Create windows from terminal size */
   main_window = newwin(terminal_size.ws_row-5,terminal_size.ws_col-2,1,1);
   box(main_window,0,0);
   secondary_window = newwin(3,terminal_size.ws_col-2,terminal_size.ws_row-4,1);
   box(secondary_window,0,0);

   char * ascii_title[6] = {"███╗   ███╗ █████╗ ███████╗███████╗ ██████╗  █████╗ ███╗   ███╗███████╗",
                            "████╗ ████║██╔══██╗╚══███╔╝██╔════╝██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
                            "██╔████╔██║███████║  ███╔╝ █████╗  ██║  ███╗███████║██╔████╔██║█████╗  ",
                            "██║╚██╔╝██║██╔══██║ ███╔╝  ██╔══╝  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
                            "██║ ╚═╝ ██║██║  ██║███████╗███████╗╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
                            "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"};

   char * list[4][2] = {
                        {"--   Charger   --","Charger un labyrinthe à partir d'un fichier."},
                        {"--    Créer    --","Créer un labyrinthe avec vos propres dimensions."},
                        {"--    Jouer    --","Jouer sur le labyrinthe chargé."},
                        {"--   Quitter   --","Quitter l'application."}
                      };

   for (i=0;i<6;i++){
     /* Displays the ascii_art */
     mvwprintw(main_window, i+6, (terminal_size.ws_col-71)/2, "%s", ascii_title[i]);
     /* Displays the options */
     if (i<4){
       /* highlights the first item */
       if (i==0){
         wattron(main_window,A_STANDOUT);
         mvwprintw(secondary_window, 1, 2, "%s", list[i][1]);
       }
       /* i * 2 (blank between two rows) + 6 (top margin) + 6 (size of the ascii art) + 10 (blank between ascii and menu)*/
       mvwprintw(main_window, ((i*2)+6+6+10), (terminal_size.ws_col-17)/2, "%s", list[i][0]);
       wattroff(main_window,A_STANDOUT);
     }
   }

   wrefresh(main_window); /* update the terminal screen */
   wrefresh(secondary_window);

   noecho(); /* disable echoing of characters on the screen (user entry)*/
   keypad(main_window, TRUE ); /* enable keyboard input for the window. */
   curs_set(0); /* hide the default screen cursor. */

   i = 0;

   while((ch_keyboard=wgetch(main_window))!='q'){
     /* When a key is pushed, we delete the highlight */
     mvwprintw(main_window,((i*2)+6+6+10), (terminal_size.ws_col-17)/2, "%s", list[i][0]);
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
     }
     /* We highlights the selected menu (same then before if it was another key than up or down) */
     wattron(main_window, A_STANDOUT);
     mvwprintw(main_window, ((i*2)+6+6+10), (terminal_size.ws_col-17)/2, "%s", list[i][0]);
     wattroff(main_window, A_STANDOUT);

     /* Displays the description in the little window */
     sprintf(str_desc, "%-50s",  list[i][1]);
     mvwprintw(secondary_window, 1, 2, "%s", str_desc);
     wrefresh(secondary_window);
   }

   delwin(main_window); /* delete the window */
   delwin(secondary_window);
   endwin(); /* ending the display */

 }
