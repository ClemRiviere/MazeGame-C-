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
 * @version     1.0.0 - 19-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

/**
 * @file player.c
 *
 * @brief The mazeGame player functions.
 */

 #include "../include/player.h"

void initPlayer(Player *player){
  player->pos.x = 1;
  player->pos.y = 0;
  /* FOR THE MOMENT */
  player->name = (char *)malloc(sizeof(char)*strlen("clem"));
  player->name = "clem";
}

void moovePlayer(Player *player, Directions dir){
  int new_x = player->pos.x;
  int new_y = player->pos.y;

  if(dir != INVALID){
    switch(dir){
      case RIGHT:
        new_x = player->pos.x;
        new_y = player->pos.y+1;
        break;
      case LEFT:
        new_x = player->pos.x;
        new_y = player->pos.y-1;
        break;
      case UP:
        new_x = player->pos.x-1;
        new_y = player->pos.y;
        break;
      case DOWN:
        new_x = player->pos.x+1;
        new_y = player->pos.y;
        break;
      default:
        new_x = player->pos.x;
        new_y = player->pos.y;
    }
  }
  player->pos.x = new_x;
  player->pos.y = new_y;
}
