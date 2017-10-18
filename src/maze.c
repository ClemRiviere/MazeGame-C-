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
 * @version     1.0.2 - 16-10-2017
 *
 * @todo nothing to do for the moment.
 * @bug no known bug for the moment.
 */

/**
 * @file maze.c
 *
 * @brief The maze functions for the maze generator program.
 */

 #include "../include/maze.h"

 Maze createMaze(Dimensions d){
     int i;
     Maze maze;

     /* The grid allocation */
     maze.grid = (int **)malloc(sizeof(int*)*d.row);
     for (i=0;i<d.row;i++){
         maze.grid[i] = (int *)malloc(sizeof(int)*d.col);
     }

     /* Check for malloc problems */
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
     srand(time(NULL));
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

int exist(Maze maze){
    char *title = (char *)malloc((strlen(maze.name)+10)*sizeof(char));
    sprintf(title,"saves/%s",maze.name);
    FILE *file = fopen(title,"r");
    if (file==NULL){
      return 0;
    }
    fclose(file);
    return 1;
}

int saveMaze(Maze maze){
    int i;
    char *title = (char *)malloc((strlen(maze.name)+10)*sizeof(char));
    sprintf(title,"saves/%s",maze.name);
    FILE *file = fopen(title,"w+");
    if (file==NULL){
      printf("Error opening file!\n");
      return -1;
    }
    fwrite(&maze.d,sizeof(Dimensions),1,file);
    for (i=0; i<maze.d.row; i++)
      fwrite(maze.grid[i], sizeof(maze.grid[i][0]), maze.d.col, file);
    fclose(file);
    /*free(title);*/
    return 0;
}

Maze readMaze(char *path_name){
    int i;
    char *token;
    char *maze_name = (char *)malloc(sizeof(char)*2);

    Maze maze;
    Dimensions d;
    FILE *file = fopen(path_name,"r");
    if (file==NULL){
      printf("Error opening file!\n");
    }
    fread(&d,sizeof(Dimensions),1,file);
    maze = createMaze(d);

    /* get the first token */
    token = strtok(path_name, "/");
    /* walk through other tokens */
    while( token != NULL ) {

      maze_name = (char *)realloc(maze_name,sizeof(char)*strlen(token));
      strcpy(maze_name,token);

      token = strtok(NULL, "/");
    }

    maze.name = maze_name;
    for (i=0; i<maze.d.row; i++)
      fread(maze.grid[i], sizeof(int), maze.d.col, file);
    fclose(file);
    /* Not need to init walls ... because that's juste for the generation */
    /*free(maze_name);*/
    return maze;
}

void generateMaze(Maze *maze){
    int res;
    int nb_broken = 0;
    do{
      res = processMazeGeneration(maze,&nb_broken);
    }while(res == 0);
    /* Entrance and exit cells */
    maze->grid[1][0] = maze->grid[1][1];
    maze->grid[maze->d.row-2][maze->d.col-1] = maze->grid[1][1];
}

int processMazeGeneration(Maze *maze, int *nb_broken){
     int wall_break = 0;
     int random = rand()%maze->n_walls;
     Position wall_pos = maze->walls[random];

     /**CONTROLS PRINTFS
     printf("RANDOM : %d",random);
     printf("X : %d | Y : %d\n",wall_pos.x,wall_pos.y);*/

     /* Horizontal */
     if (maze->grid[wall_pos.x][wall_pos.y-1] != WALL &&
          maze->grid[wall_pos.x][wall_pos.y+1] != WALL &&
          maze->grid[wall_pos.x][wall_pos.y-1] != maze->grid[wall_pos.x][wall_pos.y+1]){
         maze->grid[wall_pos.x][wall_pos.y] = maze->grid[wall_pos.x][wall_pos.y-1];
         wall_break = 1;
     }
     /* Vertical */
     else if (maze->grid[wall_pos.x-1][wall_pos.y] != WALL &&
                maze->grid[wall_pos.x+1][wall_pos.y] != WALL &&
                maze->grid[wall_pos.x-1][wall_pos.y] != maze->grid[wall_pos.x+1][wall_pos.y]){
         maze->grid[wall_pos.x][wall_pos.y] = maze->grid[wall_pos.x-1][wall_pos.y];
         wall_break = 1;
    }
    if (wall_break == 1){
      delete_wall(maze, random);
      fill_id(maze, wall_pos);
      *nb_broken+=1;
    }
    /* TEST PRINT
    displayMaze(*maze);
    printf("\n\n");*/
    return generation_end(*maze,*nb_broken);
 }

 int generation_end(Maze maze,int nb_broken){
    /* Condition finded on the internet */
    /* TEST PRINT
    printf("NB_BROKEN : %d\n",nb_broken);
    */
    if (nb_broken == (maze.d.row/2)*(maze.d.col/2)-1){
      return 1;
    }
    return 0;
 }

 void delete_wall(Maze *maze, int pos){
   int i;
   for (i=pos;i<maze->n_walls;i++){
     maze->walls[i] = maze->walls[i+1];
   }
   maze->n_walls -= 1;
   maze->walls = (Position *) realloc(maze->walls, (maze->n_walls) * sizeof(Position *));
   /** CONTROLS PRINTF
   for (i=0;i<maze->n_walls;i++){
     printf("[X : %d | Y : %d]\n",maze->walls[i].x,maze->walls[i].y);
   }
   printf("N_WALLS : %d\n",maze->n_walls);*/
 }

 void fill_id(Maze *maze, Position pos){
   Position new_pos;
   /* LEFT */
   if (maze->grid[pos.x][pos.y-1]!=WALL &&
        maze->grid[pos.x][pos.y-1]!=maze->grid[pos.x][pos.y]){
      /* FILLING ID*/
      maze->grid[pos.x][pos.y-1] = maze->grid[pos.x][pos.y];
      new_pos.x = pos.x;
      new_pos.y = pos.y-1;
      fill_id(maze,new_pos);
   }
   /* RIGHT */
   if (maze->grid[pos.x][pos.y+1]!=WALL &&
        maze->grid[pos.x][pos.y+1]!=maze->grid[pos.x][pos.y]){
      /* FILLING ID*/
      maze->grid[pos.x][pos.y+1] = maze->grid[pos.x][pos.y];
      new_pos.x = pos.x;
      new_pos.y = pos.y+1;
      fill_id(maze,new_pos);
   }
   /* ABOVE */
   if (maze->grid[pos.x-1][pos.y]!=WALL &&
        maze->grid[pos.x-1][pos.y]!=maze->grid[pos.x][pos.y]){
      /* FILLING ID*/
      maze->grid[pos.x-1][pos.y] = maze->grid[pos.x][pos.y];
      new_pos.x = pos.x-1;
      new_pos.y = pos.y;
      fill_id(maze,new_pos);
   }
   /* UNDER */
   if (maze->grid[pos.x+1][pos.y]!=WALL &&
        maze->grid[pos.x+1][pos.y]!=maze->grid[pos.x][pos.y]){
      /* FILLING ID*/
      maze->grid[pos.x+1][pos.y] = maze->grid[pos.x][pos.y];
      new_pos.x = pos.x+1;
      new_pos.y = pos.y;
      fill_id(maze,new_pos);
   }
 }
