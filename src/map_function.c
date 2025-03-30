#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map_function.h"

// Function definition
void printMap(Tile gameMap[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", gameMap[i][j].type);
        }
        printf("\n");
    }
}

void generateMap(Tile gameMap[10][10]){
    srand(time(NULL));

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            gameMap[i][j].type = '.'; 
            if(i == 5 && j == 5){
                gameMap[i][j].type = 'P';
            }
        }
    }

    int obstacleCount = 20;
    int placedObstacles = 0;
    while(placedObstacles <= obstacleCount){
        int X = rand() % 10;
        int Y = rand() % 10;

        if(gameMap[X][Y].type == '.' && gameMap[X][Y].type != 'P' && gameMap[X][Y].type != '8'){
            gameMap[X][Y].type = 'O';
            placedObstacles++;
        }
    }
}