#include "matrix/transform/TransformMatrix.h"

namespace mtrx {

class ViewMatrix : public TransformMatrix {
public:
    ViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);//mode = 1

    ~ViewMatrix() = default;

    virtual glm::mat4 getMatrix() const override;

    virtual void rotate(glm::vec3 rotation) override;

    virtual void setRotation(glm::vec3 rotation) override;

private:
    glm::quat eulerToQuatByYXZ(glm::vec3 vector);
 };

}