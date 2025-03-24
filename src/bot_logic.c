#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bot_logic.h"

void advance(Team * ai, Team * player, Tile gamemap[10][10]){
    int closest, temp;
    int xval, yval;
    closest = 10000;
    int playerIndex, AIindex;

    for(int i = 0; i < 4; i++){
        for(int e = 0; e < 4; e++){
    
            xval = (player->members[e]->pos[0] - ai->members[i]->pos[0]);
            yval = (player->members[e]->pos[1] - ai->members[i]->pos[1]);
            temp = sqrt(pow(xval, 2) + pow(yval, 2));
            if(temp < closest){
                closest = temp;
                playerIndex = e;
                AIindex = i;
            }


            if (playerIndex == -1 || AIindex == -1) {
                printf("No valid AI-Player pair found\n");
                return;  // If no valid pair was found, exit the function
            }
        }
    }

    xval = (player->members[playerIndex]->pos[0] - ai->members[AIindex]->pos[0]);
    yval = (player->members[playerIndex]->pos[1] - ai->members[AIindex]->pos[1]);

    if(xval > 0){
        moveRight(ai, player, gamemap, AIindex, 1);
    }
    else if(yval > 0){
        moveUp(ai, player, gamemap, AIindex, 1);
    }
    else if(xval < 0){
        moveLeft(ai, player, gamemap, AIindex, 1);
    }
    else{
        moveDown(ai, player, gamemap, AIindex, 1);
    }
}