#include "enemy.h"
#include "player.h"
#include "map.h"
#include "vector3.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <GL/glut.h>

// Funções auxiliares para operações com Vector3:
static inline float vectorLength(const Vector3 &v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline Vector3 normalize(const Vector3 &v) {
    float len = vectorLength(v);
    if (len == 0)
        return v;
    return Vector3(v.x / len, v.y / len, v.z / len);
}

static inline float dotProduct(const Vector3 &a, const Vector3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

std::vector<Monster> monsters;

void drawMonsters() {
    for (auto& m : monsters) {
        if (!m.active) continue;

        glPushMatrix();
        glTranslatef(m.position.x, 0.5f, m.position.z);

        // Define a cor com base no tipo de inimigo
        if (m.type == MONSTER_BASIC) { // Básico
            glColor3f(1, 0, 0); // Vermelho
        } else if (m.type == MONSTER_FAST) { // Rápido
            glColor3f(0, 1, 0); // Verde
        } else if (m.type == MONSTER_STRONG) { // Forte
            glColor3f(0, 0, 1); // Azul
        }

        glutSolidSphere(0.3, 10, 10);
        glPopMatrix();
    }
}

void updateMonsters(int value) {
    for (auto& m : monsters) {
        if (!m.active) continue;

        // Atualiza a posição do monstro em direção ao jogador (já existente)
        Vector3 dir = Vector3(playerPos.x - m.position.x, 0, playerPos.z - m.position.z);
        float len = std::sqrt(dir.x * dir.x + dir.z * dir.z);
        if (len > 0) {
            dir.x /= len;
            dir.z /= len;
        }
        float speed = 0.05f; // Velocidade padrão
        if (m.type == MONSTER_FAST)
            speed = 0.1f;
        else if (m.type == MONSTER_STRONG)
            speed = 0.02f;
        m.position.x += dir.x * speed;
        m.position.z += dir.z * speed;

        // Verifica colisões com as paredes
        if (checkCollision(m.position)) {
            m.position.x -= dir.x * speed;
            m.position.z -= dir.z * speed;
        }

        // Verifica se o monstro colidiu com o jogador (defina um limiar apropriado, ex: 0.5f)
        float dx = m.position.x - playerPos.x;
        float dz = m.position.z - playerPos.z;
        float distToPlayer = std::sqrt(dx * dx + dz * dz);
        const float collisionThreshold = 0.5f;  // Ajuste conforme necessário
        if (distToPlayer < collisionThreshold) {
            // Aplica dano ao jogador conforme o tipo do monstro
            if (m.type == MONSTER_BASIC)
                playerHP -= 10;
            else if (m.type == MONSTER_FAST)
                playerHP -= 20;
            else if (m.type == MONSTER_STRONG)
                playerHP -= 30;

            m.active = false; // O monstro "consome" sua colisão
        }
    }
    glutTimerFunc(16, updateMonsters, 0);
}



void spawnMonster(int value) {
    Monster m;
    m.position = Vector3(rand() % ROOM_SIZE, 0, rand() % ROOM_SIZE);
    m.active = true;

    // Define o tipo de inimigo aleatoriamente
    int monsterType = rand() % 3; // Gera um tipo aleatório (0, 1 ou 2)
    m.type = monsterType;

    // Define a vida com base no tipo
    if (monsterType == MONSTER_BASIC) { // Básico
        m.health = 1;
    } else if (monsterType == MONSTER_FAST) { // Rápido
        m.health = 2;
    } else if (monsterType == MONSTER_STRONG) { // Forte
        m.health = 4;
    }

    monsters.push_back(m);
    glutTimerFunc(3000, spawnMonster, 0);
}

void shoot() {
    const float SHOOT_RANGE = 10.0f;      // Alcance máximo do tiro
    const float ANGLE_TOLERANCE = 0.2f;     // Tolerância angular (radianos)

    for (auto& m : monsters) {
        if (!m.active) continue;

        // Calcula o vetor do jogador até o monstro
        Vector3 toEnemy(m.position.x - playerPos.x, m.position.y - playerPos.y, m.position.z - playerPos.z);
        float distance = vectorLength(toEnemy);

        // Se estiver fora do alcance, ignora
        if (distance > SHOOT_RANGE)
            continue;

        Vector3 toEnemyNorm = normalize(toEnemy);

        // Verifica se o inimigo está dentro do cone da mira
        if (dotProduct(playerDir, toEnemyNorm) > std::cos(ANGLE_TOLERANCE)) {
            m.health--;  // Reduz a "vida" do monstro

            // Se o monstro morreu, incrementa a pontuação conforme o tipo
            if (m.health <= 0) {
                m.active = false;
                if (m.type == MONSTER_BASIC)
                    playerScore += 10;   // Básico: 10 pontos
                else if (m.type == MONSTER_FAST)
                    playerScore += 25;   // Rápido: 25 pontos
                else if (m.type == MONSTER_STRONG)
                    playerScore += 50;   // Forte: 50 pontos
            }
        }
    }
}