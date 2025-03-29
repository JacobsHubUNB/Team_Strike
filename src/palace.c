#include <stdlib.h>
#include <stdio.h>
#include "palace.h"

void addDefender(Palace * palace,int health)
{
    if(palace->numDefender < 5){
        if(palace->numDefender ==0){
            palace->defender = (Defender*) malloc(sizeof(Defender));
            if(!palace->defender){
                printf("Defender malloc failed");
            
            }
        }
        palace->defender = (Defender*) realloc(palace->defender, sizeof(Defender)* (palace->numDefender+1));
        if(!palace->defender){
            printf("Defender malloc failed");
            
        }
        else{
            int index = palace->numDefender -1;
            switch(index){
            case 1 :
                palace->defender[index].pos[0] = 5;
                palace->defender[index].pos[1] = 6;
                break;
            case 2 :
                palace->defender[index].pos[0] = 5;
                palace->defender[index].pos[1] = 4;
                break;
            case 3 :
                palace->defender[index].pos[0] = 4;
                palace->defender[index].pos[1] = 5;
                break;
            case 4 :
                palace->defender[index].pos[0] = 6;
                palace->defender[index].pos[1] = 5;
                break;
            default:
                printf("All defender positions taken");
        }
        }
        
        
    }
    else
        printf("Defender limit Reached");
    
}
