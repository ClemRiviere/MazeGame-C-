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
  clearInterface(interface);
  displayMaze(interface);
  initPlayer(player);
  displayPlayer(interface,*player);
  printMessage(interface,"EHEH, TRY TO ESCAPE !!!");
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
    moovePlayer(player, dir);
    displayPlayer(interface,*player);
    if (gameFinish(interface,*player)==1){
      finish = 1;
    }
  }
  if(finish==1){
    return waiterInterface(interface,"Appuez sur ENTREE pour revenir au menu.","BRAVO, c'est gagné !");
  }
  return 0;
}

int launchGame(Interface interface){
  Player player;
  initGame(interface,&player);
  return gameProcess(interface,&player);
}
