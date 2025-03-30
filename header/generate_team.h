#ifndef GENERATE_TEAM_H
#define GENERATE_TEAM_H
#include "team.h"
#include "tile.h"
#include <stdbool.h>

Team * generate_ai(Tile game_map[10][10]);
Team * generate_player(Tile game_map[10][10]);
Team * generate_team(Tile game_map[10][10], bool isAI);

#endif