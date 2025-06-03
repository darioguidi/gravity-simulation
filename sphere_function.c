#include "function.h"

void DrawPlanet(float x, float y, float radius, int reso)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= reso; i++) {
        float angle = 2.0f * 3.14159265358979323846 * ((float)i / reso);
        float xv = x + cosf(angle) * radius;
        float yv = y + sinf(angle) * radius;
        glVertex2f(xv, yv);
    }
    glEnd();
}