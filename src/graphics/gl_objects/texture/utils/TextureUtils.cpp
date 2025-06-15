#include "TextureUtils.h"

void tex::uniformInteger(int program, const char* name, int value) {
    int un_loc = glGetUniformLocation(program, name);

    glUniform1i(un_loc, value);
}