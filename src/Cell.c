#include "Cell.h"
#include <stdlib.h>

void append(Cell** body, int x, int y)
{
    Cell* head = malloc(sizeof(Cell));

    if (head == NULL)
    {
        exit(42);
    }
    head->next = *body;
    head->x = x;
    head->y = y;

    *body = head;
}

void clearList(Cell* list)
{
    if (list->next == NULL)
        return;

    Cell* tmp = list->next;
    Cell* tmpnxt = tmp;

    list->next = NULL;

    while (tmp->next != NULL)
    {
        tmpnxt = tmp->next;
        free(tmp);
        tmp = tmpnxt;
    }
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
