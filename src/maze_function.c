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
 * @version     0.0.3 - 11-10-2017
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

     /* The grid allocation */
     maze.grid = (int **)malloc(sizeof(int*)*d.row);
     for (i=0;i<d.row;i++){
         maze.grid[i] = (int *)malloc(sizeof(int)*d.col);
     }
     if(maze.grid==NULL)
     {
         fprintf(stderr,"Malloc problem (Maze allocation) !");
         exit(EXIT_FAILURE);
     }

     /* The dimensions of the maze */
     maze.d = d;

     /**
      * The wall tab allocation
      * The number of walls is the area of the center square (without contour) - the number of cells
      */
     maze.n_walls = ((d.row-2)*(d.col-2))-((d.row/2)*(d.col/2));
     maze.walls = (Position *)malloc(sizeof(Position*)*maze.n_walls);

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
     int cpt_id = 1;
     int cpt_wall = 0;
     /* Init walls and the id of cells */
     for (i=0;i<maze->d.row;i++){
         for (j=0;j<maze->d.col;j++){
             if (j%2==0 || i%2==0){
                 maze->grid[i][j]=WALL;
                 /* Count the walls that can be destroyed */
                 if (i%(maze->d.row-1)!=0 && j%(maze->d.col-1)!=0){
                   maze->walls[cpt_wall].x = i;
                   maze->walls[cpt_wall].y = j;
                   cpt_wall += 1;
                 }
             }
             else {
                 maze->grid[i][j]=cpt_id;
                 cpt_id += 1;
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
     /* VERIF PRINTS
     for (i=0;i<maze.n_walls;i++){
       printf("[X : %d | Y : %d]\n",maze.walls[i].x,maze.walls[i].y);
     }
     printf("N_WALLS : %d\n",maze.n_walls);
     printf("%d\n",cpt);
     printf("%d\n",(maze.d.row/2)*(maze.d.col/2));*/
 }


 /*void generateMaze(Maze maze){

 }*/
