#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bot_logic.h"
#include <stdbool.h>

bool isTileBlocked(Tile gameMap[10][10], int x, int y) {
    return gameMap[y][x].type != '.' && gameMap[y][x].type != 'P';
}

// Helper function to find alternative path
bool findAlternativePath(Team* ai, Team* player, Tile gameMap[10][10], int AIindex, int targetX, int targetY) {
    // Try different movement strategies to avoid obstacles
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    
    for (int i = 0; i < 4; i++) {
        int newX = ai->members[AIindex]->pos[0] + dx[i];
        int newY = ai->members[AIindex]->pos[1] + dy[i];
        
        if(!isTileBlocked(gameMap, newX, newY)){
            if(dx[i] > 0)
                return moveRight(ai, player, gameMap, AIindex + 1 );
            else if (dx[i] < 0)
                return moveLeft(ai, player, gameMap, AIindex + 1);
            else if (dy[i] > 0)
                return moveDown(ai, player, gameMap, AIindex + 1);
            else
                return moveUp(ai, player, gameMap, AIindex + 1);
        }
    }
    
    return false;
}

void advance(Team* ai, Team* player, Tile gameMap[10][10]) {
    int closest = 10000;
    int close_palace = 100000;
    int playerIndex = -1, AIindex = -1, palace_finder = -1;

    // Find the closest living player character
    for (int i = 0; i < 4; i++) {
        for (int e = 0; e < 4; e++) {
            if (player->members[e]->health > 0 && ai->members[i]->health > 0) {
                int xval = (player->members[e]->pos[0] - ai->members[i]->pos[0]);
                int yval = (player->members[e]->pos[1] - ai->members[i]->pos[1]);
                int temp = sqrt(pow(xval, 2) + pow(yval, 2));
                
                if (temp < closest) {
                    closest = temp;
                    playerIndex = e;
                    AIindex = i;
                }
            }
        }
    }

    // Find the AI character closest to the palace
    for (int i = 0; i < 4; i++) {
        if (ai->members[i]->health > 0) {
            int xval = (5 - ai->members[i]->pos[0]);
            int yval = (5 - ai->members[i]->pos[1]);
            int temp = sqrt(pow(xval, 2) + pow(yval, 2));
            
            if (temp < close_palace) {
                close_palace = temp;
                palace_finder = i;
            }
        }
    }

    // Ensure we found a valid character
    if (AIindex == -1 || playerIndex == -1) {
        return;
    }

    // Target coordinates
    int targetX = player->members[playerIndex]->pos[0];
    int targetY = player->members[playerIndex]->pos[1];
    
    // Current AI character position
    int currentX = ai->members[AIindex]->pos[0];
    int currentY = ai->members[AIindex]->pos[1];

    // Determine movement direction
    int xMove = (targetX > currentX) ? 1 : ((targetX < currentX) ? -1 : 0);
    int yMove = (targetY > currentY) ? 1 : ((targetY < currentY) ? -1 : 0);

    bool result = false;
    int moveAttempts = 0;

    // Try to move towards the target character
    while (!result && moveAttempts < 3) {
        // Prioritize X movement first
        if (xMove != 0) {
            if (xMove > 0)
                result = moveRight(ai, player, gameMap, AIindex + 1);
            else
                result = moveLeft(ai, player, gameMap, AIindex + 1);
        }

        // If X movement failed, try Y movement
        if (!result) {
            if (yMove > 0)
                result = moveDown(ai, player, gameMap, AIindex + 1);
            else
                result = moveUp(ai, player, gameMap, AIindex + 1);
        }

        // If both fail, try to find an alternative path
        if (!result) {
            result = findAlternativePath(ai, player, gameMap, AIindex, targetX, targetY);
        }

        moveAttempts++;
    }

    // If no movement towards player, move towards palace
    if (!result && palace_finder != -1) {
        int palaceX = 5;
        int palaceY = 5;
        
        // Move towards palace
        if (ai->members[palace_finder]->pos[0] < palaceX)
            result = moveRight(ai, player, gameMap, palace_finder + 1);
        else if (ai->members[palace_finder]->pos[0] > palaceX)
            result = moveLeft(ai, player, gameMap, palace_finder + 1);
        else if (ai->members[palace_finder]->pos[1] < palaceY)
            result = moveDown(ai, player, gameMap, palace_finder + 1);
        else
            result = moveUp(ai, player, gameMap, palace_finder + 1);
    }
}