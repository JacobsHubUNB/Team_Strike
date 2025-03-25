#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bot_logic.h"

int calculateDistance(int x, int y) {
    return (int) sqrt(pow(x, 2) + pow(y, 2));
}

void advance(Team * ai, Team * player, Tile gamemap[10][10]){
    int closest, temp;
    int xval, yval;
    closest = 10000;
    int playerIndex, AIindex;

    for(int i = 0; i < 4; i++){
        for(int e = 0; e < 4; e++){
            xval = (player->members[e]->pos[0] - ai->members[i]->pos[0]);
            yval = (player->members[e]->pos[1] - ai->members[i]->pos[1]);
            temp = calculateDistance(xval,yval);
            
            if(temp < closest){
                closest = temp;
                playerIndex = e;
                AIindex = i;
            }
        }
    }

    xval = (player->members[playerIndex]->pos[0] - ai->members[AIindex]->pos[0]);
    yval = (player->members[playerIndex]->pos[1] - ai->members[AIindex]->pos[1]);

    if(xval > 0)
        moveRight(ai, player, gamemap, AIindex);

    else if(yval > 0)
        moveUp(ai, player, gamemap, AIindex);
    else if(xval < 0)
        moveLeft(ai, player, gamemap, AIindex);
    else if(yval<0)
        moveDown(ai, player, gamemap, AIindex);
    else{
        xval = (5 - ai->members[0]->pos[0]);
        yval = (5 - ai->members[0]->pos[1]);
        if(xval>0)
            moveRight(ai, player, gamemap, AIindex);
        else if(yval>0)
            moveUp(ai, player, gamemap, AIindex);
        else if(xval<0)
            moveLeft(ai, player, gamemap, AIindex);
        else
            moveDown(ai, player, gamemap, AIindex);
    }
}