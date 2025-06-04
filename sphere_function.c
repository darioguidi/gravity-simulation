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

void DrawPlanets(Planet *planets, int number_planets)
{
    for(int i=0;i<number_planets;i++){
        Planet *p = &planets[i];

        DrawPlanet(p->x, p->y, p->radius, p->reso);

        p->x += p->velocity_x;
        p->y += p->velocity_y;

        p->velocity_y -= 0.05f;

        if(p->x<0 || p->x > SCREEN_WIDTH){
            p->velocity_x *= -0.95f;
        }

        if(p->y<0 || p->y > SCREEN_HEIGHT){
            p->velocity_y *= -0.95f;
        }
/*
    for (int i = 0; i < number_planets; i++) {
        for (int j = 0; j < number_planets; j++) {
            if (i != j) {
                float Gforce = (G * p->mass * (planets+j)->mass)/(p->radius*p->radius);
            }
        }
    }*/


}
}

