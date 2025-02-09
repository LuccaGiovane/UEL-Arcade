#include "player.h"
#include "map.h"
#include "enemy.h"
#include <GL/glut.h>
#include <cmath>

// Constantes para o jogador
const float PLAYER_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;

static float yaw = 0.0f;
static float pitch = 0.0f;


// Estado inicial do jogo
bool gameOver = false;
int playerHP = 100;
int playerScore = 0;
Vetor3D playerPos(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);  // ROOM_SIZE definido em map.cpp
Vetor3D playerDir(0, 0, -1);
bool keyPressed[256] = { false };

void movePlayer() {
    // Movimento para frente (W) e para trás (S) já existentes:
    if (keyPressed['w'] || keyPressed['W']) {
        Vetor3D newPos = playerPos;
        newPos.x += playerDir.x * PLAYER_SPEED;
        newPos.z += playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    if (keyPressed['s'] || keyPressed['S']) {
        Vetor3D newPos = playerPos;
        newPos.x -= playerDir.x * PLAYER_SPEED;
        newPos.z -= playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    
    // Movimento lateral para a direita (D)
    if (keyPressed['d'] || keyPressed['D']) {
        // Vetor perpendicular à direção do jogador: para a esquerda, (-playerDir.z, 0, playerDir.x)
        Vetor3D left(-playerDir.z, 0, playerDir.x);
        // Normaliza o vetor left
        float len = std::sqrt(left.x * left.x + left.z * left.z);
        left.x /= len;
        left.z /= len;
        Vetor3D newPos = playerPos;
        newPos.x += left.x * PLAYER_SPEED;
        newPos.z += left.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    
    // Movimento lateral para a esquerda (A)
    if (keyPressed['a'] || keyPressed['A']) {
        // Vetor perpendicular para a direita: (playerDir.z, 0, -playerDir.x)
        Vetor3D right(playerDir.z, 0, -playerDir.x);
        float len = std::sqrt(right.x * right.x + right.z * right.z);
        right.x /= len;
        right.z /= len;
        Vetor3D newPos = playerPos;
        newPos.x += right.x * PLAYER_SPEED;
        newPos.z += right.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
}



void keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        // Em game over, o ENTER reinicia e a tecla Q sai do jogo
        if (key == 13) { // Código ASCII para ENTER
            extern void resetGame();
            resetGame();
        } else if (key == 'q' || key == 'Q') {
            exit(0);
        }
        return;
    }
    
    keyPressed[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

void mouseClick(int button, int state, int x, int y) {
    if (!gameOver && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shoot();
    }
}


void mouse(int x, int y) {
    static int lastX = 400, lastY = 300; // Inicializado na posição central (400,300)
    int deltaX = x - lastX;
    int deltaY = y - lastY;
    lastX = x;
    lastY = y;
    
    float sensitivity = MOUSE_SENSITIVITY;
    yaw   += deltaX * sensitivity;
    pitch -= deltaY * sensitivity;  // Inverte para que mover o mouse para cima aumente o pitch
    
    // Limita o pitch para evitar rotação exagerada (ex: entre -90° e 90°)
    const float maxPitch = 1.57f; // aproximadamente 90 graus em radianos
    if (pitch > maxPitch)
        pitch = maxPitch;
    if (pitch < -maxPitch)
        pitch = -maxPitch;
    
    // Recalcula o vetor direção do jogador usando os ângulos yaw e pitch:
    playerDir.x = sin(yaw) * cos(pitch);
    playerDir.y = sin(pitch);
    playerDir.z = -cos(yaw) * cos(pitch);
    
}


void update(int value) {
    if (!gameOver) {
        movePlayer();
        if (playerHP <= 0)
            gameOver = true;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
