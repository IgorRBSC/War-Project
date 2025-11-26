#include "mission.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Mission **create_missions(int n) {
    Mission **arr = (Mission**)calloc((size_t)n, sizeof(Mission*));
    return arr;
}

void destroy_missions(Mission **missions, int n) {
    if (!missions) return;
    for (int i=0;i<n;i++) {
        if (missions[i]) {
            free(missions[i]->color);
            free(missions[i]->description);
            free(missions[i]);
        }
    }
    free(missions);
}

Mission *create_mission_occupy(int n) {
    Mission *m = (Mission*)malloc(sizeof(Mission));
    m->type = OCCUPY_N;
    m->param = n;
    m->color = NULL;
    m->description = strdup("Ocupar N territórios");
    return m;
}

Mission *create_mission_eliminate_color(const char *color) {
    Mission *m = (Mission*)malloc(sizeof(Mission));
    m->type = ELIMINATE_COLOR;
    m->param = 0;
    m->color = strdup(color ? color : "");
    size_t len = 64 + strlen(m->color);
    char *desc = (char*)malloc(len);
    snprintf(desc, len, "Eliminar todas as tropas da cor %s", m->color);
    m->description = desc;
    return m;
}

Mission *create_mission_total_troops(int troops) {
    Mission *m = (Mission*)malloc(sizeof(Mission));
    m->type = TOTAL_TROOPS;
    m->param = troops;
    m->color = NULL;
    m->description = strdup("Ter um total de tropas alocado");
    return m;
}

void print_mission(const Mission *m) {
    if (!m) return;
    printf("Missão: %s\n", m->description);
}

int check_mission(const Mission *m, Territory **territories, int tcount) {
    if (!m) return 0;
    if (m->type == OCCUPY_N) {
        int occupied = 0;
        for (int i=0;i<tcount;i++) if (territories[i] && territories[i]->troops > 0) occupied++;
        return occupied >= m->param;
    } else if (m->type == ELIMINATE_COLOR) {
        for (int i=0;i<tcount;i++) {
            if (territories[i] && territories[i]->color && strcmp(territories[i]->color, m->color) == 0) {
                if (territories[i]->troops > 0) return 0; // ainda existe tropas dessa cor
            }
        }
        return 1;
    } else if (m->type == TOTAL_TROOPS) {
        int total = 0;
        for (int i=0;i<tcount;i++) if (territories[i]) total += territories[i]->troops;
        return total >= m->param;
    }
    return 0;
}
