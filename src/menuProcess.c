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
 * @file menuProcess.c
 *
 * @brief The mazeGame menu functions processes.
 */

#include "../include/menuProcess.h"

int createProcess(Interface *interface){
  Dimensions dim;

  getDimensions(*interface,&dim);
  interface->maze = createMaze(dim);
  initMaze(&interface->maze);
  generateMaze(&interface->maze);
  clearInterface(*interface);
  displayMaze(*interface);
  getMazeName(interface);
  interface->init = 1;
  return 0;
}

int getOverwrite(Interface *interface){
  int enter = 0;
  int escape = 0;
  int ch_keyboard;

  printMessage(*interface,"Ce labyrinthe existe déjà, ENTREE pour écraser / ECHAP pour annuler");
  /* Waiting for the key */
  while(enter == 0 && escape == 0 && (ch_keyboard=wgetch(interface->main_window))!='q'){
    switch(ch_keyboard){
      case 10:
         enter = 1;
         break;
      case 27:
         escape = 1;
         break;
    }
  }
  return enter;
}

void getMazeName(Interface *interface){
  char name[30];
  int enter = 0;

  do{
    enter = 1;
    printMessage(*interface,"Entrez un nom pour votre labyrinthe (/24): ");
    echo();
    getStringInput(*interface,"%24[^\n]",name);
    noecho();
    strcat(name,".cfg");
    interface->maze.name = (char *)malloc(sizeof(char)*strlen(name));
    strcpy(interface->maze.name,name);

    /* Checking if the maze already exists */
    if (exist(interface->maze)==1){
      enter = getOverwrite(interface);
    }

    if (enter == 1){
      /* Checking for save issues */
      if (saveMaze(interface->maze)!=0){
        enter = 0;
      }
    }
  }while(enter == 0);
}

int loadProcess(Interface *interface){
  char **list;

  int nSaves = getSavesNumber();
  list = (char **)malloc(sizeof(char*)*nSaves);
  fillSaveList(list);
  int enter = selectMaze(interface,list,nSaves);

  if (enter == 1){
    interface->init = 1;
    return 1;
  }
  interface->init = 0;
  return 0;
}

int getSavesNumber(){
  int cpt = 0;
  DIR * rep = opendir("./saves");
  if (rep != NULL){
     struct dirent *ent;
     while ((ent = readdir(rep)) != NULL){
         cpt += 1;
     }
     closedir(rep);
  }
  return cpt-2;
}

void fillSaveList(char **list){
  int cpt = 0;

  DIR * rep = opendir("./saves");
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
}

int selectMaze(Interface *interface, char **list, int nSaves){
  char path[32]; /* 25 + 8 (./saves/) */
  char message[100];
  int ch_keyboard;
  int i = 0;
  int enter = 0;

  /* Initialize with the first maze */
  clearInterface(*interface);
  sprintf(message,"ENTREE pour charger %s | LEFT / RIGHT pour sélectionner.",list[i]);
  printMessage(*interface,message);
  sprintf(path,"./saves/%s",list[i]);
  if (interface->init == 1){
    destroyMaze(&interface->maze);
  }
  interface->maze = readMaze(path);
  displayMaze(*interface);

  /* Get the keyboard entries while it's not the exit key or enter */
  while(enter == 0 && (ch_keyboard=wgetch(interface->main_window))!='q'){
    switch(ch_keyboard){
      case KEY_LEFT:
         i--;
         i = ( i<0 ) ? nSaves-1 : i;
         break;
      case KEY_RIGHT:
         i++;
         i = ( i>(nSaves-1)) ? 0 : i;
         break;
      case 10:
         enter = 1;
         break;
    }
    clearInterface(*interface);
    sprintf(message,"ENTREE pour charger %s | LEFT / RIGHT pour sélectionner.",list[i]);
    printMessage(*interface,message);
    sprintf(path,"./saves/%s",list[i]);
    destroyMaze(&interface->maze);
    interface->maze = readMaze(path);
    displayMaze(*interface);
  }
  return enter;
}
