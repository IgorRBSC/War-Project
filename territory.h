#ifndef TERRITORY_H
#define TERRITORY_H
#include <stdbool.h>

typedef struct Territory {
    char *name;
    char *color;
    int troops;
    int id; // id único
} Territory;

Territory *create_territory(const char *name, const char *color, int troops, int id);
void destroy_territory(Territory *t);
void print_territory(const Territory *t);

#endif
