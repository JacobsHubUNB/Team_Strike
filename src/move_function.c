#include "move_function.h"
#include <stdio.h>
#include "tile.h"
#include "team.h"
void moveRight(Team* team, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];

    if(posY + 1 < 10 && gameMap[posX][posY + 1].type == '.'){
        team->members[character - 1]->pos[1] += 1;  // Move UP
        gameMap[posX][posY].type = '.'; // Clear old position
        gameMap[posX][posY + 1].type = '0' + character; // Mark new position
    }
    else{
        printf("Invalid move\n");
    }
}

void moveLeft(Team* team, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];

    if(posY - 1 >= 0 && gameMap[posX][posY - 1].type == '.'){
        team->members[character - 1]->pos[1] -= 1;  // Move Down
        gameMap[posX][posY].type = '.'; // Clear old position
        gameMap[posX][posY - 1].type = '0' + character; // Mark new position
    } 
    else{
        printf("Invalid move\n");
    }
}

void moveUp(Team* team, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];

    if(posX - 1 >= 0 && gameMap[posX - 1][posY].type == '.'){
        team->members[character - 1]->pos[0] -= 1;  // Move Left
        gameMap[posX][posY].type = '.'; // Clear old position
        gameMap[posX - 1][posY].type = '0' + character; // Mark new position
    } 
    else{
        printf("Invalid move\n");
    }
}

void moveDown(Team* team, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];

    if(posX + 1 < 10 && gameMap[posX + 1][posY].type == '.'){
        team->members[character - 1]->pos[0] += 1;  // Move Right
        gameMap[posX][posY].type = '.'; // Clear old position
        gameMap[posX + 1][posY].type = '0' + character; // Mark new position
    } 
    else{
        printf("Invalid move\n");
    }
}
