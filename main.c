#include "function.h"

int main(int /*argc*/, char* /*argv*/[])
{
    srand((unsigned int)time(NULL));

    int number_planets;

    printf("Quanti pianeti vuoi rappresentare?\n");
    scanf("%d", &number_planets);
    number_planets += 1;

    Planet *planets = malloc(number_planets * sizeof(Planet));
    createSystem(planets, number_planets);

    /*
    // Posizionamento casuale ma con margini per evitare sovrapposizioni iniziali
    for (int j = 1; j < number_planets; j++) {
        printf("Inserire il raggio del corpo:\n");
        scanf("%f", &radius);
        printf("Inserire la massa del corpo:\n");
        scanf("%f", &mass);

        float margin = radius * 3.0f;
        float x = margin + (float)(rand() % (SCREEN_WIDTH+10 - (int)(2 * margin)));
        float y = margin + (float)(rand() % (SCREEN_HEIGHT+10 - (int)(2 * margin)));

        float dx = x - SCREEN_OFFSET_X;
        float dy = y - SCREEN_OFFSET_Y;
        float r = sqrt(dx * dx + dy * dy);

        float v_tan = sqrt((G * MASS_SUN) / r);

        planets[j] = (Planet) {
            x, y, radius, mass,
            -dy / r * v_tan,   // componente x della velocità tangente
             dx / r * v_tan,   // componente y della velocità tangente
            resolution
        };
    }*/

    if (!glfwInit()) {
        fprintf(stderr, "Errore nell'inizializzazione di GLFW\n");
        return -1;
    }

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

    // Usa la dimensione reale del framebuffer per il viewport
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, fbWidth, 0, fbHeight, -1, 1);  // 🔧 Adatta la proiezione
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1, 1, 1);

        DrawPlanets(planets, number_planets);

        glfwSwapBuffers(window);
    }

    free(planets);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
