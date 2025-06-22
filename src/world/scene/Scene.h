#pragma once

#include <memory>
#include <vector>
#include <stdexcept>

#include "graphics/IRenderable.h"
#include "graphics/param/RenderParam.h"
#include "graphics/gl_objects/buffers/fbo/LayerFBO.h"
#include "graphics/elements/window/callback/windowCallback/WindowListener.h"
#include "graphics/elements/window/callback/windowCallback/events/FramebufferSizeEvent.h"

class Scene : public callback::WindowListener {
public:
    Scene(int width, int height);

    ~Scene() = default;

    void onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) override;

    void render();

    void addLink(shared_ptr<IRenderable> renderable);

    shared_ptr<IRenderable> getLink(int i) const;

    void removeLink(int i);

    void removeLink(shared_ptr<IRenderable> renderable);

    shared_ptr<LayerFBO> getFBOInput() const;

    shared_ptr<LayerFBO> getFBOOutput() const;
private:
    std::shared_ptr<LayerFBO> fbo_input, fbo_output;

    std::vector<shared_ptr<IRenderable>> pipeline;

    int width, height;

    float aspect = 1;
};