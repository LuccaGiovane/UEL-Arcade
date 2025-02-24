#ifndef MAP_H
#define MAP_H

#include "menu.h"  // Para usar Vetor3D

extern const int ROOM_SIZE;

void drawRoom();
bool checkCollision(const Vetor3D &pos);
void setupLighting();

#endif
