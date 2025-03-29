#ifndef MOVE_FUNCTION_H
#define MOVE_FUNCTION_H
#include <stdbool.h>
#include "tile.h"
#include "team.h"

bool moveRight(Team* team1, Team* team2,  Tile gameMap [10][10], int character);
bool moveLeft(Team* team, Team* team2, Tile gameMap [10][10], int character);
bool moveUp(Team* team, Team* team2, Tile gameMap [10][10], int character);
bool moveDown(Team* team, Team* team2, Tile gameMap [10][10], int character);
void attack(Character * attacker, Character * defender);
int attack_palace(Palace* palace, Character * attacker);

#endif