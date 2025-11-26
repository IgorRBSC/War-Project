#include "territory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Territory *create_territory(const char *name, const char *color, int troops, int id) {
    Territory *t = (Territory*)malloc(sizeof(Territory));
    if (!t) return NULL;
    t->name = strdup(name ? name : "");
    t->color = strdup(color ? color : "");
    t->troops = troops;
    t->id = id;
    return t;
}

void destroy_territory(Territory *t) {
    if (!t) return;
    free(t->name);
    free(t->color);
    free(t);
}

void print_territory(const Territory *t) {
    if (!t) return;
    printf("[ID:%d] %s (Cor: %s) - Tropas: %d\n", t->id, t->name, t->color, t->troops);
}
