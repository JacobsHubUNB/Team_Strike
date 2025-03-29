#ifndef TILE_H
#define TILE_H
#include "palace.h"
typedef struct tile {
    char type; // 'P' for palace, 'O' for obstacle, '.' for open space
    int x, y;
    Palace * palace;
} Tile;
void addPalace(Palace * palace);
#endif
