#ifndef TILE_H
#define TILE_H

typedef struct tile{
    char type; // 'P' for palace, 'O' for obstacle, '.' for open space
    int x, y;
}Tile;

#endif
