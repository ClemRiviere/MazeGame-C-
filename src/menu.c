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
   /*int enter = 0;
   int ch_keyboard;*/
   char nom[25];
   Dimensions dim;
   getDimensions(display,&dim);
   display.maze = createMaze(dim);
   initMaze(&display.maze);
   generateMaze(&display.maze);
   clearDisplay(display);
   displayMaze(display);
   printMessage(display,"Entrez un nom pour votre labyrinthe (/24): ");
   getStringInput(display,"%24[^\n]",nom);
   /*while(enter == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
     switch(ch_keyboard){
       case 10:
          enter = 1;
          break;
     }
   }*/
   finishDisplay(display);
   printf("%s",nom);
 }


 int getPosX(int row,int i){
   int res;
   res = ((i*2)+6+6+10);
   if (row < 40){
     res = ((i*2)+5);
   }
   return res;
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

   i = 0;
   enter = 0;

   while(enter == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
     /* When a key is pushed, we delete the highlight */
     printMain(display,getPosX(display.terminal_size.ws_row,i),(display.terminal_size.ws_col-17)/2,list[i][0]);
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
     activateHighlight(display);
     printMain(display,getPosX(display.terminal_size.ws_row,i),(display.terminal_size.ws_col-17)/2,list[i][0]);
     stopHighlight(display);

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
