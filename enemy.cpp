#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include "enemy.h"
#include "player.h"
#include "map.h"

// ========== VARIÁVEIS GLOBAIS E CONSTANTES ==========

// Vetor de inimigos
std::vector<Monster> monsters;

// Constantes para os tipos de inimigos
const int MONSTER_BASIC = 0;
const int MONSTER_FAST = 1;
const int MONSTER_STRONG = 2;

// Constantes para o tiro
static const float SHOOT_RANGE = 10.0f;
static const float ANGLE_TOLERANCE = 0.2f;

void drawMonsters() {
    // Habilita a iluminação para aplicar emissão de luz
    glEnable(GL_LIGHTING);

    for (auto &m : monsters) {
        if (!m.active) {
            continue;
        }

        // Salva o estado atual da matriz de transformação
        glPushMatrix();

        // Move a coordenada para onde o monstro está, 0.5 para ele não ficar no chão
        glTranslatef(m.position.x, 0.5f, m.position.z);

        // Define a cor de emissão dependendo do tipo de monstro
        GLfloat emissionColor[4];
        if (m.type == MONSTER_BASIC) {
            emissionColor[0] = 1.0f; // Vermelho
            emissionColor[1] = 0.0f;
            emissionColor[2] = 0.0f;
        } else if (m.type == MONSTER_FAST) {
            emissionColor[0] = 0.0f; // Verde
            emissionColor[1] = 1.0f;
            emissionColor[2] = 0.0f;
        } else if (m.type == MONSTER_STRONG) {
            emissionColor[0] = 0.0f; // Azul
            emissionColor[1] = 0.0f;
            emissionColor[2] = 1.0f;
        }
        emissionColor[3] = 1.0f; // Componente alfa

        // Define a emissão de luz
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissionColor);

        // Desenha a esfera
        glutSolidSphere(0.3, 10, 10);

        // Restaura a emissão padrão (nenhuma emissão)
        GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmission);

        // Restaura a matriz de transformação
        glPopMatrix();
    }

    // Desabilita a iluminação após desenhar os monstros
    glDisable(GL_LIGHTING);
}

void updateMonsters(int value) {

    if (gameOver) {
        glutTimerFunc(16, updateMonsters, 0);
        return;
    }
    
    for (auto &m : monsters) {
        if (!m.active){
            continue;
        }
            
        // Calcula a direção do inimigo até o jogador
        Vetor3D dir(playerPos.x - m.position.x, 0, playerPos.z - m.position.z);
        float len = std::sqrt(dir.x * dir.x + dir.z * dir.z);
        
        if (len > 0) {
            dir.x /= len;
            dir.z /= len;
        }

        float speed = 0.05f;
        if (m.type == MONSTER_FAST){
            speed = 0.1f;
        }else if (m.type == MONSTER_STRONG){
            speed = 0.02f;
        }
        
        m.position.x += dir.x * speed;
        m.position.z += dir.z * speed;
        
        if (checkCollision(m.position)) {
            m.position.x -= dir.x * speed;
            m.position.z -= dir.z * speed;
        }
        
        // Verifica colisão com o jogador
        float dx = m.position.x - playerPos.x;
        float dz = m.position.z - playerPos.z;
        float dist = std::sqrt(dx * dx + dz * dz);
        
        if (dist < 0.5f) {
            if (m.type == MONSTER_BASIC){
                playerHP -= 10;
            }else if (m.type == MONSTER_FAST){
                playerHP -= 20;
            }else if (m.type == MONSTER_STRONG){
                playerHP -= 30;
            } 

            m.active = false;
        }
    }
    glutTimerFunc(16, updateMonsters, 0);
}

void spawnMonster(int value) {
    Monster m;
    m.position = Vetor3D(rand() % ROOM_SIZE, 0, rand() % ROOM_SIZE);
    m.active = true;
    
    int type = rand() % 3;
    m.type = type;
    
    if (type == MONSTER_BASIC){
        m.health = 1;
    }else if (type == MONSTER_FAST){
        m.health = 2;
    }else if (type == MONSTER_STRONG){
        m.health = 4;
    }  
    
    monsters.push_back(m);
    glutTimerFunc(3000, spawnMonster, 0);
}

void shoot() {
    for (auto &m : monsters) {
        if (!m.active){
            continue;
        }
        // Calcula o vetor do jogador até o inimigo
        Vetor3D toEnemy(m.position.x - playerPos.x,
                        m.position.y - playerPos.y,
                        m.position.z - playerPos.z);
        
        float distance = vectorLength(toEnemy);
        if (distance > SHOOT_RANGE){
            continue;
        }

        
        Vetor3D normToEnemy = normalize(toEnemy);
        if (dotProduct(playerDir, normToEnemy) > std::cos(ANGLE_TOLERANCE)) {
            m.health--;
            if (m.health <= 0) {
                m.active = false;
                if (m.type == MONSTER_BASIC){
                    playerScore += 10;
                }else if (m.type == MONSTER_FAST){
                    playerScore += 25;
                }else if (m.type == MONSTER_STRONG){
                    playerScore += 50;
                }
            }
        }
    }
}
