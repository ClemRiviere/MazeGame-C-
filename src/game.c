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
 * @version     1.0.0 - 18-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

/**
 * @file game.c
 *
 * @brief The mazeGame game functions.
 */

 #include "../include/game.h"

void initGame(Interface interface,Player *player){
  char name[25];
  char message[50];
  clearInterface(interface);
  displayMaze(interface);
  initPlayer(player,interface.maze);
  printMessage(interface, "Entrez votre nom : ");
  echo();
  getStringInput(interface,"%s",name);
  noecho();
  player->name = (char *)malloc(sizeof(char)*strlen(name));
  strcpy(player->name, name);
  sprintf(message,"Vas-y, échappes-toi %s !!!",name);
  printMessage(interface,message);
  displayPlayer(interface,*player);
}

int checkDir(Interface interface,Player player,Directions dir){
  int x_check;
  int y_check;

  if(dir != INVALID){
    switch(dir){
      case RIGHT:
        x_check = player.pos.x;
        y_check = player.pos.y+1;
        break;
      case LEFT:
        x_check = player.pos.x;
        y_check = player.pos.y-1;
        break;
      case UP:
        x_check = player.pos.x-1;
        y_check = player.pos.y;
        break;
      case DOWN:
        x_check = player.pos.x+1;
        y_check = player.pos.y;
        break;
      default:
        return 0;
    }

    /* Check only Y because X cannot be < 0 or > rows */
    if(y_check < 0 || y_check > interface.maze.d.col){
        return 0;
    }

    if (interface.maze.grid[x_check][y_check]==WALL){
        return 0;
    }
    return 1;
  }
  return 0;
}

int gameFinish(Interface interface,Player player){
  if (player.pos.y == interface.maze.d.col-1){
    return 1;
  }
  return 0;
}

int gameProcess(Interface interface, Player *player){
  int ch_keyboard;
  Directions dir;
  int scorePosition;
  int finish = 0;

  while(finish==0 && (ch_keyboard=wgetch(interface.main_window))!='q'){
    dir = INVALID;
    switch(ch_keyboard){
      case KEY_RIGHT:
        if(checkDir(interface,*player,RIGHT)==1){
          dir =  RIGHT;
        }
        break;
      case KEY_LEFT:
        if(checkDir(interface,*player,LEFT)==1){
          dir =  LEFT;
        }
        break;
      case KEY_UP:
        if(checkDir(interface,*player,UP)==1){
          dir =  UP;
        }
        break;
      case KEY_DOWN:
        if(checkDir(interface,*player,DOWN)==1){
          dir =  DOWN;
        }
        break;
    }
    clearPlayer(interface,*player);
    moovePlayer(player, &interface.maze, dir);
    displayPlayer(interface,*player);
    if (gameFinish(interface,*player)==1){
      finish = 1;
    }
  }
  if(finish==1){
    scorePosition = fillScore(interface.maze, *player);
    return displayScoreboard(interface, *player, scorePosition);
  }
  return 0;
}

int fillScore(Maze maze, Player player){
  char path_name[40]; /* 25 + ./saves/ + .scores */
  int score[10] = {0};
  char name[10][25] = {0};
  int playerPos;
  int i,j,ok;
  sprintf(path_name,"./saves/%s.scores",maze.name);
  FILE *file = fopen(path_name,"r+");
  if (file==NULL){
    printf("Error opening file!\n");
  }
  fscanf(file,"%d %d %d %d %d %d %d %d %d %d",&score[0],&score[1],&score[2],&score[3],&score[4],&score[5],&score[6],&score[7],&score[8],&score[9]);
  fscanf(file,"%s %s %s %s %s %s %s %s %s %s",name[0],name[1],name[2],name[3],name[4],name[5],name[6],name[7],name[8],name[9]);
  fclose(file);

  i=0;
  ok=0;

  playerPos = -1;

  file = fopen(path_name,"w");
  while(i<10 && ok==0){
    if (player.score>score[i]){
      ok = 1;
      for (j=9;j>i;j--){
        strcpy(name[j],name[j-1]);
        score[j]=score[j-1];
      }
      score[i] = player.score;
      strcpy(name[i],player.name);
      playerPos = i;
    }
    i++;
  }

  fprintf(file,"%d %d %d %d %d %d %d %d %d %d\n",score[0],score[1],score[2],score[3],score[4],score[5],score[6],score[7],score[8],score[9]);
  fprintf(file,"%s %s %s %s %s %s %s %s %s %s",name[0],name[1],name[2],name[3],name[4],name[5],name[6],name[7],name[8],name[9]);
  fclose(file);

  return playerPos;
}

int launchGame(Interface interface){
  Player player;
  initGame(interface,&player);
  return gameProcess(interface,&player);
}
