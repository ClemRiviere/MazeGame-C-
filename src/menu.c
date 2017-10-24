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

 void initMenu(Interface *interface, char * list[4][2]){
   int i;
   char path[32];
   /* Print the title and the message of the current loaded maze */
   clearInterface(*interface);
   printTitle(*interface);
   printLoadedMaze(*interface);
   if (interface->init == 1){
     sprintf(path,"./saves/%s.cfg",interface->maze.name);
     destroyMaze(&interface->maze);
     interface->maze = readMaze(path);
   }
   for (i=0;i<4;i++){
     if (i==0){
       activateHighlight(*interface);
       printMessage(*interface,list[i][1]);
     }
     printMain(*interface,getPosX(interface->terminal_size.ws_row,i),(interface->terminal_size.ws_col-17)/2,list[i][0]);
     stopHighlight(*interface);
   }

   refreshInterface(*interface);

   noecho(); /* disable echoing of characters on the screen (user entry)*/
   keypad(interface->main_window, TRUE ); /* enable keyboard input for the window. */
   curs_set(0); /* hide the default screen cursor. */
 }

 int selectMenu(Interface interface,char * list[4][2]){
   int ch_keyboard;
   int i = 0;
   int enter = 0;
   char str_desc[50];

   while(enter == 0 && (ch_keyboard=wgetch(interface.main_window))!='q'){
     /* When a key is pushed, we delete the highlight */
     printMain(interface,getPosX(interface.terminal_size.ws_row,i),(interface.terminal_size.ws_col-17)/2,list[i][0]);
     /* If it's key_up or key_down, we are changing the value of selected menus */
     switch(ch_keyboard){
       case KEY_UP:
          i--;
          i = ( i<0 ) ? 3 : i;
          i = (i==2 && interface.init==0) ? 1 : i;
          break;
       case KEY_DOWN:
          i++;
          i = ( i>3 ) ? 0 : i;
          i = (i==2 && interface.init==0) ? 3 : i;
          break;
       case 10:
          enter = 1;
          break;
     }
     /* We highlights the selected menu (same then before if it was another key than up or down) */
     activateHighlight(interface);
     printMain(interface,getPosX(interface.terminal_size.ws_row,i),(interface.terminal_size.ws_col-17)/2,list[i][0]);
     stopHighlight(interface);

     /* Interfaces the description in the little window */
     sprintf(str_desc, "%-50s",  list[i][1]);
     printMessage(interface,str_desc);
   }
   if (enter==1){
     return i;
   }
   return -1;
 }

void interactMenu(Interface interface,int select){
  int relaunchMenu = 0;

  switch (select){
    case 0:
       relaunchMenu = loadProcess(&interface);
       break;
    case 1:
       createProcess(&interface);
       relaunchMenu = 1;
       break;
    case 2:
       relaunchMenu = launchGame(interface);
       break;
    case 3:
       relaunchMenu = 0;
       break;
  }
  if (relaunchMenu==1)
    launchMenu(interface);
  else
    finishInterface(interface);
}

void launchMenu(Interface interface){
   int selected;

   /* The options with their descriptions */
   char * list[4][2] = {
                        {"--   Charger   --","Charger un labyrinthe à partir d'un fichier."},
                        {"--    Créer    --","Créer un labyrinthe avec vos propres dimensions."},
                        {"--    Jouer    --","Jouer sur le labyrinthe chargé."},
                        {"--   Quitter   --","Quitter l'application."}
                      };

   initMenu(&interface,list);

   selected = selectMenu(interface,list);

   /* The exit key have been pressed */
   if (selected == -1){
     finishInterface(interface);
   }
   else {
     interactMenu(interface, selected);
   }
 }
