#ifndef MOVE_FUNCTION_H
#define MOVE_FUNCTION_H
#include "tile.h"
#include "team.h"

void moveRight(Team* team1, Team* team2,  Tile gameMap [10][10], int character);
void moveLeft(Team* team, Team* team2, Tile gameMap [10][10], int character);
void moveUp(Team* team, Team* team2, Tile gameMap [10][10], int character);
void moveDown(Team* team, Team* team2, Tile gameMap [10][10], int character);
void attack(Character * attacker, Character * defender);

#endif