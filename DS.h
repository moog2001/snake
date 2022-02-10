#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>



struct Grid
{
    float x;
    float y;
};
typedef struct Grid Grid;
struct Elm {
        Grid x;
        struct Elm *next;
};
typedef struct Elm Elm;

// List
struct List {
        Elm *head;
        Elm *tail;
        int len;
};
typedef struct List List;

void l_push_back(List *, Grid);
void l_push_front(List *, Grid);
void l_pop_front(List *);
void l_pop_back(List *);
void l_print(List *);
Elm *l_search(List *, Grid);
Elm *l_search_noHead(List *, Grid);

#endif
