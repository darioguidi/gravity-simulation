CC = gcc
SRCS = main.c sphere_function.c
HEADERS = function.h
TARGET = gravity_simulation
CFLAGS = -Wall -Wextra

ifeq ($(OS),Windows_NT)
  PLATFORM ?= windows
else
  PLATFORM ?= linux
endif

ifeq ($(PLATFORM),windows)
    GLFW_INCLUDE = -IC:/glfw/include
    GLFW_LIB = -LC:/glfw/lib -lglfw3 -lopengl32 -lgdi32
    TARGET := $(TARGET).exe
else
    GLFW_INCLUDE = $(shell pkg-config --cflags glfw3)
    GLFW_LIB = $(shell pkg-config --static --libs glfw3) -lGL
endif

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(GLFW_INCLUDE) $(SRCS) -o $(TARGET) $(GLFW_LIB)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
