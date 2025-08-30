#pragma once

#include <memory>
#include <string>

#include "graphics/gl_objects/uniform/Uniform.h"
#include "graphics/gl_objects/uniform/uniforms/basic/FloatUniform.h"
#include "graphics/gl_objects/uniform/uniforms/basic/Vec3Uniform.h"

#include "TestStruct.h"

class TestUniform : public Uniform<TestStruct> {
public:
    TestUniform(const std::string &path);

    virtual ~TestUniform() = default;

    virtual void updateLoc(GLint program) override;

    virtual void uniform() const override;

    virtual void setPath(const std::string &path) override;

    virtual void setPrefix(const std::string &prefix) override;

    virtual void setSuffix(const std::string &suffix) override;

    virtual void setValue(const TestStruct &value) override;
private:
    std::shared_ptr<FloatUniform> far_uniform;
    std::shared_ptr<Vec3Uniform> position_uniform, color_uniform;

    virtual void update();
};