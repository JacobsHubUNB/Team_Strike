#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generate_team.h"

Team * generate_ai(Tile game_map[10][10]){
    int count = 0;
    int max = 20;
    int min = 10;
    int posMax = 9;
    Team * team1 = (Team *)malloc(sizeof(Team));
    if(!team1){
        printf("Failed to generate Team");
        return NULL;
    }
    while(count < 4){
        team1->members[count]=malloc(sizeof(Character ));
        if(team1->members[count] == NULL){
            printf("Character Generation failed");
            return NULL;
        }
        team1->members[count]->health = rand() %((max - min) + 1 ) + min;
        team1->members[count]->attack = rand() %(min + 1 );
        team1->members[count]->pos[0] = rand() %(posMax + 1 );
        team1->members[count]->pos[1] = rand() %(posMax + 1 );
        while(game_map[team1->members[count]->pos[1]][team1->members[count]->pos[0]].type != '.'){
            team1->members[count]->pos[0] = rand() %(posMax + 1 );
            team1->members[count]->pos[1] = rand() %(posMax + 1 );
        }
        count++;
    }
    team1->teamName = "BYTESTORM";
    int posX, posY;
    for(int i = 0; i < 4; i++){
        posX = team1->members[i]->pos[0]; 
        posY = team1->members[i]->pos[1];
        if(team1->members[i]->attack > 6)
            game_map[ posY][posX].type = 'X';
        else
            game_map[ posY][posX].type = 'D';

    }
    return team1;
}
Team * generate_player(Tile game_map [10][10]){
    int count = 0;
    int max = 20;
    int min =10;
    int posMax = 9;
    Team * team = (Team*)malloc(sizeof(Team));
    if(!team){
        printf("Failed to generate Player Team");
        return NULL;
    }
    while(count < 4){
        team->members[count]=malloc(sizeof(Character));
        if(team->members[count] == NULL){
            printf("Player Character Generation failed");
            return NULL;
        }
        team->members[count]->health = rand() %((max - min) + 1 ) + min;
        team->members[count]->attack = rand() %(min + 1 );
        team->members[count]->pos[0] = rand() %(posMax + 1 );
        team->members[count]->pos[1] = rand() %(posMax + 1 );
        while(game_map[team->members[count]->pos[0]][team->members[count]->pos[1]].type != '.'){
            team->members[count]->pos[0] = rand() %(posMax + 1 );
            team->members[count]->pos[1] = rand() %(posMax + 1 );
        }
        count++;
    }
     int posX, posY;
   for(int i = 0; i < 4; i++){
        posX = team->members[i]->pos[0]; 
        posY = team->members[i]->pos[1];
        game_map[posY][posX].type = '1' + i;
    }
    return team;
}