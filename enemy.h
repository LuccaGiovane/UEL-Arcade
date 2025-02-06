#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "player.h"

struct Monster {
    Vector3 position;
    bool active;
};

extern std::vector<Monster> monsters;

void drawMonsters();
void updateMonsters(int value);
void spawnMonster(int value);
void shoot(); // Declaração adicionada

#endif