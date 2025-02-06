#ifndef PLAYER_H
#define PLAYER_H

#include <GL/freeglut.h>

struct Vector3 {
    float x, y, z;
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

extern Vector3 playerPos;
extern Vector3 playerDir;
extern bool keyPressed[256];

void movePlayer();
void mouse(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y); // Declaração adicionada
void update(int value); // Declaração adicionada

#endif