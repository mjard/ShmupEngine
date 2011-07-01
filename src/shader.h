#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <GL/glfw.h>

char * read_file(const char *f);
GLuint compile_shaders(const char *vsh_src, const char *fsh_src);
GLuint load_shaders(const char *vsh_file, const char *fsh_file);

#endif