#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "team.h"
#include "tile.h"
#include "save_function.h"
#include "load_function.h"
#include "move_function.h"
#include "map_function.h"
#include "generate_team.h"
#include "bot_logic.h"

int checkTeamAlive(Team* team) {
    int aliveCount = 0;
    for (int i = 0; i < 4; i++) {
        if (team->members[i]->health > 0)
            aliveCount++;
    }
    return aliveCount;
}

void printStats(Team * player, Team * ai){
    printf("*******************\nTeam %s stats:\n", player->teamName);
    for(int i = 0; i < 4; i++){
        if(player->members[i]->health > 0)
            printf("char#%d HP:%d AD:%d \n", i, player->members[i]->health, player->members[i]->attack);
    }
}

int main(int argc, char ** argv){
    printf("Welcome to Team Strike!\n");
    int MAX_COLS = 10; 
    int MAX_ROWS = 10;
    Tile gameMap [MAX_ROWS][MAX_COLS];
    generateMap(gameMap);
 
    //Generate Enemy Team(AI)
    Team * AI = generate_ai(gameMap);
    AI->teamName = "AI";
     
    printf("Generating Characters for <Team %s>\n", AI->teamName);
    //Dont print out character coord, just show on map
    for(int i = 0; i < 4; i++){
        printf("HP: %d AD: %d\n", AI->members[i]->health, AI->members[i]->attack);
    }
    
    // Players's team
    char Name[50];
    printf("\nPlease enter your team name: ");
    scanf("%49s", Name);
    Team * team1 = generate_player(gameMap);
    team1->teamName = malloc(strlen(Name) + 1);

    if(team1->teamName == NULL){
        printf("Team name malloc failed.\n");
    }

    strcpy(team1->teamName, Name);
 
    printf("Generating Characters for <Team %s>\n", team1->teamName);
    //Dont print out character coord, just show on map
    for(int i = 0; i < 4; i++){
        printf("HP: %d AD: %d\n", team1->members[i]->health, team1->members[i]->attack);
    }

    printMap(gameMap);

    //User Inputs
    char userInput[2];
    bool inMovementMode = false;

    while(1){
        // Check for game end conditions
        int playerAlive = checkTeamAlive(team1);
        int aiAlive = checkTeamAlive(AI);

        if (playerAlive == 0) {
            printf("Game Over! AI Team wins!\n");
            break;
        }
        if (aiAlive == 0) {
            printf("Congratulations! %s Team wins!\n", team1->teamName);
            break;
        }

        if(!inMovementMode){
            printf("(p)lay, (s)ave, (l)oad or (q)uit?: \n");
            scanf(" %c", &userInput[0]);
        
            if(userInput[0] == 'p'){
                inMovementMode = true;
            }
            else if(userInput[0] == 'q'){
                printf("Exiting game.\n");
                // Free memory
                for (int i = 0; i < 4; i++) {
                    free(team1->members[i]);
                    free(AI->members[i]);
                }
                free(team1);
                free(AI);                         
                return 0;
            }
            else if(userInput[0] == 's'){
                char saveName[100];
                printf("Enter save name: "); 
                scanf("%99s", &saveName[0]);
                FILE * file = fopen(saveName, "w");
                saveGame(gameMap, team1, AI, file); 
                fclose(file);
            }
            else if(userInput[0] == 'l'){
                char saveName[100];
                printf("Enter save name: ");
                scanf("%99s", &saveName[0]);
                FILE * file = fopen(saveName, "r");
                loadGame(gameMap, team1, AI, file);
                fclose(file);
                printMap(gameMap);
            }
        }
        else{
            printf("Select which character to move (or q to return): ");
            scanf(" %c", &userInput[0]);
            getchar();

            if(userInput[0] == 'q'){
                inMovementMode = false;
                continue;
            }

            if(userInput[0] >= '1' && userInput[0] <= '4'){
                char character = userInput[0] - '0';

                printf("Now enter a command {w, a, s, d to move}: ");
                scanf(" %c", &userInput[0]);

                if(userInput[0] == 'q'){
                    inMovementMode = false;
                    continue;
                }

                //move logic
                switch(userInput[0]){
                    case 'w':
                        moveUp(team1, AI, gameMap, character);
                        printMap(gameMap);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap);
                        printStats(team1, AI);
                        break;

                    case 'a':
                        moveLeft(team1, AI, gameMap, character);
                        printMap(gameMap);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap);
                        printStats(team1, AI);
                        break;
                        
                    case 's':
                        moveDown(team1, AI, gameMap, character);
                        printMap(gameMap);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap);
                        printStats(team1, AI);
                        break;

                    case 'd':
                        moveRight(team1, AI, gameMap, character);
                        printMap(gameMap);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap);
                        printStats(team1, AI);
                        break;

                    default:
                        printf("Invalid movement command\n");
                        break;
                }
            }
            else{
                printf("Invalid character selected.\n");
            }
        }   
    }
}
