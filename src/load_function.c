#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_function.h"

void loadGame(Tile gameWorld[10][10], Team* playerTeam, Team* teamAI, FILE* file) {
    if (file == NULL) {
        printf("Error: File pointer is NULL.\n");
        return;
    }

    char line[100];
    int section = 0; // 0 = header, 1 = game world, 2 = player team, 3 = AI team
    int row = 0;
    int characterNum = -1;

    // Read line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Remove newline character if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // Skip empty lines
        if (len == 0) {
            continue;
        }

        // Determine which section we're in
        if (strcmp(line, "GAME WORLD:") == 0) {
            section = 1;
            row = 0;
            continue;
        } else if (strcmp(line, "PLAYER TEAM:") == 0) {
            section = 2;
            characterNum = -1;
            continue;
        } else if (strcmp(line, "AI TEAM:") == 0) {
            section = 3;
            characterNum = -1;
            continue;
        }

        // Process the line based on the current section
        switch (section) {
            case 1: // Game World
                if (row < 10) {
                    for (int col = 0; col < 10; col++) {
                        gameWorld[row][col].type = line[col * 2]; // Accounting for spaces
                    }
                    row++;
                }
                break;

            case 2: // Player Team
                if (strncmp(line, "Team Name: ", 11) == 0) {
                    // Free existing name if it exists
                    if (playerTeam->teamName != NULL) {
                        free(playerTeam->teamName);
                    }
                    
                    // Allocate and copy new name
                    playerTeam->teamName = malloc(strlen(line + 11) + 1);
                    if (playerTeam->teamName == NULL) {
                        printf("Error: Failed to allocate memory for team name.\n");
                        return;
                    }
                    strcpy(playerTeam->teamName, line + 11);
                } else if (strncmp(line, "Character ", 10) == 0) {
                    characterNum = line[10] - '1'; // Convert to 0-based index
                } else if (strncmp(line, "  Health: ", 10) == 0 && characterNum >= 0 && characterNum < 4) {
                    playerTeam->members[characterNum]->health = atoi(line + 10);
                } else if (strncmp(line, "  Attack: ", 10) == 0 && characterNum >= 0 && characterNum < 4) {
                    playerTeam->members[characterNum]->attack = atoi(line + 10);
                } else if (strncmp(line, "  Position: (", 13) == 0 && characterNum >= 0 && characterNum < 4) {
                    int x, y;
                    sscanf(line + 13, "%d, %d)", &x, &y);
                    playerTeam->members[characterNum]->pos[0] = x;
                    playerTeam->members[characterNum]->pos[1] = y;
                }
                break;

            case 3: // AI Team
                if (strncmp(line, "Team Name: ", 11) == 0) {
                    // For AI team, name is likely static but update it anyway
                    strcpy(teamAI->teamName, "AI");
                } else if (strncmp(line, "Character ", 10) == 0) {
                    characterNum = line[10] - '1'; // Convert to 0-based index
                } else if (strncmp(line, "  Health: ", 10) == 0 && characterNum >= 0 && characterNum < 4) {
                    teamAI->members[characterNum]->health = atoi(line + 10);
                } else if (strncmp(line, "  Attack: ", 10) == 0 && characterNum >= 0 && characterNum < 4) {
                    teamAI->members[characterNum]->attack = atoi(line + 10);
                } else if (strncmp(line, "  Position: (", 13) == 0 && characterNum >= 0 && characterNum < 4) {
                    int x, y;
                    sscanf(line + 13, "%d, %d)", &x, &y);
                    teamAI->members[characterNum]->pos[0] = x;
                    teamAI->members[characterNum]->pos[1] = y;
                }
                break;
        }
    }

    // Update the map based on character positions
    // First clear existing character markers (except palace and obstacles)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (gameWorld[i][j].type != 'P' && gameWorld[i][j].type != 'O') {
                gameWorld[i][j].type = '.';
            }
        }
    }

    // Then place the characters back on the map
    for (int i = 0; i < 4; i++) {
        if (playerTeam->members[i]->health > 0) {
            int x = playerTeam->members[i]->pos[0];
            int y = playerTeam->members[i]->pos[1];
            gameWorld[y][x].type = '1' + i; // Characters 1-4
        }
        
        if (teamAI->members[i]->health > 0) {
            int x = teamAI->members[i]->pos[0];
            int y = teamAI->members[i]->pos[1];
            gameWorld[y][x].type = 'A' + i; // Characters A-D
        }
    }
    
    printf("Game loaded successfully.\n");
}