#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
    int min = 10;
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

Team * generate_team(Tile game_map[10][10], bool isAI){
    Team * team = malloc(sizeof(Team));
    if(team == NULL){
        printf("Failed to allocate memory for team\n");
        return NULL;
    }
    team->isAI = isAI;
    team->teamName = NULL;

    for(int i = 0; i < 4; i++){
        team->members[i] = malloc(sizeof(Character));
        if(team->members[i] == NULL){
            printf("Failed to allocate memory for team member %d\n", i);

            for(int j = 0; j < i; j++){
                free(team->members[j]);
            }
            free(team);
            return NULL;
        }
        int posX, posY;
        bool positionTaken;

        if(isAI){
            team->teamName = "AI";

            do{
                posX = rand() % 2;  
                posY = rand() % 10;
                positionTaken = false;

                for(int j = 0; j < i; j++){
                    if(team->members[j]->pos[0] == posX && team->members[j]->pos[1] == posY){
                        positionTaken = true;
                        break;
                    }
                }
            }while (game_map[posY][posX].type != '.' || positionTaken);

            team->members[i]->pos[0] = posX;
            team->members[i]->pos[1] = posY;

            team->members[i]->berserker = false;
            team->members[i]->bulldozer = false;

            if(i % 2 == 0){
                team->members[i]->attack = 3 + rand()%10;
                team->members[i]->health = 15 + rand()%10;
                game_map[posY][posX].type = 'D';
            }
            else{
                team->members[i]->attack = 10 + rand()%10;
                team->members[i]->health = 7 + rand()%10;
                game_map[posY][posX].type = 'X';
            }
        }
        else{
            do{
                posX = 8 + rand() % 2;  
                posY = rand() % 10;

                
                positionTaken = false;
                for (int j = 0; j < i; j++) {
                    if (team->members[j]->pos[0] == posX && team->members[j]->pos[1] == posY) {
                        positionTaken = true;
                        break;
                    }
                }
            } while (game_map[posY][posX].type != '.' || positionTaken);

            team->members[i]->pos[0] = posX;
            team->members[i]->pos[1] = posY;
            
            team->members[i]->attack = 8 + rand()%7;
            team->members[i]->health = 8 + rand()%7;

            team->members[i]->berserker = (rand()%3 == 0);
            team->members[i]->bulldozer = !team->members[i]->berserker;

            game_map[posY][posX].type = '1' + i;
        }
    }
    return team;
}
