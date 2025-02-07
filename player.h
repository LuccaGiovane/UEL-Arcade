#ifndef PLAYER_H
#define PLAYER_H

#include <GL/freeglut.h>
#include "vector3.h" // Inclui a definição de Vector3

extern Vector3 playerPos;
extern Vector3 playerDir;
extern bool keyPressed[256];

void movePlayer();
void mouse(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void update(int value);

#endif