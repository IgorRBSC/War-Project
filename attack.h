#ifndef ATTACK_H
#define ATTACK_H
#include "territory.h"

typedef int (*BattleResolver)(Territory *attacker, Territory *defender);

int simple_battle(Territory *attacker, Territory *defender);
int perform_attack(Territory *attacker, Territory *defender, BattleResolver resolver);

#endif
