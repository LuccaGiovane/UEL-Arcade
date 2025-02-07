#include "enemy.h"
#include "player.h"
#include "map.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <GL/glut.h>

// Funções auxiliares para operações com Vector3:

// Calcula o comprimento de um vetor
static inline float vectorLength(const Vector3 &v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Retorna um vetor normalizado (com comprimento 1)
static inline Vector3 normalize(const Vector3 &v) {
    float len = vectorLength(v);
    if (len == 0)
        return v;
    return Vector3(v.x / len, v.y / len, v.z / len);
}

// Calcula o produto escalar entre dois vetores
static inline float dotProduct(const Vector3 &a, const Vector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

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
        float len = std::sqrt(dir.x * dir.x + dir.z * dir.z);
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

// A função shoot() foi atualizada para utilizar as funções auxiliares acima.
// Agora ela mata um inimigo se ele estiver dentro de um range de 10 unidades e se estiver na mira (dentro de um cone definido pela tolerância angular).
void shoot() {
    const float SHOOT_RANGE = 10.0f;   // Range máximo para o tiro
    const float ANGLE_TOLERANCE = 0.2f;  // Tolerância angular em radianos

    for (auto& m : monsters) {
        if (!m.active) continue;
        // Calcula o vetor do jogador até o inimigo
        Vector3 toEnemy(m.position.x - playerPos.x, m.position.y - playerPos.y, m.position.z - playerPos.z);
        float distance = vectorLength(toEnemy);
        if (distance > SHOOT_RANGE)
            continue;  // Inimigo fora do alcance

        Vector3 toEnemyNorm = normalize(toEnemy);
        // Se o produto escalar entre a direção do jogador e a direção até o inimigo for maior que cos(ANGLE_TOLERANCE),
        // o inimigo está dentro do cone da mira.
        if (dotProduct(playerDir, toEnemyNorm) > std::cos(ANGLE_TOLERANCE)) {
            m.active = false; // Inimigo atingido
        }
    }
}
