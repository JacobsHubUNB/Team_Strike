#include "tile.h"
#include "team.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int attack_palace(Palace* palace, Character * attacker){
    printf("\n*********************\n!!PALACE UNDER ATTACK!!\n***************\n");
    palace->health -= attacker->attack;
    if(palace->health <=0){
        printf("\n*********************PALACE DESTROYED! GAME OVER!****************************\n");
        free(palace->defender);
        free(palace);
        return 1;
    }
    return 0;
}

bool moveRight(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    bool success =false;
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
            success =true;
            return success;
        }
    }

    if(newX <10 && gameMap[newY][newX].type == '.'){
        team->members[character - 1]->pos[0] += 1;  
        gameMap[posY][posX].type = '.'; 
        gameMap[posY][newX].type = moverType;
        success = true;
        return success;
        
    }
    else
        printf("Invalid move\n");
    return success;
   
}

bool moveLeft(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    bool success = false;
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX - 1;
    int newY = posY;
    char moverType = gameMap[posX][posY].type;
    if(newX >= 10 || newY >= 10){
        printf("Invalid move: Out of bounds.\n");
    }
    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success =true;
            return success;
        }
    }
    if(posY - 1 >= 0 && gameMap[posY][newX].type == '.'){
        team->members[character - 1]->pos[0] -= 1;  
        gameMap[posY][posX].type = '.'; 
        gameMap[posY][newX].type = moverType;
        success =true;
            return success;
    }
    else
        printf("Invalid move\n");
    return success;   
}

bool moveUp(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
     bool success = false;
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newY = posY -1;
    char moverType = gameMap[posX][posY].type;
    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success =true;
            return success;
        }
    }
    if(posY - 1 >= 0 && gameMap[newY][posX].type == '.'){
        team->members[character - 1]->pos[1] += 1;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][posX].type = moverType;
        success =true;
        return success;
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
    char moverType = gameMap[posX][posY].type;

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[character - 1], enemyTeam->members[i], gameMap);
            success =true;
            return success;
        }
    }
    if(posX - 1 >= 0 && gameMap[newY][posX].type == '.'){
        team->members[character - 1]->pos[0] -= 1;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        success =true;
        return success;
        }
    else{
        printf("Invalid move\n");
    }

    return success;
}