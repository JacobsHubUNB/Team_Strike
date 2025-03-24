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

int main(int argc, char ** argv){
    //Generate Map
    //Generate Map
    //================================================================================================================//
    
    printf("Welcome to Team Strike!\n");
     int MAX_COLS = 10; //map is always 10x10
    int MAX_ROWS = 10;
    Tile gameMap [MAX_ROWS][MAX_COLS];
    generateMap(gameMap);
 
 
    //Generate Enemy Team(AI)
    //================================================================================================================//
    Team * AI = generate_ai(gameMap);
    AI->teamName = "AI";
     
    printf("Generating Characters for <Team %s>\n", AI->teamName);
    //Dont print out character coord, just show on map
    for(int i; i <4; i++){
        printf("HP: %d AD: %d\n", AI->members[i]->health, AI->members[i]->attack);
    }
    
    
 
    // Players's team
    //================================================================================================================//                 
    //================================================================================================================//                 
    char Name[50];
    printf("\nPlease enter your team name: ");
    scanf("%s", Name);
    Team * team1 = NULL;
    team1 = generate_player(gameMap);
    team1->teamName = Name;
 
    printf("Generating Characters for <Team %s>\n", team1->teamName);
    //Dont print out character coord, just show on map
    for(int i; i <4; i++){
        printf("HP: %d AD: %d\n", team1->members[i]->health, team1->members[i]->attack);
    }
   
    //================================================================================================================//
 
 

    printMap(gameMap);

    //User Inputs
    //================================================================================================================//                                             
    char userInput[2];
    bool inMovementMode = false;

    while(1){
        if(!inMovementMode){
            printf("(p)lay, (s)ave, (l)oad or (q)uit?: \n");
            scanf(" %c", &userInput[0]);
        
            if(userInput[0] == 'p'){
                inMovementMode = true;
            }
            else if(userInput[0] == 'q'){
                printf("Exiting game.\n");
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
            }
            else if(userInput[0] == 'l'){
                char saveName[100];
                printf("Enter save name: ");
                scanf("%99s", &saveName[0]);
                FILE * file = fopen(saveName, "r");
                loadGame(gameMap, team1, AI, file);
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
                        break;

                    case 'a':
                        moveLeft(team1, AI, gameMap, character);
                        printMap(gameMap);
                        break;

                    case 's':
                        moveDown(team1, AI, gameMap, character);
                        printMap(gameMap);
                        break;

                    case 'd':
                        moveRight(team1, AI, gameMap, character);
                        printMap(gameMap);
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
    

