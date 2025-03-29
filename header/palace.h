#ifndef PALACE_H
#define PALACE_H
#include "defender.h"
typedef struct Palace{
    int health;
    Defender *defender;
    int numDefender;
}Palace;
void addDefender(Palace * palace, int health);
void freeDefenders(Palace * palace,int numDefenders);
#endif