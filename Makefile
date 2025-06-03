# Makefile universale per "Gravity Simulation"
# Compatibile con Linux e Windows, usando GLFW e OpenGL

# Compilatore
CC = gcc

# File sorgenti
SRCS = main.c sphere_function.c

# Header files
HEADERS = function.h

# Nome eseguibile
TARGET = gravity_simulation

# Flags di compilazione comuni
CFLAGS = -Wall -Wextra

# Flags per piattaforma specifica
# Usa "make PLATFORM=windows" oppure "make PLATFORM=linux"
ifeq ($(PLATFORM),windows)
    # Percorsi e librerie GLFW per Windows (modifica secondo la tua installazione)
    GLFW_INCLUDE = -IC:/glfw/include
    GLFW_LIB = -LC:/glfw/lib -lglfw3 -lopengl32 -lgdi32
    TARGET := $(TARGET).exe
else
    # Default Linux: usa pkg-config per glfw3 e OpenGL
    GLFW_INCLUDE = $(shell pkg-config --cflags glfw3)
    GLFW_LIB = $(shell pkg-config --static --libs glfw3) -lGL
endif

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(GLFW_INCLUDE) $(SRCS) -o $(TARGET) $(GLFW_LIB)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
