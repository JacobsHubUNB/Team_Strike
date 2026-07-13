// Engine mode: line-based protocol for the web front end.
// Reads commands from stdin, prints game-log lines to stdout,
// and after each command emits one line:  STATE {json}
//
// Commands:
//   new <teamName>     start a new game
//   move <1-4> <wasd>  move a character (AI takes its turn after)
//   skip               skip player turn (AI still moves)
//   quit               exit
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "team.h"
#include "tile.h"
#include "move_function.h"
#include "map_function.h"
#include "generate_team.h"
#include "bot_logic.h"
#include "palace.h"

static int teamAliveCount(Team* team){
    int aliveCount = 0;
    for(int i = 0; i < 4; i++){
        if(team->members[i]->health > 0)
            aliveCount++;
    }
    return aliveCount;
}

static void freeTeam(Team * team, bool freeName){
    if(team == NULL) return;
    for(int i = 0; i < 4; i++){
        free(team->members[i]);
    }
    if(freeName && team->teamName != NULL){
        free(team->teamName);
    }
    free(team);
}

static void printJsonEscaped(const char * s){
    for(; *s; s++){
        if(*s == '"' || *s == '\\') putchar('\\');
        putchar(*s);
    }
}

static void printTeamJson(Team * team){
    printf("{\"name\":\"");
    printJsonEscaped(team->teamName ? team->teamName : "");
    printf("\",\"members\":[");
    for(int i = 0; i < 4; i++){
        Character * c = team->members[i];
        printf("%s{\"hp\":%d,\"ad\":%d,\"x\":%d,\"y\":%d,\"berserker\":%s,\"bulldozer\":%s}",
               i ? "," : "",
               c->health, c->attack, c->pos[0], c->pos[1],
               c->berserker ? "true" : "false",
               c->bulldozer ? "true" : "false");
    }
    printf("]}");
}

static void printState(Tile gameMap[10][10], Team * player, Team * AI, Palace * palace){
    const char * status = "playing";
    if(player != NULL && AI != NULL){
        if(teamAliveCount(player) == 0 || palace->health <= 0)
            status = "ai_wins";
        else if(teamAliveCount(AI) == 0)
            status = "player_wins";
    }
    else{
        status = "waiting";
    }

    printf("STATE {\"status\":\"%s\",\"palace\":%d,\"map\":[", status, palace->health);
    for(int i = 0; i < 10; i++){
        printf("%s\"", i ? "," : "");
        for(int j = 0; j < 10; j++){
            char t = gameMap[i][j].type;
            putchar((t == '"' || t == '\\') ? '?' : t);
        }
        printf("\"");
    }
    printf("]");
    if(player != NULL && AI != NULL){
        printf(",\"player\":");
        printTeamJson(player);
        printf(",\"ai\":");
        printTeamJson(AI);
    }
    printf("}\n");
    fflush(stdout);
}

int main(void){
    srand(time(NULL));
    setvbuf(stdout, NULL, _IONBF, 0);

    int MAX_COLS = 10;
    int MAX_ROWS = 10;
    Tile gameMap[MAX_ROWS][MAX_COLS];
    Palace palace;
    Team *AI = NULL;
    Team *team1 = NULL;

    initPalace(&palace);
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            gameMap[i][j].type = '.';

    char line[256];
    while(fgets(line, sizeof(line), stdin)){
        line[strcspn(line, "\r\n")] = '\0';

        if(strncmp(line, "new", 3) == 0){
            freeTeam(team1, true);
            freeTeam(AI, false);

            generateMap(gameMap, &palace);
            AI = generate_team(gameMap, true);
            team1 = generate_team(gameMap, false);

            const char * name = line[3] == ' ' ? line + 4 : "Player";
            if(*name == '\0') name = "Player";
            team1->teamName = malloc(strlen(name) + 1);
            if(team1->teamName != NULL){
                strcpy(team1->teamName, name);
            }
            printf("A new battle begins. Defend the palace, Team %s!\n", name);
        }
        else if(strncmp(line, "move", 4) == 0){
            int characterIndex;
            char dir;
            if(team1 == NULL || AI == NULL){
                printf("No game in progress.\n");
            }
            else if(sscanf(line + 4, " %d %c", &characterIndex, &dir) != 2 ||
                    characterIndex < 1 || characterIndex > 4 ||
                    (dir != 'w' && dir != 'a' && dir != 's' && dir != 'd')){
                printf("Invalid move command.\n");
            }
            else if(team1->members[characterIndex - 1]->health <= 0){
                printf("Character %d is defeated and can't move.\n", characterIndex);
            }
            else{
                switch(dir){
                    case 'w': moveUp(team1, AI, gameMap, characterIndex - 1); break;
                    case 'a': moveLeft(team1, AI, gameMap, characterIndex - 1); break;
                    case 's': moveDown(team1, AI, gameMap, characterIndex - 1); break;
                    case 'd': moveRight(team1, AI, gameMap, characterIndex - 1); break;
                }
                if(teamAliveCount(AI) > 0 && teamAliveCount(team1) > 0 && palace.health > 0){
                    printf("--- AI's turn ---\n");
                    advance(AI, team1, gameMap);
                }
            }
        }
        else if(strcmp(line, "skip") == 0){
            if(team1 == NULL || AI == NULL){
                printf("No game in progress.\n");
            }
            else{
                printf("Turn skipped.\n--- AI's turn ---\n");
                advance(AI, team1, gameMap);
            }
        }
        else if(strcmp(line, "quit") == 0){
            break;
        }
        else if(strcmp(line, "state") != 0){
            printf("Unknown command: %s\n", line);
        }

        printState(gameMap, team1, AI, &palace);
    }

    freeTeam(team1, true);
    freeTeam(AI, false);
    return 0;
}
