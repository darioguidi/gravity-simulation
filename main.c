#include "function.h"

int main(int argc, char* argv[]) 
{
    // Inizializza GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Errore nell'inizializzazione di GLFW\n");
        return -1;
    }

    // Imposta la versione di OpenGL (es: 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crea la finestra
    GLFWwindow* window = glfwCreateWindow(
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        "Gravity Simulation", 
        NULL, 
        NULL
    );
    
    if (!window) {
        fprintf(stderr, "Errore nella creazione della finestra\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Loop principale
    while (!glfwWindowShouldClose(window)) {
        // Gestione eventi
        glfwPollEvents();

        // Rendering (clear)
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Presenta la finestra
        glfwSwapBuffers(window);
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}