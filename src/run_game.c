#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "team.h"
#include "tile.h"
#include "save_function.h"
#include "load_function.h"
#include "move_function.h"
#include "map_function.h"
#include "generate_team.h"
#include "bot_logic.h"
#include "palace.h"

// Allocate a team shell for loadGame to fill in
Team * allocEmptyTeam(bool isAI){
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
        team->members[i]->health = 0;
        team->members[i]->attack = 0;
        team->members[i]->pos[0] = 0;
        team->members[i]->pos[1] = 0;
        team->members[i]->berserker = false;
        team->members[i]->bulldozer = false;
    }
    return team;
}

int checkTeamAlive(Team* team){
    int aliveCount = 0;
    for(int i = 0; i < 4; i++){
        if(team->members[i]->health > 0)
            aliveCount++;
    }
    return aliveCount;
}

void printAIstats(Team * AI){
    printf("*******************\nTeam %s stats:\n", AI->teamName);
    for(int i = 0; i < 4; i++){
        if(AI->members[i]->health > 0){
            printf("char#%d HP:%d AD:%d \n", i+1, AI->members[i]->health, AI->members[i]->attack);
        }
    }
    printf("\n");
}

void printPlayerStats(Team * player){
    printf("*******************\nTeam %s stats:\n", player->teamName);
    for(int i = 0; i < 4; i++){
        if(player->members[i]->health > 0){
            printf("char#%d HP:%d AD:%d ", i+1, player->members[i]->health, player->members[i]->attack);

            if(player->members[i]->berserker){
                printf("[Berserker]\n");
            }
            else{
                printf("[Bulldozer]\n");
            }
        }
    }
    printf("\n");
}

int main(int argc, char ** argv){
    srand(time(NULL));

    printf("Welcome to Team Strike!\n");

    // Prompt user to load a save file or start a new game
    char userInput[2];
    printf("Would you like to load a save file? (y/n): ");
    scanf(" %c", &userInput[0]);

    int MAX_COLS = 10; 
    int MAX_ROWS = 10;
    Tile gameMap[MAX_ROWS][MAX_COLS];
    Palace palace;
    Team *AI = NULL;
    Team *team1 = NULL;
    
    if(userInput[0] == 'y' || userInput[0] == 'Y'){
        // Load game if user wants to
        char saveName[100];
        printf("Enter save file name: ");
        scanf("%99s", saveName);
        
        FILE *file = fopen(saveName, "r");
        if (file == NULL) {
            printf("Error: Could not open save file. Starting a new game.\n");
            generateMap(gameMap, &palace);
            AI = generate_team(gameMap, true);
            team1 = generate_team(gameMap, false);
            team1->teamName = malloc(strlen("Player") + 1);
            if(team1->teamName != NULL){
                strcpy(team1->teamName, "Player");
            }
        } else {
            // The teams must exist before loadGame can fill them in
            team1 = allocEmptyTeam(false);
            AI = allocEmptyTeam(true);
            AI->teamName = "AI";

            initPalace(&palace);
            gameMap[5][5].palace = &palace;

            loadGame(gameMap, team1, AI, file);
            fclose(file);
        }
    } else {
        // Start a new game if user chooses not to load a save
        generateMap(gameMap, &palace);
        AI = generate_team(gameMap, true);

        printf("Generating Characters for <Team %s>\n", AI->teamName);
        for(int i = 0; i < 4; i++){
            printf("HP: %d AD: %d\n", AI->members[i]->health, AI->members[i]->attack);
        }

        // Players's team
        char Name[50];
        printf("\nPlease enter your team name: ");
        scanf("%49s", Name);
        team1 = generate_team(gameMap, false);
        team1->teamName = malloc(strlen(Name) + 1);

        if(team1->teamName == NULL){
            printf("Team name malloc failed.\n");
        }

        strcpy(team1->teamName, Name);

        printf("Generating Characters for <Team %s>\n", team1->teamName);
        printPlayerStats(team1);
    }

    printMap(gameMap, &palace);

    bool inMovementMode = false;

    while(1){
        int playerAlive = checkTeamAlive(team1);
        int aiAlive = checkTeamAlive(AI);

        if (playerAlive == 0) {
            printf("Game Over! AI Team wins!\n");
            for (int i = 0; i < 4; i++) {
                free(team1->members[i]);
                free(AI->members[i]);
            }
            free(team1);
            free(AI); 
            return 0;
        }
        if (aiAlive == 0) {
            printf("Congratulations! %s Team wins!\n", team1->teamName);
            for (int i = 0; i < 4; i++) {
                free(team1->members[i]);
                free(AI->members[i]);
            }
            free(team1);
            free(AI);
            return 0;
        }
        if(gameMap[5][5].palace->health <=0){
            printf("Game Over! AI Team wins!\n");
            for (int i = 0; i < 4; i++) {
                free(team1->members[i]);
                free(AI->members[i]);
            }
            free(team1);
            free(AI);
            return 0;
        }

        if(!inMovementMode){
            printf("(p)lay, (s)ave or (q)uit?: \n");
            scanf(" %c", &userInput[0]);
        
            if(userInput[0] == 'p'){
                inMovementMode = true;
            }
            else if(userInput[0] == 'q'){
                printf("Exiting game.\n");
                for (int i = 0; i < 4; i++) {
                    free(team1->members[i]);
                    free(AI->members[i]);
                }
                free(team1->teamName);
                free(team1);
                free(AI);                         
                return 0;
            }
            else if(userInput[0] == 's'){
                char saveName[100];
                printf("Enter save name: "); 
                scanf("%99s", &saveName[0]);
                FILE *file = fopen(saveName, "w");
                saveGame(gameMap, team1, AI, file); 
                fclose(file);
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
                int characterIndex = userInput[0] - '1';

                if (characterIndex < 0 || characterIndex >= 4 || 
                    team1->members[characterIndex] == NULL || 
                    team1->members[characterIndex]->health <= 0) {
                    printf("Invalid character or character is defeated!\n");
                    continue;
                }

                printf("Now enter a command {w, a, s, d to move} or {x to skip}: ");
                scanf(" %c", &userInput[0]);

                if(userInput[0] == 'q'){
                    inMovementMode = false;
                    continue;
                }

                //move logic
                switch(userInput[0]){
                    case 'w':
                        moveUp(team1, AI, gameMap, characterIndex);
                        printMap(gameMap, &palace);
                        printAIstats(AI);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap, &palace);
                        printf("Palace HP: %d\n", palace.health);
                        printPlayerStats(team1);
                        break;

                    case 'a':
                        moveLeft(team1, AI, gameMap, characterIndex);
                        printMap(gameMap, &palace);
                        printAIstats(AI);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap, &palace);
                        printf("Palace HP: %d\n", palace.health);
                        printPlayerStats(team1);
                        break;
                        
                    case 's':
                        moveDown(team1, AI, gameMap, characterIndex);
                        printMap(gameMap, &palace);
                        printAIstats(AI);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap, &palace);
                        printf("Palace HP: %d\n", palace.health);
                        printPlayerStats(team1);
                        break;

                    case 'd':
                        moveRight(team1, AI, gameMap, characterIndex);
                        printMap(gameMap, &palace);
                        printAIstats(AI);
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap, &palace);
                        printf("Palace HP: %d\n", palace.health);
                        printPlayerStats(team1);
                        break;

                    case 'x':
                        printf("Skipping player turn\n");
                        printf("***************************************************************\n");
                        printf("\nAI's turn...\n");
                        advance(AI, team1, gameMap);
                        printMap(gameMap, &palace);
                        printf("Palace HP: %d\n", palace.health);
                        printPlayerStats(team1);
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
    
    for (int i = 0; i < 4; i++) {
        free(team1->members[i]);
        free(AI->members[i]);
    }
    free(team1);
    free(AI);                         
    return 1;
}
