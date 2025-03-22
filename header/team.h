#ifndef TEAM_H
#define TEAM_H
#include "character.h"

typedef struct team{
    Character * members [4];
    char * teamName;    
}Team;

#endif