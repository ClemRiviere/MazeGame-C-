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

 Maze createMaze(Dimensions d){
     int i;
     Maze maze;
     maze.grid = (int **)malloc(sizeof(int*)*d.row);
     for (i=0;i<d.row;i++){
         maze.grid[i] = (int *)malloc(sizeof(int)*d.col);
     }
     if(maze.grid==NULL)
     {
         fprintf(stderr,"Malloc problem (Maze allocation) !");
         exit(EXIT_FAILURE);
     }
     maze.d = d;
     return maze;
 }

 void destroyMaze(Maze *maze){
     int i;
     for (i=0;i<maze->d.row;i++){
         free(maze->grid[i]);
     }
     free(maze->grid);
 }

  void initMaze(Maze *maze){
     int i,j;
     int cpt = 1;
     for (i=0;i<maze->d.row;i++){
         for (j=0;j<maze->d.col;j++){
             if (j%2==0 || i%2==0){
                 maze->grid[i][j]=WALL;
             }
             else {
                 maze->grid[i][j]=cpt;
                 cpt += 1;
             }
         }
     }
 }

 void displayMaze(Maze maze){
     int i,j;
     int cpt = 0;
     for (i=0;i<maze.d.row;i++){
         for (j=0;j<maze.d.col;j++){
             if (maze.grid[i][j]==WALL){
                 printf("#");
             }
             else {
                 cpt += 1;
                 printf(" ");
             }
         }
         printf("\n");
     }
     /*printf("%d\n",cpt);
     printf("%d\n",(maze.d.row/2)*(maze.d.col/2));*/
 }

 /*void generateMaze(Maze maze){

 }*/
