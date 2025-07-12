#include "PerspectiveWindowMatrix.h"

mtrx::PerspectiveWindowMatrix::PerspectiveWindowMatrix(float fov, float aspect, float near, float far) 
	: mtrx::PerspectiveMatrix(fov, aspect, near, far){}

void mtrx::PerspectiveWindowMatrix::onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) {
    if (event.getHeight() == 0) {
	return;
    }

    aspect = static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight());

    this->mat = mtrx::PerspectiveMatrix::createMatrix(fov, aspect, near, far);
}