#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

// Create a NULL-terminated string by reading the provided file
static char* readShaderSource(const char* shaderFile);
GLuint InitShader(const char* vShaderFile, const char* fShaderFile);