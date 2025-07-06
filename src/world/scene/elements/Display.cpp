#include "Display.h"

render::Display::Display(std::shared_ptr<tex::Texture> texture) : texture(texture) {}

void render::Display::render(RenderParam &param) {
    glUseProgram(0);

    texture->bind();

    float aspect = 1;

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(-aspect, -1);
    glTexCoord2f(1, 0); glVertex2f(aspect, -1);
    glTexCoord2f(1, 1); glVertex2f(aspect,  1);
    glTexCoord2f(0, 1); glVertex2f(-aspect,  1);
    glEnd();

    texture->unbind();
}