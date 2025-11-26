#include "attack.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Resolução simples de batalha:
// atacante rola até 3 dados (máx tropas-1), defensor até 2 (máx tropas)
// comparamos maiores valores e perdedores perdem 1 tropa por confronto
static int roll_die(void) {
    return rand() % 6 + 1;
}

static int max(int a, int b) { return a > b ? a : b; }

int simple_battle(Territory *attacker, Territory *defender) {
    if (!attacker || !defender) return -1;
    if (attacker->troops < 2) return -1; // precisa deixar 1 tropa
    int attack_dice = max(1, attacker->troops - 1);
    if (attack_dice > 3) attack_dice = 3;
    int defend_dice = defender->troops;
    if (defend_dice > 2) defend_dice = 2;

    int a_rolls[3] = {0,0,0};
    int d_rolls[2] = {0,0};
    for (int i=0;i<attack_dice;i++) a_rolls[i] = roll_die();
    for (int i=0;i<defend_dice;i++) d_rolls[i] = roll_die();
    // ordenar decrescente (pequeno selection sort)
    for (int i=0;i<attack_dice-1;i++) for (int j=i+1;j<attack_dice;j++) if (a_rolls[j] > a_rolls[i]) { int tmp=a_rolls[i]; a_rolls[i]=a_rolls[j]; a_rolls[j]=tmp; }
    for (int i=0;i<defend_dice-1;i++) for (int j=i+1;j<defend_dice;j++) if (d_rolls[j] > d_rolls[i]) { int tmp=d_rolls[i]; d_rolls[i]=d_rolls[j]; d_rolls[j]=tmp; }

    int comparisons = attack_dice < defend_dice ? attack_dice : defend_dice;
    int attacker_losses = 0, defender_losses = 0;
    for (int i=0;i<comparisons;i++) {
        if (a_rolls[i] > d_rolls[i]) defender_losses++;
        else attacker_losses++;
    }
    attacker->troops -= attacker_losses;
    defender->troops -= defender_losses;
    return defender_losses - attacker_losses; // positivo = atacante ganhou mais
}

int perform_attack(Territory *attacker, Territory *defender, BattleResolver resolver) {
    if (!resolver) resolver = simple_battle;
    // realizar batalha até que atacante recue (troops<2) ou defensor perca todas tropas
    int rounds = 0;
    int last_result = 0;
    while (attacker->troops >= 2 && defender->troops > 0) {
        last_result = resolver(attacker, defender);
        rounds++;
        // pequena segurança para não loop infinito
        if (rounds > 1000) break;
    }
    // se defensor zerou, atacante pode mover 1 tropa para o território
    if (defender->troops <= 0) {
        defender->troops = 1;
        attacker->troops -= 1;
    }
    return last_result;
}
