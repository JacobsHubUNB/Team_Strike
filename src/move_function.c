#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tile.h"
#include "team.h"

void attack(Character * attacker, Character * defender, Tile gameMap[10][10]){
    if(attacker == NULL || defender == NULL){
        printf("Error: no attacker/defender found.\n");
        return;
    }

    char attackerType = gameMap[attacker->pos[1]][attacker->pos[0]].type;

    if(attacker->berserker && attacker->health <= 7){
        defender->health -= attacker->attack*2;
        printf("Berserker ability activated!\n");
        printf("%d damage dealt!\n", attacker->attack*2);
    }
    else{
        defender->health -= attacker->attack;
        printf("%d damage dealt!\n", attacker->attack);
    }

    if(defender -> health <= 0){
        printf("\n******************\nCHARACTER DEFEATED!\n****************\n");
        //Once target hp < 0, move onto its tile
        gameMap[attacker->pos[1]][attacker->pos[0]].type = '.';
        attacker->pos[0] = defender->pos[0];
        attacker->pos[1] = defender->pos[1];
        gameMap[defender->pos[1]][defender->pos[0]].type = attackerType;
        defender->pos[0] = 999;
        defender->pos[1] = 999;
    }
}
int attack_palace(Palace* palace, Character * attacker){
    printf("\n*********************\n!!PALACE UNDER ATTACK!!\n***************\n");
    palace->health -= attacker->attack;
    if(palace->health <=0){
        printf("\n*********************PALACE DESTROYED! GAME OVER!****************************\n");
        return 1;
    }
    return 0;
}
void attack_Defender(){
    printf("\n*************\n!Defender Taking Damage!\n***********\n");
    int def = 10;
    if(def <=0){
    printf("\n*************\n!Defender Destroyed!\n***********\n");  
    }
}
bool moveRight(Team* team, Team* enemyTeam, Tile gameMap [10][10], int characterIndex){
    int posX = team->members[characterIndex]->pos[0];
    int posY = team->members[characterIndex]->pos[1];
    int newX = posX + 1;
    int newY = posY;
    char moverType = gameMap[posY][posX].type;

    if(newX >= 10){
        printf("Invalid move: Out of bounds.\n");
        return false;
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[characterIndex], enemyTeam->members[i], gameMap);
            return true;
        }
    }

    if(gameMap[newY][newX].type == 'O' && team->members[characterIndex]->bulldozer){
        team->members[characterIndex]->pos[0] = newX;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        printf("Bulldozer ability activated!\n");
        return true;
    }

    if(gameMap[newY][newX].type == '.'){
        team->members[characterIndex]->pos[0] = newX;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        return true;
    }
    else if(newY == 5 && newX == 5){
        if(team->isAI){
            attack_palace(gameMap[5][5].palace, team->members[characterIndex]);
            return true;
        }
        printf("Can't move: that's your own palace!\n");
    }
    else if(gameMap[newY][newX].type == '8'){
        attack_Defender();
    }
    else{
        printf("Can't move due to '%c' blocking\n", gameMap[newY][newX].type);
    }
    return false;
}

bool moveLeft(Team* team, Team* enemyTeam, Tile gameMap [10][10], int characterIndex){
    int posX = team->members[characterIndex]->pos[0];
    int posY = team->members[characterIndex]->pos[1];
    int newX = posX - 1;
    int newY = posY;
    char moverType = gameMap[posY][posX].type;

    if(newX < 0){
        printf("Invalid move: Out of bounds.\n");
        return false;
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == newX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[characterIndex], enemyTeam->members[i], gameMap);
            return true;
        }
    }

    if(gameMap[newY][newX].type == 'O' && team->members[characterIndex]->bulldozer){
        team->members[characterIndex]->pos[0] = newX;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        printf("Bulldozer ability activated!\n");
        return true;
    }

    if(gameMap[posY][newX].type == '.'){
        team->members[characterIndex]->pos[0] = newX;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        return true;
    }
    else if(newY == 5 && newX == 5){
        if(team->isAI){
            attack_palace(gameMap[5][5].palace, team->members[characterIndex]);
            return true;
        }
        printf("Can't move: that's your own palace!\n");
    }
    else if(gameMap[newY][newX].type == '8'){
        attack_Defender();
    }
    else{
        printf("Can't move due to '%c' blocking\n", gameMap[newY][newX].type);    
    }
    return false;
}

bool moveUp(Team* team, Team* enemyTeam, Tile gameMap [10][10], int characterIndex){
    int posX = team->members[characterIndex]->pos[0];
    int posY = team->members[characterIndex]->pos[1];
    int newY = posY - 1;
    int newX = posX;
    char moverType = gameMap[posY][posX].type;

    if(newY < 0){
        printf("Invalid move: Out of bounds.\n");
        return false;
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[characterIndex], enemyTeam->members[i], gameMap);
            return true;
        }
    }

    if(gameMap[newY][newX].type == 'O' && team->members[characterIndex]->bulldozer){
        team->members[characterIndex]->pos[1] = newY;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        printf("Bulldozer ability activated!\n");
        return true;
    }

    if(gameMap[newY][newX].type == '.'){
        team->members[characterIndex]->pos[1] = newY;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        return true;
    }
    else if(newY == 5 && newX == 5){
        if(team->isAI){
            attack_palace(gameMap[5][5].palace, team->members[characterIndex]);
            return true;
        }
        printf("Can't move: that's your own palace!\n");
    }
    else if(gameMap[newY][newX].type == '8'){
        attack_Defender();
    }
    else{
        printf("Can't move due to '%c' blocking\n", gameMap[newY][newX].type); 
    }
    return false;
}

bool moveDown(Team* team, Team* enemyTeam, Tile gameMap [10][10], int characterIndex){
    int posX = team->members[characterIndex]->pos[0];
    int posY = team->members[characterIndex]->pos[1];
    int newY = posY + 1;
    int newX = posX;
    char moverType = gameMap[posY][posX].type;

    if(newY >= 10){
        printf("Invalid move: Out of bounds.\n");
        return false;
    }

    for(int i = 0; i < 4; i++){
        if(enemyTeam->members[i]->pos[0] == posX && enemyTeam->members[i]->pos[1] == newY){
            printf("Enemy detected! Attacking...\n");
            attack(team->members[characterIndex], enemyTeam->members[i], gameMap);
            return true;
        }
    }

    if(gameMap[newY][newX].type == 'O' && team->members[characterIndex]->bulldozer){
        team->members[characterIndex]->pos[1] = newY;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        printf("Bulldozer ability activated!\n");
        return true;
    }

    if(gameMap[newY][newX].type == '.'){
        team->members[characterIndex]->pos[1] = newY;  
        gameMap[posY][posX].type = '.'; 
        gameMap[newY][newX].type = moverType;
        return true;
    }
    else if(newY == 5 && newX == 5){
        if(team->isAI){
            attack_palace(gameMap[5][5].palace, team->members[characterIndex]);
            return true;
        }
        printf("Can't move: that's your own palace!\n");
    }
    else if(gameMap[newY][newX].type == '8'){
        attack_Defender();
    }
    else{
        printf("Can't move due to '%c' blocking\n", gameMap[newY][newX].type);
    }
    return false;
}