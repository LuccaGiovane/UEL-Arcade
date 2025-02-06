#ifndef MAP_H
#define MAP_H

#include "player.h"

extern const int ROOM_SIZE;

void drawRoom();
bool checkCollision(Vector3 pos);

#endif