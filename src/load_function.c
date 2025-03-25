#include "load_function.h"
#include <stdio.h>
#include <stdlib.h>

void loadGame(Tile gameWorld[10][10], Team* playerTeam, Team* teamAI, FILE* file) {
    if (file == NULL) {
        printf("Error: File pointer is NULL.\n");
        return;
    }

    // Load game world (entire Tile structure)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fread(&gameWorld[i][j], sizeof(char), 1, file);
        }
    }

    // Load player team name
    int nameLen;
    fread(&nameLen, sizeof(int), 1, file);
    playerTeam->teamName = malloc(nameLen);
    fread(playerTeam->teamName, sizeof(char), nameLen, file);

    // Load character data (both teams)
    for (int i = 0; i < 4; i++) {
        fread(&playerTeam->members[i]->health, sizeof(int), 1, file);
        fread(&playerTeam->members[i]->attack, sizeof(int), 1, file);
        fread(playerTeam->members[i]->pos, sizeof(int), 2, file);

        fread(&teamAI->members[i]->health, sizeof(int), 1, file);
        fread(&teamAI->members[i]->attack, sizeof(int), 1, file);
        fread(teamAI->members[i]->pos, sizeof(int), 2, file);
    }
    printf("Game loaded successfully.\n");
}

