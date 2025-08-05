#include "matrix/transform/TransformMatrix.h"

namespace mtrx {

class ModelMatrix : public TransformMatrix {
public:
    ModelMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);//mode = 1

    ~ModelMatrix() = default;

    virtual glm::mat4 getMatrix() const override;
};

}