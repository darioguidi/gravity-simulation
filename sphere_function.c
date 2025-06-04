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

        if(p->x<0 || p->x > SCREEN_WIDTH){
            p->velocity_x *= -0.95f;
        }

        if(p->y<0 || p->y > SCREEN_HEIGHT){
            p->velocity_y *= -0.95f;
        }

        for (int j = 0; j < number_planets; j++) {
            Planet *pv = &planets[j];

            if (i != j) {
                float dx = p->x - pv->x;
                float dy = p->y - pv->y;

                float distance_squared = (dx*dx) + (dy*dy) + EPS;
                float distance = sqrt(distance_squared);

                float Gforce = (G * p->mass * pv->mass)/distance_squared;

                float forceX = Gforce * (dx/distance);
                float forceY = Gforce * (dy/distance);

                p->velocity_x -= forceX / p->mass;
                p->velocity_y -= forceY / p->mass;
            }
        }
    }
}

