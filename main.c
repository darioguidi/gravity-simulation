#include "function.h"

int main(int /*argc*/, char* /*argv*/[])
{
    srand((unsigned int)time(NULL));

    int number_planets, resolution=20;
    float radius, mass;

    printf("Quanti pianeti vuoi rappresentare?\n");
    scanf("%d", &number_planets);

    Planet *planets = malloc(number_planets*sizeof(Planet));

    // Posizionamento casuale ma con margini per evitare sovrapposizioni iniziali
    for(int j=0;j<number_planets;j++){
        printf("Inserire il raggio del corpo:\n");
        scanf("%f", &radius);
        printf("Inserire la massa del corpo:\n");
        scanf("%f", &mass);

        float margin = radius * 3.0f; // margine per non sovrapporre i pianeti alle estremità
        float x = margin + (float)(rand() % (SCREEN_WIDTH - (int)(2*margin)));
        float y = margin + (float)(rand() % (SCREEN_HEIGHT - (int)(2*margin)));

        *(planets+j) = (Planet) {x, y, radius, mass, 0.0f, 0.0f, resolution};
    }

    set_orbital_velocity(planets, number_planets);

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

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1, 1, 1);

        DrawPlanets(planets, number_planets);  // funzione modificata con DT

        glfwSwapBuffers(window);
    }

    free(planets);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
} 