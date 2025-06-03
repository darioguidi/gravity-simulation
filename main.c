#include "function.h"

int main(int /*argc*/, char* /*argv*/[])
{
    float raggio;
    int reso = 40;

    printf("Inserire il raggio del corpo:\n");
    scanf("%f", &raggio);

    float position[2] = {SCREEN_OFFSET_X, SCREEN_OFFSET_Y};
    float velocity[2] = {0.0f,0.0f};

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
        
        DrawPlanet(position[0], position[1], raggio, reso);

        position[0] += velocity[0];
        position[1] += velocity[1];
        velocity[1] += -9.81/20.0f;

        if (position[1]<0 || position[1]>SCREEN_HEIGHT){
            velocity[1] *= -0.95;
        }
        if (position[0]<0 || position[0]>SCREEN_WIDTH){
            velocity[1] *= -0.95;
        }

        printf("Velocità verticale: %.2f\n", velocity[1]);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
