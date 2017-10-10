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
 * @version     0.0.1 - 10-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

/**
 * @file maze_function.c
 *
 * The maze functions for the maze generator program.
 */

 #include "../include/maze_function.h"

 void getDimensions(Dimensions *d){
     printf ("Entrez le nombre de lignes de votre labyrinthe : ");
     scanf("%d",&d->row);
     printf ("Entrez le nombre de colonnes de votre labyrinthe : ");
     scanf("%d",&d->col);
 }

 int ** createMaze(Dimensions d){
     int i;
     int ** maze = (int **)malloc(sizeof(int*)*d.row);
     for (i=0;i<d.row;i++){
         maze[i] = (int *)malloc(sizeof(int)*d.col);
     }
     if(maze==NULL)
     {
         fprintf(stderr,"Malloc problem (Maze allocation) !");
         exit(EXIT_FAILURE);
     }
     return maze;
 }

 void destroyMaze(int ** maze,Dimensions d){
     int i;
     for (i=0;i<d.row;i++){
         free(maze[i]);
     }
     free(maze);
 }

  void initMaze(int ** maze,Dimensions d){
     int i,j;
     int cpt = 1;
     for (i=0;i<d.row;i++){
         for (j=0;j<d.col;j++){
             if (j%2==0 || i%2==0){
                 maze[i][j]=WALL;
             }
             else {
                 maze[i][j]=cpt;
                 cpt += 1;
             }
         }
     }
 }

 void displayMaze(int ** maze,Dimensions d){
     int i,j;
     int cpt = 0;
     for (i=0;i<d.row;i++){
         for (j=0;j<d.col;j++){
             if (maze[i][j]==WALL){
                 printf("#");
             }
             else {
                 cpt += 1;
                 printf(" ");
             }
         }
         printf("\n");
     }
     printf("%d\n",cpt);
     printf("%d\n",(d.row/2)*(d.col/2));
 }
