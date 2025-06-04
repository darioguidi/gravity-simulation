#include "function.h"

int main(int /*argc*/, char* /*argv*/[])
{
    int number_planets, resolution, d=0;
    float radius, mass;

    printf("Quanti pianeti vuo irappresentare?\n");
    scanf("%d", &number_planets);

    Planet *planets = malloc(number_planets*sizeof(Planet));

    for(int j=0;j<number_planets;j++){
        printf("Inserire il raggio del corpo:\n");
        scanf("%f", &radius);
        printf("Inserire la massa del corpo:\n");
        scanf("%f", &mass);
        printf("Inserire la risoluzione del corpo:\n");
        scanf("%d", &resolution);
        *(planets+j) = (Planet) {SCREEN_OFFSET_X+d, SCREEN_OFFSET_Y+d, radius, mass, 0.0f, 0.0f, resolution};
        d+=100;
    }

    if (!glfwInit()) {
        fprintf(stderr, "Errore nell'inizializzazione di GLFW\n");
        return -1;
    }

    // OpenGL 2.1 compatibility profile (immediate mode consentito)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gravity Simulation", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Errore nella creazione della finestra\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Imposta viewport e proiezione ortografica per coordinate 2D
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Clear prima del disegno
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0f, 1.0f, 1.0f);  // colore bianco
        
        DrawPlanets(planets, number_planets);

        glfwSwapBuffers(window);
    }

    free(planets);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
