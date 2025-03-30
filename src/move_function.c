#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"
#include "team.h"

void attack(Character * attacker, Character * defender, Tile gameMap[10][10]){
    char attackerType = gameMap[attacker->pos[1]][attacker->pos[0]].type;
    
    if(attacker == NULL || defender == NULL){
        printf("Error: no attacker/defender found.\n");
        return;
    }

    defender -> health -= attacker -> attack;

    printf("%d damage dealt!\n", attacker->attack);

    if(defender -> health <= 0){
        printf("******************\nCHARACTER DEFEATED!\n****************\n");
        //Once target hp < 0, move onto its tile
        gameMap[attacker->pos[1]][attacker->pos[0]].type = '.';
        attacker->pos[0] = defender->pos[0];
        attacker->pos[1] = defender->pos[1];
        gameMap[defender->pos[1]][defender->pos[0]].type = attackerType;
    }
}

bool moveRight(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    bool success =false;
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX + 1;
    int newY = posY;
    char moverType = gameMap[posY][posX].type;

    if(newX >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success = true;
        }
    }

    if(gameMap[newY][newX].type == '.'){
        team->members[character - 1]->pos[0] = newX;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        success = true;
    }
    else{
        printf("Invalid move\n");
    }

    return success;
}

bool moveLeft(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    bool success = false;
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX - 1;
    int newY = posY;
    char moverType = gameMap[posY][posX].type;

    if(newX >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success = true;
        }
    }
    if(gameMap[posY][newX].type == '.'){
        team->members[character - 1]->pos[0] = newX;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        success = true;
    }
    else{
        printf("Invalid move\n");    
    }

    return success;   
}

bool moveUp(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    bool success = false;
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newY = posY - 1;
    int newX = posX;
    char moverType = gameMap[posY][posX].type;

    if(newY >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success = true;
        }
    }
    if(gameMap[newY][newX].type == '.'){
        team->members[character - 1]->pos[1] = newY;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        success = true;
    }
    else{
        printf("Invalid move\n");
    }

    return success;
}

bool moveDown(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    bool success = false;
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newY = posY + 1;
    int newX = posX;
    char moverType = gameMap[posY][posX].type;

    if(newY >= 10){
        printf("Invalid move: Out of bounds.\n");
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success = true;
        }
    }
    if(gameMap[newY][newX].type == '.'){
        team->members[character - 1]->pos[0] = newY;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        success = true;
    }
    else{
        printf("Invalid move\n");
    }

    return success;
}