#include "MatrixUtils.h"

void mtrx::uniform(GLuint program, const char* name, glm::mat4 matrix) {
    int un_loc = glGetUniformLocation(program, name);

    glUniformMatrix4fv(un_loc, 1, GL_FALSE, glm::value_ptr(matrix));
}