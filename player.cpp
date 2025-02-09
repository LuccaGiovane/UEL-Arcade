#include "player.h"
#include "map.h"
#include <GL/glut.h>
#include <cmath>

// Constantes para o jogador
const float PLAYER_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;

// Estado inicial do jogo
bool gameOver = false;
int playerHP = 100;
int playerScore = 0;
Vetor3D playerPos(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);  // ROOM_SIZE definido em map.cpp
Vetor3D playerDir(0, 0, -1);
bool keyPressed[256] = { false };

void movePlayer() {
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
    if (keyPressed['a'] || keyPressed['A']) {
        float angle = -PLAYER_SPEED;
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
    if (keyPressed['d'] || keyPressed['D']) {
        float angle = PLAYER_SPEED;
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
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
    if (key == ' ') {
        extern void shoot();
        shoot();
    } else {
        keyPressed[key] = true;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

void mouse(int x, int y) {
    static int lastX = 400;
    int deltaX = x - lastX;
    lastX = x;
    float angle = deltaX * MOUSE_SENSITIVITY;
    float oldDirX = playerDir.x;
    playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
    playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    glutWarpPointer(400, 300);
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
