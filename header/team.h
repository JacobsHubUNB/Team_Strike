#ifndef TEAM_H
#define TEAM_H
#include <stdbool.h>
#include "character.h"

typedef struct team{
    Character * members [4];
    char * teamName;
    bool isAI;
}Team;

#endif