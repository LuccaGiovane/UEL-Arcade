#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include "enemy.h"
#include "player.h"
#include "map.h"


// Vetor de inimigos
std::vector<Monster> monsters;

// Constantes para os tipos de inimigos
const int MONSTER_BASIC = 0;
const int MONSTER_FAST = 1;
const int MONSTER_STRONG = 2;

// Constantes para o tiro
static const float SHOOT_RANGE = 10.0f;
static const float ANGLE_TOLERANCE = 0.1f;


/*
    Função drawMonsters:
    - Percorre a lista de inimigos e, para cada inimigo ativo, desenha-o na tela.
    - Cada inimigo é desenhado como uma esfera, com cor definida pelo seu tipo:
      vermelho para básico, verde para rápido e azul para forte.
*/
void drawMonsters() {

    for (auto &m : monsters) {
        
        if (!m.active) continue;
            
        glPushMatrix();

        // move para a posição do monstro 0.5 na altura para que não ficar no chã
        glTranslatef(m.position.x, 0.5f, m.position.z);
        
        // define a cor dependendo do monstro respectivamente: vermelho, verde, azul
        if (m.type == MONSTER_BASIC)
            glColor3f(1, 0, 0);
        else if (m.type == MONSTER_FAST)
            glColor3f(0, 1, 0);
        else if (m.type == MONSTER_STRONG)
            glColor3f(0, 0, 1);
        
        // desenha a esfera
        glutSolidSphere(0.3, 10, 10);

        
        glPopMatrix();
    }
}


/*
    Função updateMonsters:
    - Atualiza a posição e o comportamento dos inimigos periodicamente.
    - Cada inimigo ativo move-se na direção do jogador.
    - Se ocorrer uma colisão com o ambiente (checkCollision), o movimento é revertido.
    - Se um inimigo colidir com o jogador (distância < 0.5) ele da o dano e desativa
*/
void updateMonsters(int value) {

    if (gameOver) {
        glutTimerFunc(16, updateMonsters, 0);
        return;
    }
    
    for (auto &m : monsters) {
        if (!m.active) continue;
        
            
        // Calcula a direção do inimigo até o jogador
        Vetor3D dir(playerPos.x - m.position.x, 0, playerPos.z - m.position.z);
        float len = std::sqrt(dir.x * dir.x + dir.z * dir.z);
        
        if (len > 0) {
            dir.x /= len;
            dir.z /= len;
        }

        float speed;
        if (m.type == MONSTER_FAST) speed = 0.1f;
        else if (m.type == MONSTER_STRONG) speed = 0.02f;
        else speed = 0.05f;
        
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
            if (m.type == MONSTER_BASIC)       playerHP -= 20;
            else if (m.type == MONSTER_FAST)   playerHP -= 10;
            else if (m.type == MONSTER_STRONG) playerHP -= 40;
            
            m.active = false;
        }
    }
    glutTimerFunc(16, updateMonsters, 0);
}


/*
    Função spawnMonster:
    - Cria um novo inimigo em uma posição aleatória dentro da sala.
    - Define seu tipo aleatoriamente (básico, rápido ou forte) e ajusta sua vida de acordo.
    - Adiciona o novo inimigo ao vetor global de inimigos.
    - Reagenda a criação de inimigos a cada 3000 ms.
*/
void spawnMonster(int value) {
    Monster m;
    m.position = Vetor3D(rand() % ROOM_SIZE, 0, rand() % ROOM_SIZE);
    m.active = true;
    
    int type = rand() % 3;
    m.type = type;

    if (type == MONSTER_BASIC)       m.health = 2; 
    else if (type == MONSTER_FAST)   m.health = 1;
    else if (type == MONSTER_STRONG) m.health = 4;
      
    monsters.push_back(m);
    
    glutTimerFunc(3000, spawnMonster, 0);
}


/*
    Função shoot:
    - Processa o disparo do jogador.
    - Percorre todos os inimigos ativos e, para cada um:
        - Calcula a distância até o jogador.
        - Verifica se o inimigo está dentro do alcance do tiro (SHOOT_RANGE).
        - Usa o produto escalar (dotProduct) para determinar se o inimigo está alinhado com a mira do jogador.
    - Se o inimigo estiver no campo de tiro, diminui sua vida.
    - Se a vida do inimigo chegar a zero ou menos, o inimigo é desativado e a pontuação do jogador é incrementada conforme o tipo.
*/
void shoot() {
    for (auto &m : monsters) {
        if (!m.active) continue;

        // Calcula o vetor do jogador até o inimigo
        Vetor3D toEnemy(m.position.x - playerPos.x,
                        m.position.y - playerPos.y,
                        m.position.z - playerPos.z);
        
        // se o tiro nao der range do monstro so ignora
        float distance = vectorLength(toEnemy);
        if (distance > SHOOT_RANGE) continue;
        

        Vetor3D normToEnemy = normalize(toEnemy);
        if (dotProduct(playerDir, normToEnemy) > std::cos(ANGLE_TOLERANCE)) {
            m.health--;
            if (m.health <= 0) {
                m.active = false;

                if (m.type == MONSTER_BASIC)       playerScore += 10;
                else if (m.type == MONSTER_FAST)   playerScore += 25;
                else if (m.type == MONSTER_STRONG) playerScore += 50;
                
            }
        }
    }
}
