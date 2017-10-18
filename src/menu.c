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

 int getPosX(int row,int i){
   int res;
   res = ((i*MENU_OPTIONS_MARGIN)+TITLE_HEIGHT+TITLE_MARGIN_TOP+TITLE_MARGIN_BOT);
   /* If there is no title, we push the text up */
   if (row < MIN_SIZE_TITLE){
     res = ((i*MENU_OPTIONS_MARGIN)+TITLE_MARGIN_TOP);
   }
   return res;
 }

 void initMenu(Display display, char * list[4][2]){
   int i;
   /* Print the title and the message of the current loaded maze */
   clearDisplay(display);
   printTitle(display);
   printLoadedMaze(display);
   for (i=0;i<4;i++){
     if (i==0){
       activateHighlight(display);
       printMessage(display,list[i][1]);
     }
     printMain(display,getPosX(display.terminal_size.ws_row,i),(display.terminal_size.ws_col-17)/2,list[i][0]);
     stopHighlight(display);
   }

   refreshDisplay(display);

   noecho(); /* disable echoing of characters on the screen (user entry)*/
   keypad(display.main_window, TRUE ); /* enable keyboard input for the window. */
   curs_set(0); /* hide the default screen cursor. */
 }

 int selectMenu(Display display,char * list[4][2]){
   int ch_keyboard;
   int i = 0;
   int enter = 0;
   char str_desc[50];

   while(enter == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
     /* When a key is pushed, we delete the highlight */
     printMain(display,getPosX(display.terminal_size.ws_row,i),(display.terminal_size.ws_col-17)/2,list[i][0]);
     /* If it's key_up or key_down, we are changing the value of selected menus */
     switch(ch_keyboard){
       case KEY_UP:
          i--;
          i = ( i<0 ) ? 3 : i;
          i = (i==2 && display.init==0) ? 1 : i;
          break;
       case KEY_DOWN:
          i++;
          i = ( i>3 ) ? 0 : i;
          i = (i==2 && display.init==0) ? 3 : i;
          break;
       case 10:
          enter = 1;
          break;
     }
     /* We highlights the selected menu (same then before if it was another key than up or down) */
     activateHighlight(display);
     printMain(display,getPosX(display.terminal_size.ws_row,i),(display.terminal_size.ws_col-17)/2,list[i][0]);
     stopHighlight(display);

     /* Displays the description in the little window */
     sprintf(str_desc, "%-50s",  list[i][1]);
     printMessage(display,str_desc);
   }
   if (enter==1){
     return i;
   }
   return -1;
 }

void interactMenu(Display display,int select){
  int relaunchMenu = 1;

  switch (select){
    case 0:
       if (loadProcess(&display)!=0)
          relaunchMenu = 0;
       break;
    case 1:
       if (createProcess(&display)!=0)
          relaunchMenu = 0;
       break;
    case 2:
       launchGame(display);
       relaunchMenu = 0;
       break;
    case 3:
       relaunchMenu = 0;
       break;
  }
  if (relaunchMenu==1)
    launchMenu(display);
  else
    finishDisplay(display);
}

void launchMenu(Display display){
   int selected;

   /* The options with their descriptions */
   char * list[4][2] = {
                        {"--   Charger   --","Charger un labyrinthe à partir d'un fichier."},
                        {"--    Créer    --","Créer un labyrinthe avec vos propres dimensions."},
                        {"--    Jouer    --","Jouer sur le labyrinthe chargé."},
                        {"--   Quitter   --","Quitter l'application."}
                      };

   initMenu(display,list);

   selected = selectMenu(display,list);

   /* The exit key have been pressed */
   if (selected == -1){
     finishDisplay(display);
   }
   else {
     interactMenu(display, selected);
   }
 }
