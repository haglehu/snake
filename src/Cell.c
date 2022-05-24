#include "Cell.h"
#include <stdlib.h>

Cell* append(Cell* body, int x, int y)
{
    Cell* head = malloc(sizeof(Cell));

    if (head == NULL)
    {
        exit(42);
    }
    head->next = body;
    head->x = x;
    head->y = y;

    return head;
}

void removeLast(Cell* list)
{
    if (list->next->next == NULL)
    {
        free(list->next);
        list->next = NULL;
        return;
    }
    removeLast(list->next);
}

bool collides(Vector2 pos, Cell* body)
{
    if (body == NULL)
    {
        return false;
    }
    if (pos.x == body->x && pos.y == body->y)
    {
        return true;
    }
    return collides(pos, body->next);
}
