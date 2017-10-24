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

void initPlayer(Player *player, Maze maze){
  int i,j;
  player->pos.x = 1;
  player->pos.y = 0;
  for (i=0;i<maze.d.row;i++){
    for (j=0;j<maze.d.col;j++){
      if (maze.grid[i][j]<0)
        player->score -= maze.grid[i][j];
    }
  }
}

void moovePlayer(Player *player, Maze *maze, Directions dir){
  int new_x = player->pos.x;
  int new_y = player->pos.y;
  int changeScore = 0;

  if(dir != INVALID){
    changeScore = 1;
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
        changeScore = 0;
    }
  }
  player->pos.x = new_x;
  player->pos.y = new_y;
  if (changeScore == 1)
    player->score += maze->grid[new_x][new_y];
    maze->grid[new_x][new_y] = -1;
}
