#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include "menu.h"    // Para a definição de Vetor e funções de vetor
#include "player.h"  // Para acesso às variáveis do jogador (playerPos, playerHP, etc.)
#include "map.h"     // Para ROOM_SIZE e checkCollision

// Estrutura que representa um inimigo (monstro)
struct Monster {
    Vetor3D position;
    bool active;
    int type;       // 0 = básico, 1 = rápido, 2 = forte
    int health;
};

// Constantes para os tipos de inimigos
extern const int MONSTER_BASIC;
extern const int MONSTER_FAST;
extern const int MONSTER_STRONG;

// Vetor global de inimigos
extern std::vector<Monster> monsters;

// Funções relacionadas aos inimigos
void drawMonsters();
void updateMonsters(int value);
void spawnMonster(int value);
void shoot();

#endif
