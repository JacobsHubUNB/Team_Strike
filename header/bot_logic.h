#ifndef BOT_LOGIC_H
#define BOT_LOGIC_H
#include "move_function.h"
#include <stdbool.h>

void advance(Team * ai, Team * player, Tile game_map[10][10]);
bool isTileBlocked(Tile gameMap[10][10], int x, int y);
bool findAlternativePath(Team* ai, Team* player, Tile gameMap[10][10], int AIindex, int targetX, int targetY);
#endif