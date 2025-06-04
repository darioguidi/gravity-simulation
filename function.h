#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SCREEN_OFFSET_X (SCREEN_WIDTH / 2)
#define SCREEN_OFFSET_Y (SCREEN_HEIGHT / 2)
#define G 6.67430e-11

typedef struct {
    float x;
    float y;
    float radius;
    float mass;
    float velocity_x;
    float velocity_y;
    int reso;
} Planet;

#endif

void DrawPlanet(float x, float y, float radius, int reso);
void DrawPlanets(Planet *planets, int number_planets);
