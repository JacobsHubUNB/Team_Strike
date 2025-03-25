#include "save_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveGame(Tile gameWorld[10][10], Team* playerTeam, Team* teamAI, FILE* file) {
    if (file == NULL) {
        printf("Error: File pointer is NULL.\n");
        return;
    }

    // Save game world with readable tile types
    fprintf(file, "GAME WORLD:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fprintf(file, "%c ", gameWorld[i][j].type);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    // Save player team information
    fprintf(file, "PLAYER TEAM:\n");
    fprintf(file, "Team Name: %s\n", playerTeam->teamName);
    
    for (int i = 0; i < 4; i++) {
        fprintf(file, "Character %d:\n", i + 1);
        fprintf(file, "  Health: %d\n", playerTeam->members[i]->health);
        fprintf(file, "  Attack: %d\n", playerTeam->members[i]->attack);
        fprintf(file, "  Position: (%d, %d)\n", playerTeam->members[i]->pos[0], playerTeam->members[i]->pos[1]);
    }
    fprintf(file, "\n");

    // Save AI team information
    fprintf(file, "AI TEAM:\n");
    fprintf(file, "Team Name: %s\n", teamAI->teamName);
    
    for (int i = 0; i < 4; i++) {
        fprintf(file, "Character %d:\n", i + 1);
        fprintf(file, "  Health: %d\n", teamAI->members[i]->health);
        fprintf(file, "  Attack: %d\n", teamAI->members[i]->attack);
        fprintf(file, "  Position: (%d, %d)\n", teamAI->members[i]->pos[0], teamAI->members[i]->pos[1]);
    }

    printf("Game saved successfully.\n");
}