#include "player.h"
#include "map.h"
#include "enemy.h"
#include "vector3.h"
#include <cmath>
#include <GL/glut.h>

const float PLAYER_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;

Vector3 playerPos(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);
Vector3 playerDir(0, 0, -1);
bool keyPressed[256] = { false };

void movePlayer() {
    // Avança com a tecla W
    if (keyPressed['w'] || keyPressed['W']) {
        Vector3 newPos = playerPos;
        newPos.x += playerDir.x * PLAYER_SPEED;
        newPos.z += playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    // Retrocede com a tecla S
    if (keyPressed['s'] || keyPressed['S']) {
        Vector3 newPos = playerPos;
        newPos.x -= playerDir.x * PLAYER_SPEED;
        newPos.z -= playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    // Rotaciona para a esquerda com a tecla A
    if (keyPressed['a'] || keyPressed['A']) {
        float angle = -PLAYER_SPEED;  // Rotaciona negativamente
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
    // Rotaciona para a direita com a tecla D
    if (keyPressed['d'] || keyPressed['D']) {
        float angle = PLAYER_SPEED;  // Rotaciona positivamente
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
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

// Se a tecla pressionada for espaço, dispara; caso contrário, registra o estado para movimentação.
void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        shoot();  // Dispara utilizando o range definido em enemy.cpp
    } else {
        keyPressed[key] = true;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

void mouseButton(int button, int state, int x, int y) {
    // Se preferir, pode manter o disparo com o mouse; agora está desativado.
    // if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    //     shoot();
    // }
}

void update(int value) {
    movePlayer();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
