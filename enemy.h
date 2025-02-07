#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "vector3.h" // Inclui a definição de Vector3
#include "player.h"
#include "map.h"

struct Monster {
    Vector3 position;
    bool active;
    int type;       // Tipo de inimigo: 0 = básico, 1 = rápido, 2 = forte
    int health;     // Vida do inimigo
};

// Constantes para os tipos de inimigos
const int MONSTER_BASIC = 0;   // Inimigo básico
const int MONSTER_FAST = 1;    // Inimigo rápido
const int MONSTER_STRONG = 2;  // Inimigo forte

extern std::vector<Monster> monsters;

void drawMonsters();
void updateMonsters(int value);
void spawnMonster(int value);
void shoot();

#endif