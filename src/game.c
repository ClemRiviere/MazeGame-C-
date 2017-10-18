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

void initGame(Display display){
  clearDisplay(display);
  displayMaze(display);
}

void waiter(Display display){
  int ch_keyboard;
  int enter = 0;
  while(enter == 0 && (ch_keyboard=wgetch(display.main_window))!='q'){
    switch(ch_keyboard){
      case 10:
         enter = 1;
         break;
    }
  }
}

void launchGame(Display display){
  initGame(display);
  waiter(display);
}
