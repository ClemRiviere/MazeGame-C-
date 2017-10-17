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
   int enter;
   int escape;
   int ch_keyboard;
   char name[25];
   Dimensions dim;
   getDimensions(display,&dim);
   display.maze = createMaze(dim);
   initMaze(&display.maze);
   generateMaze(&display.maze);
   clearDisplay(display);
   displayMaze(display);

   do{
     enter = 1;
     printMessage(display,"Entrez un nom pour votre labyrinthe (/24): ");
     echo();
     getStringInput(display,"%24[^\n]",name);
     noecho();
     display.maze.name = name;

     /* Checking if the maze already exists */
     if (exist(display.maze)==1){
       enter = 0;
       escape = 0;
       printMessage(display,"Ce labyrinthe existe déjà, ENTREE pour écraser / ECHAP pour annuler");
       /* Waiting for the key */
       while(enter == 0 && escape == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
         switch(ch_keyboard){
           case 10:
              enter = 1;
              break;
           case 27:
              escape = 1;
              break;
         }
       }
     }

     if (enter == 1){
       /* Checking for save issues */
       if (saveMaze(display.maze)!=0){
         enter = 0;
       }
     }
   }while(enter == 0);
   display.init = 1;
   launchMenu(display);
 }

 void load(Display display){
   int i,enter,ch_keyboard;
   int cpt = 0;
   char message[100];
   char path[32]; /* 25 + 8 (./saves/) */
   char **list;

   DIR * rep = opendir("./saves");
   if (rep != NULL){
      struct dirent *ent;
      while ((ent = readdir(rep)) != NULL){
          cpt += 1;
      }
      closedir(rep);
   }
   list = (char **)malloc(sizeof(char*)*cpt);

   cpt = 0;
   rep = opendir("./saves");
   if (rep != NULL){
      struct dirent *ent;
      while ((ent = readdir(rep)) != NULL){
          /*list[cpt] = (char *)malloc(sizeof(char)*strlen(ent->d_name));*/
          if (strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
            list[cpt] = (char*)malloc(sizeof(char)*strlen(ent->d_name));
            strcpy(list[cpt],ent->d_name);
            cpt += 1;
          }
      }
      closedir(rep);
   }

   i = 0;
   enter = 0;

   clearDisplay(display);
   sprintf(message,"ENTREE pour charger %s | LEFT / RIGHT pour sélectionner.",list[i]);
   printMessage(display,message);
   sprintf(path,"./saves/%s",list[i]);
   display.maze = readMaze(path);
   displayMaze(display);

   while(enter == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
     switch(ch_keyboard){
       case KEY_LEFT:
          i--;
          i = ( i<0 ) ? cpt-1 : i;
          break;
       case KEY_RIGHT:
          i++;
          i = ( i>(cpt-1)) ? 0 : i;
          break;
       case 10:
          enter = 1;
          break;
     }
     clearDisplay(display);
     sprintf(message,"ENTREE pour charger %s | LEFT / RIGHT pour sélectionner.",list[i]);
     printMessage(display,message);
     sprintf(path,"./saves/%s",list[i]);
     display.maze = readMaze(path);
     displayMaze(display);
   }
   if (enter == 1){
     display.init = 1;
   }

   launchMenu(display);
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

   clearDisplay(display);
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

   switch (i){
     case 0:
        load(display);
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
