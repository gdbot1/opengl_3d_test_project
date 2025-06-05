#include "TransformMatrix.h"

namespace mtrx {

class ViewMatrix : public TransformMatrix {
public:
    ViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);//mode = 1

    ViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float mode);

    ~ViewMatrix() = default;

    virtual glm::mat4 getMatrix() const override;
};

}