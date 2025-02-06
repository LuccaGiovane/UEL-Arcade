#include "enemy.h"
#include "player.h"
#include "map.h"
#include <cmath>

std::vector<Monster> monsters;

void drawMonsters() {
    for (auto& m : monsters) {
        if (!m.active) continue;
        glPushMatrix();
        glTranslatef(m.position.x, 0.5f, m.position.z);
        glColor3f(1, 0, 0);
        glutSolidSphere(0.3, 10, 10);
        glPopMatrix();
    }
}

void updateMonsters(int value) {
    for (auto& m : monsters) {
        if (!m.active) continue;
        Vector3 dir = Vector3(playerPos.x - m.position.x, 0, playerPos.z - m.position.z);
        float len = sqrt(dir.x * dir.x + dir.z * dir.z);
        if (len > 0) {
            dir.x /= len;
            dir.z /= len;
            m.position.x += dir.x * 0.05f;
            m.position.z += dir.z * 0.05f;
        }
    }
    glutTimerFunc(16, updateMonsters, 0);
}

void spawnMonster(int value) {
    Monster m;
    m.position = Vector3(rand() % ROOM_SIZE, 0, rand() % ROOM_SIZE);
    m.active = true;
    monsters.push_back(m);
    glutTimerFunc(3000, spawnMonster, 0);
}

void shoot() {
    for (auto& m : monsters) {
        if (!m.active) continue;
        if (fabs(m.position.x - playerPos.x) < 0.5 &&
            fabs(m.position.z - playerPos.z) < 0.5) {
            m.active = false; // Desativa o monstro
        }
    }
}