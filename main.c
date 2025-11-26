#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "territory.h"
#include "attack.h"
#include "mission.h"
#include "utils.h"

// Projeto usa arrays dinâmicos de ponteiros para Territories e Missions.

void print_all(Territory **arr, int n) {
    printf("--- Territórios cadastrados ---\n");
    for (int i=0;i<n;i++) {
        if (arr[i]) print_territory(arr[i]);
        else printf("[vazio] slot %d\n", i);
    }
    printf("-------------------------------\n");
}

int main(void) {
    srand((unsigned)time(NULL));
    int capacity = 4;
    int count = 0;
    Territory **territories = (Territory**)calloc((size_t)capacity, sizeof(Territory*));
    int next_id = 1;

    int missions_capacity = 4;
    int missions_count = 0;
    Mission **missions = create_missions(missions_capacity);

    while (1) {
        printf("\nMenu:\n1) Cadastrar território\n2) Listar territórios\n3) Atacar\n4) Criar missões demo\n5) Verificar missões\n6) Remover território\n7) Sair\Escolha: ");
        int opt = read_int("");
        if (opt == 1) {
            char *name = read_line("Nome do território: ");
            char *color = read_line("Cor (jogador) do território: ");
            int troops = read_int("Tropas iniciais: ");
            if (count >= capacity) {
                capacity *= 2;
                territories = (Territory**)realloc(territories, (size_t)capacity * sizeof(Territory*));
                for (int i=count;i<capacity;i++) territories[i] = NULL;
            }
            Territory *t = create_territory(name, color, troops, next_id++);
            free(name); free(color);
            territories[count++] = t;
            printf("Território criado.\n");
        } else if (opt == 2) {
            print_all(territories, count);
        } else if (opt == 3) {
            print_all(territories, count);
            int a = read_int("Escolha ID do atacante (número do slot, exemplo 0): ");
            int d = read_int("Escolha ID do defensor (número do slot, exemplo 1): ");
            if (a < 0 || a >= count || d < 0 || d >= count || !territories[a] || !territories[d] || a==d) {
                printf("Seleção inválida.\n");
            } else {
                printf("Iniciando ataque entre %s e %s...\n", territories[a]->name, territories[d]->name);
                int res = perform_attack(territories[a], territories[d], NULL); // usa simple_battle por padrão
                printf("Resultado do conflito: %d (positivo favorece atacante)\n", res);
                if (territories[d]->troops <= 0) {
                    printf("Território conquistado! Movendo 1 tropa de %s para %s.\n", territories[a]->name, territories[d]->name);
                }
            }
        } else if (opt == 4) {
            // criar missões demo
            if (missions_count + 3 > missions_capacity) {
                missions_capacity *= 2;
                missions = (Mission**)realloc(missions, (size_t)missions_capacity * sizeof(Mission*));
                for (int i=missions_count;i<missions_capacity;i++) missions[i] = NULL;
            }
            missions[missions_count++] = create_mission_occupy(3);
            missions[missions_count++] = create_mission_eliminate_color("Red");
            missions[missions_count++] = create_mission_total_troops(10);
            printf("Missões demo criadas (3).\n");
        } else if (opt == 5) {
            if (missions_count == 0) { printf("Nenhuma missão cadastrada.\n"); continue; }
            for (int i=0;i<missions_count;i++) {
                if (!missions[i]) continue;
                print_mission(missions[i]);
                int ok = check_mission(missions[i], territories, count);
                printf("Concluída? %s\n", ok ? "SIM" : "NÃO");
            }
        } else if (opt == 6) {
            print_all(territories, count);
            int idx = read_int("Escolha slot para remover (ex: 0): ");
            if (idx < 0 || idx >= count || !territories[idx]) {
                printf("Índice inválido.\n");
            } else {
                destroy_territory(territories[idx]);
                territories[idx] = NULL;
                printf("Removido.\n");
            }
        } else if (opt == 7) {
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }

    // cleanup
    for (int i=0;i<count;i++) if (territories[i]) destroy_territory(territories[i]);
    free(territories);
    destroy_missions(missions, missions_capacity);
    printf("Encerrando...\n");
    return 0;
}
