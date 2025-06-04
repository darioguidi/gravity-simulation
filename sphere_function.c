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
    for (int i = 0; i < number_planets; i++) {
        Planet *p = &planets[i];
        p->x += p->velocity_x;
        p->y += p->velocity_y;

    if (p->x - p->radius < 0) {
        p->x = p->radius;
        p->velocity_x *= -0.95f;
    }
    if (p->x + p->radius > SCREEN_WIDTH) {
        p->x = SCREEN_WIDTH - p->radius;
        p->velocity_x *= -0.95f;
    }
    if (p->y - p->radius < 0) {
        p->y = p->radius;
        p->velocity_y *= -0.95f;
    }
    if (p->y + p->radius > SCREEN_HEIGHT) {
        p->y = SCREEN_HEIGHT - p->radius;
        p->velocity_y *= -0.95f;
    }
    }

    for (int i = 0; i < number_planets; i++) {
        Planet *p1 = &planets[i];
        for (int j = i + 1; j < number_planets; j++) {
            Planet *p2 = &planets[j];

            float dx = p1->x - p2->x;
            float dy = p1->y - p2->y;
            float dist_sq = dx*dx + dy*dy + EPS;
            float dist = sqrt(dist_sq);

            float Gforce = (G * p1->mass * p2->mass) / dist_sq;
            float forceX = Gforce * (dx / dist);
            float forceY = Gforce * (dy / dist);

            p1->velocity_x -= forceX / p1->mass;
            p1->velocity_y -= forceY / p1->mass;
            p2->velocity_x += forceX / p2->mass;
            p2->velocity_y += forceY / p2->mass;

            if (dist <= p1->radius + p2->radius) {
                float nx = dx / dist;
                float ny = dy / dist;

                float p1v = p1->velocity_x * nx + p1->velocity_y * ny;
                float p2v = p2->velocity_x * nx + p2->velocity_y * ny;

                float m1 = p1->mass;
                float m2 = p2->mass;
                float v1_after = (p1v * (m1 - m2) + 2 * m2 * p2v) / (m1 + m2);
                float v2_after = (p2v * (m2 - m1) + 2 * m1 * p1v) / (m1 + m2);

                p1->velocity_x += (v1_after - p1v) * nx;
                p1->velocity_y += (v1_after - p1v) * ny;
                p2->velocity_x += (v2_after - p2v) * nx;
                p2->velocity_y += (v2_after - p2v) * ny;

                float overlap = 0.5f * (p1->radius + p2->radius - dist);
                p1->x += nx * overlap;
                p1->y += ny * overlap;
                p2->x -= nx * overlap;
                p2->y -= ny * overlap;
            }
        }
    }

    for (int i = 0; i < number_planets; i++) {
        Planet *p = &planets[i];
        DrawPlanet(p->x, p->y, p->radius, p->reso);
    }
}


void set_orbital_velocity(Planet *central, Planet *orbiting) 
{
    float dx = orbiting->x - central->x;
    float dy = orbiting->y - central->y;
    float distance = sqrt(dx*dx + dy*dy) + 1e-6f; // evita divisione per zero

    float v = sqrt(G * central->mass / distance);

    float vx = -dy / distance * v; // velocità tangenziale (perpendicolare a r)
    float vy = dx / distance * v;

    orbiting->velocity_x = vx;
    orbiting->velocity_y = vy;
}