#ifndef MENU_H
#define MENU_H

#include <cmath>
#include <GL/freeglut.h>
#include <cstring>

// O tipo Vetor3D representa um vetor ou coordenada em 3 dimensões (usado para posições e direções)
struct Vetor3D {
    float x, y, z;
    Vetor3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

// Funções utilitárias para Vetor3D
inline float vectorLength(const Vetor3D &v) {
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vetor3D normalize(const Vetor3D &v) {
    float len = vectorLength(v);
    return (len == 0) ? v : Vetor3D(v.x / len, v.y / len, v.z / len);
}

inline float dotProduct(const Vetor3D &a, const Vetor3D &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Funções do HUD e telas de menu
void drawCrosshair();
void drawHUD();
void drawGameOverScreen();

#endif
