#include "Scene.h"

#include <iostream>

Scene::Scene(int width, int height) {
    this->fbo_input = std::make_shared<LayerFBO>(width, height);
    this->fbo_output = std::make_shared<LayerFBO>(width, height);

    std::cout << fbo_input << " " << fbo_output << std::endl;

    this->width = width;
    this->height = height;
}

void Scene::onFramebufferSizeEvent(callback::FramebufferSizeEvent &event) {
    this->aspect = static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight());
}

void Scene::render() {
    RenderParam param;

    param.setProgram(nullptr).setAspect(aspect).setFBOInput(fbo_input).setFBOOutput(fbo_output);

    for (int i = 0; i < this->pipeline.size(); i++) {
	if (!pipeline[i]) {
	    pipeline.erase(pipeline.begin() + i);
	    i--;
	    continue;
	}

	pipeline[i]->render(param);
    }
}

void Scene::addLink(shared_ptr<IRenderable> renderable) {
    pipeline.push_back(renderable);
}

shared_ptr<IRenderable> Scene::getLink(int i) const {
    if (i < 0 || i >= pipeline.size()) {
	throw std::runtime_error("SCENE ERROR: get listener error at -> i < 0 or i >= pipeline.size()");
    }

    return pipeline[i];
}

void Scene::removeLink(int i) {
    if (i < 0 || i >= pipeline.size()) {
	throw std::runtime_error("SCENE ERROR: remove listener error at -> i < 0 or i >= pipeline.size()");
    }

    pipeline.erase(pipeline.begin() + i);
}

void Scene::removeLink(shared_ptr<IRenderable> renderable) {
    pipeline.erase(
        std::remove_if(pipeline.begin(), pipeline.end(),
            [&](const std::shared_ptr<IRenderable>& ptr) { return ptr.get() == renderable.get(); }),
        pipeline.end()
    );
}

shared_ptr<LayerFBO> Scene::getFBOInput() const {
    return this->fbo_input;
}

shared_ptr<LayerFBO> Scene::getFBOOutput() const {
    return this->fbo_output;
}