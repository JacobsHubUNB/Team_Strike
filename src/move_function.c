#include "tile.h"
#include "team.h"
#include <stdio.h>
#include <stdlib.h>

void attack(Character * attacker, Character * defender, Tile gameMap[10][10]){
    char attackerType = gameMap[attacker->pos[0]][attacker->pos[1]].type;

    if(attacker == NULL || defender == NULL){
        printf("Error: no attacker/defender found.\n");
        return;
    }

    defender -> health -= attacker -> attack;

    printf("%d damage dealt!\n", attacker->attack);

    if(defender -> health <= 0){
        printf("Character defeated!\n");
        
        //Once target hp < 0, move onto its tile
        gameMap[attacker->pos[0]][attacker->pos[1]].type = '.';
        attacker->pos[0] = defender->pos[0];
        attacker->pos[1] = defender->pos[1];
        gameMap[defender->pos[0]][defender->pos[1]].type = attackerType;
    }
}

void moveRight(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX;
    int newY = posY + 1;
    char moverType = gameMap[posX][posY].type;

    if(newX >= 10 || newY >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            return;
        }
    }

    if(posY + 1 < 10 && gameMap[posX][posY + 1].type == '.'){
        team->members[character - 1]->pos[1] += 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX][posY + 1].type = moverType;
        return;
    }
    else{
        printf("Invalid move\n");
    }
}

void moveLeft(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX;
    int newY = posY - 1;
    char moverType = gameMap[posX][posY].type;

    if(newX >= 10 || newY >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            return;
        }
    }

    if(posY - 1 >= 0 && gameMap[posX][posY - 1].type == '.'){
        team->members[character - 1]->pos[1] -= 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX][posY - 1].type = moverType;
        return; 
    }
    else{
        printf("Invalid move\n");
    }
}

void moveUp(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX - 1;
    int newY = posY;
    char moverType = gameMap[posX][posY].type;

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            return;
        }
    }

    if(posX - 1 >= 0 && gameMap[posX - 1][posY].type == '.'){
        team->members[character - 1]->pos[0] -= 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX - 1][posY].type = moverType;
        return; 
    } 
    else{
        printf("Invalid move\n");
    }
}

void moveDown(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX + 1;
    int newY = posY;
    char moverType = gameMap[posX][posY].type;

    if(newX >= 10 || newY >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            return;
        }
    }

    if(posX + 1 < 10 && gameMap[posX + 1][posY].type == '.'){
        team->members[character - 1]->pos[0] += 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX + 1][posY].type = moverType;
        return;
    } 
    else{
        printf("Invalid move: Tile is occupied.\n");
    }
}