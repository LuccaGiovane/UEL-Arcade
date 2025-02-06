#include "player.h"
#include "map.h"
#include "enemy.h"
#include <cmath>

const float PLAYER_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;

Vector3 playerPos(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);
Vector3 playerDir(0, 0, -1);
bool keyPressed[256] = {false};

void movePlayer() {
    if (keyPressed['w']) {
        Vector3 newPos = playerPos;
        newPos.x += playerDir.x * PLAYER_SPEED;
        newPos.z += playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos)) playerPos = newPos;
    }
    if (keyPressed['s']) {
        Vector3 newPos = playerPos;
        newPos.x -= playerDir.x * PLAYER_SPEED;
        newPos.z -= playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos)) playerPos = newPos;
    }
    if (keyPressed['a']) {
        float angle = -PLAYER_SPEED;
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
    if (keyPressed['d']) {
        float angle = PLAYER_SPEED;
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

void keyboard(unsigned char key, int x, int y) {
    keyPressed[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shoot();
    }
}

void update(int value) {
    movePlayer();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}