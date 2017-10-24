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
 * @file interface.c
 *
 * @brief The mazeGame interface functions.
 */

 #include "../include/interface.h"

 void initInterface(Interface *interface){
   ioctl(0, TIOCGWINSZ, &interface->terminal_size);
   /* Necessary to print utf-8 chars */
   setlocale(LC_ALL, "");
   /* Initialize ncurses */
   initscr();

   /* Create windows and boxes around */
   interface->main_window = newwin(interface->terminal_size.ws_row-5,interface->terminal_size.ws_col-2,1,1);
   box(interface->main_window,0,0);
   interface->secondary_window = newwin(3,interface->terminal_size.ws_col-2,interface->terminal_size.ws_row-4,1);
   box(interface->secondary_window,0,0);

   /* Set the interface to not initialized (there is no maze loaded) */
   interface->init = 0;
 }

 void clearInterface(Interface interface){
   /* Complete clear of windows */
   wclear(interface.main_window);
   wclear(interface.secondary_window);

   /* Redraw boxes and refresh */
   box(interface.main_window,0,0);
   box(interface.secondary_window,0,0);
   refreshInterface(interface);
 }

 void printTitle(Interface interface){
   /* We need a minimum terminal size to print the title. */
   if (interface.terminal_size.ws_row >= MIN_SIZE_TITLE){
     int i;
     char * ascii_title[TITLE_HEIGHT] = {"███╗   ███╗ █████╗ ███████╗███████╗ ██████╗  █████╗ ███╗   ███╗███████╗",
                                         "████╗ ████║██╔══██╗╚══███╔╝██╔════╝██╔════╝ ██╔══██╗████╗ ████║██╔════╝",
                                         "██╔████╔██║███████║  ███╔╝ █████╗  ██║  ███╗███████║██╔████╔██║█████╗  ",
                                         "██║╚██╔╝██║██╔══██║ ███╔╝  ██╔══╝  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ",
                                         "██║ ╚═╝ ██║██║  ██║███████╗███████╗╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗",
                                         "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝"};
     for (i=0;i<TITLE_HEIGHT;i++){
       /* Interfaces the ascii_art */
       printMain(interface,i+TITLE_MARGIN_TOP,(interface.terminal_size.ws_col-TITLE_WIDTH)/2,ascii_title[i]);
     }
     refreshInterface(interface);
   }
 }

 void printLoadedMaze(Interface interface){
   char *message;

   if (interface.init == 1){
     message = (char *)malloc(sizeof(char)*(strlen(interface.maze.name)+7));
     sprintf(message,"%s CHARGÉ",interface.maze.name);
   }
   else {
     message = (char *)malloc(sizeof(char)*23);
     sprintf(message,"AUCUN LABYRINTHE CHARGÉ");
   }

   /* If there are enough rows, we print the text under the title */
   if (interface.terminal_size.ws_row >= MIN_SIZE_TITLE){
     printMain(interface,TITLE_HEIGHT+9,(interface.terminal_size.ws_col-strlen(message))/2,message);
   }
   /* Else at the top of the window */
   else {
     printMain(interface,4,(interface.terminal_size.ws_col-strlen(message))/2,message);
   }
   refreshInterface(interface);
 }

 void getDimensions(Interface interface, Dimensions *d){
     int ch_keyboard;
     int error = 0;
     int enter = 0;
     clearInterface(interface);
     printTitle(interface);
     echo();
     /* ROW */
     do{
       if (error == 1){
         enter = 0;
         printMessage(interface,"Incorrect ! (Entrée pour recommencer)");
         while(enter == 0 && (ch_keyboard=wgetch(interface.secondary_window))!='q'){
           switch(ch_keyboard){
             case 10:
                enter = 1;
                break;
           }
         }
       }
       printMessage(interface,"Entrez le nombre de lignes de votre labyrinthe : ");
       getIntInput(interface,&d->row);
       error = 1;
     }while(d->row%2 != 1 || d->row < 0 || d->row > interface.terminal_size.ws_row - 7);

     /* COL */
     error = 0;
     do{
       if (error == 1){
         enter = 0;
         printMessage(interface,"Incorrect ! (Entrée pour recommencer)");
         while(enter == 0 && (ch_keyboard=wgetch(interface.secondary_window))!='q'){
           switch(ch_keyboard){
             case 10:
                enter = 1;
                break;
           }
         }
       }
       printMessage(interface,"Entrez le nombre de colonnes de votre labyrinthe : ");
       getIntInput(interface,&d->col);
       error = 1;
     }while(d->col%2 != 1 || d->col < 0 || d->col > (interface.terminal_size.ws_col - 4)/2);
 }

 void displayMaze(Interface interface){
     int i,j;
     int cpt = 0;
     char symbol[2];
     for (i=0;i<interface.maze.d.row;i++){
         for (j=0;j<interface.maze.d.col;j++){
             if (interface.maze.grid[i][j]==WALL){
                 strcpy(symbol, "██");
             }
             else {
                 cpt += 1;
                 /* EMPTY CELL */
                 if (interface.maze.grid[i][j]==-1){
                   strcpy(symbol, "  ");
                 }
                 /* CHEST */
                 else if (interface.maze.grid[i][j]>1){
                   strcpy(symbol, "💰 ");
                 }
                 /* TRAP */
                 else {
                   strcpy(symbol, "☠ ");
                 }
            }
            printMain(interface,
                     ((interface.terminal_size.ws_row-7)/2)-(interface.maze.d.row/2)+i+1,
                     ((interface.terminal_size.ws_col-4)/2)-(interface.maze.d.col)+(((j+1)*2)-1),
                     symbol);
         }
     }
 }

 void clearPlayer(Interface interface, Player player){
   printMain(interface,
            ((interface.terminal_size.ws_row-7)/2)-(interface.maze.d.row/2)+player.pos.x+1,
            ((interface.terminal_size.ws_col-4)/2)-(interface.maze.d.col)+(((player.pos.y+1)*2)-1),
            "  ");
 }

 void displayPlayer(Interface interface, Player player){
   printMain(interface,
            ((interface.terminal_size.ws_row-7)/2)-(interface.maze.d.row/2)+player.pos.x+1,
            ((interface.terminal_size.ws_col-4)/2)-(interface.maze.d.col)+(((player.pos.y+1)*2)-1),
            "😚 ");
   printScore(interface, player);
 }

 void printScore(Interface interface, Player player){
   int nDigits = (player.score == 0 ? 1 : ((int)(log10(fabs(player.score))+1) + (player.score < 0 ? 1 : 0)));
   int textLength = strlen("SCORE : ")+nDigits+3;
   char *text = (char *)malloc(sizeof(char)*textLength);
   sprintf(text,"SCORE : %d",player.score);
   mvwprintw(interface.secondary_window, 1, interface.terminal_size.ws_col-textLength, "%s", text);
   refreshInterface(interface);
 }

 void activateHighlight(Interface interface){
   wattron(interface.main_window,A_STANDOUT);
 }

 void stopHighlight(Interface interface){
   wattroff(interface.main_window,A_STANDOUT);
 }

 void refreshInterface(Interface interface){
   wrefresh(interface.main_window); /* update the terminal screen */
   wrefresh(interface.secondary_window);
 }

 void printMain(Interface interface, int x, int y, char *text){
   mvwprintw(interface.main_window, x, y, "%s", text);
   refreshInterface(interface);
 }

 void printMessage(Interface interface, char *text){
   wclear(interface.secondary_window);
   box(interface.secondary_window,0,0);
   mvwprintw(interface.secondary_window, 1, 2, "%s", text);
   refreshInterface(interface);
 }

 void getIntInput(Interface interface, int *var){
   wscanw(interface.secondary_window,"%d",var);
 }

 void getStringInput(Interface interface, char *pattern,char *var){
   wscanw(interface.secondary_window,pattern,var);
 }

 int waiterInterface(Interface interface, char *mainText, char *secondaryText){
   int ch_keyboard;
   int enter = 0;

   clearInterface(interface);
   printMain(interface,
            (interface.terminal_size.ws_row-7)/2,
            (interface.terminal_size.ws_col-4)/2 - strlen(mainText)/2,
            mainText);
   printMessage(interface,secondaryText);

   while(enter==0 && (ch_keyboard=wgetch(interface.main_window))!='q'){
     switch(ch_keyboard){
       case 10:
          enter = 1;
          break;
     }
   }

   return enter;
 }

 int displayScoreboard(Interface interface, Player player, int pos){
   int ch_keyboard,i,cpt,margin;
   int enter = 0;
   char path_name[40];
   int score[10] = {0};
   char name[10][25] = {0};
   char *message = (char *)malloc(sizeof(char)*1);

   clearInterface(interface);
   sprintf(path_name,"./saves/%s.scores",interface.maze.name);
   FILE *file = fopen(path_name,"r");
   if (file==NULL){
     printf("Error opening file!\n");
   }
   fscanf(file,"%d %d %d %d %d %d %d %d %d %d",&score[0],&score[1],&score[2],&score[3],&score[4],&score[5],&score[6],&score[7],&score[8],&score[9]);
   fscanf(file,"%s %s %s %s %s %s %s %s %s %s",name[0],name[1],name[2],name[3],name[4],name[5],name[6],name[7],name[8],name[9]);
   fclose(file);
   cpt = 0;
   for (i=0;i<10;i++){
     if (score[i]!=0){
       message = realloc(message,sizeof(char)*(strlen(name[i])+floor(log10(abs(score[i])))+14));
       sprintf(message,"-- %s : %d --",name[i],score[i]);
       if (i==pos){
         activateHighlight(interface);
       }
       if (interface.terminal_size.ws_row<MIN_SIZE_TITLE){
         margin = 2;
       }
       else {
         margin = 10;
       }
       printMain(interface,(cpt*2)+margin,(interface.terminal_size.ws_col/2)-(strlen(message)/2),message);
       cpt ++;
       stopHighlight(interface);
     }
   }
   message = (char *)realloc(message,sizeof(char)*50);
   sprintf(message,"Votre score : %d | ENTREE pour revenir au menu",player.score);
   printMessage(interface,message);

   while(enter==0 && (ch_keyboard=wgetch(interface.main_window))!='q'){
     switch(ch_keyboard){
       case 10:
          enter = 1;
          break;
     }
   }

   return enter;
 }

 void finishInterface(Interface interface){
   if (interface.init == 1){
     destroyMaze(&interface.maze);
   }
   delwin(interface.main_window); /* delete the window */
   delwin(interface.secondary_window);
   endwin(); /* ending the interface */
 }
