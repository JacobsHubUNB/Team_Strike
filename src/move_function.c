#include "tile.h"
#include "team.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void attack(Character * attacker, Character * defender, Tile gameMap[10][10]){
    char attackerType = gameMap[attacker->pos[1]][attacker->pos[0]].type;
    
    if(attacker == NULL || defender == NULL){
        printf("Error: no attacker/defender found.\n");
        return ;
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
bool moveRight(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character, int isAI){
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
    else
        printf("Invalid move\n");
    return success;
   
}

void moveLeft(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX;
    int newY = posY - 1;

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

    if(posY - 1 >= 0 && gameMap[posX][posY - 1].type == '.' && isAI == 1){
        team->members[character - 1]->pos[1] -= 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX][posY - 1].type = 'X';
        return; 
    } 
    else if(posY - 1 >= 0 && gameMap[posX][posY - 1].type == '.'){
        team->members[character - 1]->pos[1] -= 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX][posY - 1].type = '0' + character; 
        return;
    }
    else
        printf("Invalid move\n");
    return success;   
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

    return success;
}

void moveDown(Team* team, Team* enemyTeam, Tile gameMap [10][10], int character){
    int posX = team->members[character - 1]->pos[0];
    int posY = team->members[character - 1]->pos[1];
    int newX = posX + 1;
    int newY = posY;

    // Check if the new position is within map bounds
    if (newY < 10) {
        // Check for enemy characters in the new position
        for (int i = 0; i < 4; i++) {
            if (enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY) {
                printf(" Attacking Team %s...\n************", enemyTeam->teamName);
                attack(team->members[character - 1], enemyTeam->members[i], gameMap);
                success = true;
                return success;
            }
        }

    if(posX + 1 < 10 && gameMap[posX + 1][posY].type == '.' && isAI == 1){
        team->members[character - 1]->pos[0] += 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX + 1][posY].type = 'X';
        return;
    } 
    else if(posX + 1 < 10 && gameMap[posX + 1][posY].type == '.'){
        team->members[character - 1]->pos[0] += 1;  
        gameMap[posX][posY].type = '.'; 
        gameMap[posX + 1][posY].type = '0' + character; 
        return;
    }
    else{
        printf("Invalid move: Tile is occupied.\n");
    }

    return success;
}