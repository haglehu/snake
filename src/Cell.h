#ifndef _CELL
#define _CELL

#include <raylib.h>
#include <stdbool.h>

typedef struct Cell Cell;

struct Cell
{
    int x;
    int y;
    Cell* next;
};
void append(Cell**, int, int);
void removeLast(Cell*);
bool collides(Vector2, Cell*);

#endif
