#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bot_logic.h"

void advance(Team * ai, Team * player, Tile gamemap[10][10]){
    int closest, temp, close_palace;
    int xval, yval;
    closest = 10000;
    int playerIndex, AIindex, plalace_finder;
    for(int i =0; i < 4; i++){
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
        }
    }

    xval = (player->members[playerIndex]->pos[0] - ai->members[AIindex]->pos[0]);
    yval = (player->members[playerIndex]->pos[1] - ai->members[AIindex]->pos[1]);

    if(xval > 0)
        moveRight(ai, player, gamemap, AIindex, 1);

    else if(yval > 0)
        moveUp(ai, player, gamemap, AIindex, 1);
    else if(xval < 0)
        moveLeft(ai, player, gamemap, AIindex, 1);
    else if(yval<0)
        moveDown(ai, player, gamemap, AIindex, 1);
    else(){
        xval = (5 - ai->members[plalace_finder]->pos[0]);
        yval = (5 - ai->members[plalace_finder]->pos[1]);
        if(xval>0)
            moveRight(ai, player, gamemap, AIindex, 1);
        else if(yval>0)
            moveUp(ai, player, gamemap, AIindex, 1);
        else if(xval<0)
            moveLeft(ai, player, gamemap, AIindex, 1);
        else
            moveDown(ai, player, gamemap, AIindex, 1);
    }
}