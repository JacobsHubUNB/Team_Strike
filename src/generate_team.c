#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generate_team.h"

Team * generate_ai(Tile game_map[10][10]){
    int count = 0;
    int max = 20;
    int min = 10;
    int posMax = 9;
    Team * teamAI = (Team *)malloc(sizeof(Team));
    if(!teamAI){
        printf("Failed to generate Team");
        return NULL;
    }
    while(count < 4){
        teamAI->members[count]=malloc(sizeof(Character ));
        if(teamAI->members[count] == NULL){
            printf("Character Generation failed");
            return NULL;
        }
        teamAI->members[count]->health = rand() %((max - min) + 1 ) + min;
        teamAI->members[count]->attack = rand() %(min + 1 );
        teamAI->members[count]->pos[0] = rand() %(posMax + 1 );
        teamAI->members[count]->pos[1] = rand() %(posMax + 1 );
        while(game_map[teamAI->members[count]->pos[1]][teamAI->members[count]->pos[0]].type != '.'){
            teamAI->members[count]->pos[0] = rand() %(posMax + 1 );
            teamAI->members[count]->pos[1] = rand() %(posMax + 1 );
        }
        count++;
    }
    
    teamAI->teamName = "AI";
    int posX, posY;
    for(int i = 0; i < 4; i++){
        posX = teamAI->members[i]->pos[0]; 
        posY = teamAI->members[i]->pos[1];
        if(teamAI->members[i]->attack > 6)
            game_map[ posY][posX].type = 'X';
        else
            game_map[ posY][posX].type = 'D';

    }

    return teamAI;
}

Team * generate_player(Tile game_map [10][10]){
    int count = 0;
    int max = 20;
    int min =10;
    int posMax = 9;
    Team * teamPlayer = (Team*)malloc(sizeof(Team));
    if(!teamPlayer){
        printf("Failed to generate Player Team");
        return NULL;
    }

    while(count < 4){
        teamPlayer->members[count]=malloc(sizeof(Character));
        if(teamPlayer->members[count] == NULL){
            printf("Player Character Generation failed");
            return NULL;
        }
        teamPlayer->members[count]->health = rand() %((max - min) + 1 ) + min;
        teamPlayer->members[count]->attack = rand() %(min + 1 );
        teamPlayer->members[count]->pos[0] = rand() %(posMax + 1 );
        teamPlayer->members[count]->pos[1] = rand() %(posMax + 1 );
        while(game_map[teamPlayer->members[count]->pos[0]][teamPlayer->members[count]->pos[1]].type != '.'){
            teamPlayer->members[count]->pos[0] = rand() %(posMax + 1 );
            teamPlayer->members[count]->pos[1] = rand() %(posMax + 1 );
        }
        count++;
    }

    int posX, posY;
    for(int i = 0; i < 4; i++){
        posX = teamPlayer->members[i]->pos[0]; 
        posY = teamPlayer->members[i]->pos[1];
        game_map[posY][posX].type = '1' + i;
    }

    return teamPlayer;
}