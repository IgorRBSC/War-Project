#ifndef MISSION_H
#define MISSION_H
#include "territory.h"

typedef enum { OCCUPY_N, ELIMINATE_COLOR, TOTAL_TROOPS } MissionType;

typedef struct Mission {
    MissionType type;
    int param; // significado depende do tipo (N territories, or troops)
    char *color; // used if ELIMINATE_COLOR
    char *description;
} Mission;

Mission **create_missions(int n);
void destroy_missions(Mission **missions, int n);
Mission *create_mission_occupy(int n);
Mission *create_mission_eliminate_color(const char *color);
Mission *create_mission_total_troops(int troops);
void print_mission(const Mission *m);
int check_mission(const Mission *m, Territory **territories, int tcount);

#endif
