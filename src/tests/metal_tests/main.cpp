// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#include <jet.viz/metal_app.h>
#include <jet.viz/metal_window.h>
#include <jet.viz/triangle_renderable.h>

using namespace jet::viz;

int main() {
    MetalApp::initialize();

    auto window = MetalApp::createWindow("Metal Tests", 1280, 720);

    auto renderer = window->renderer();
    renderer->setBackgroundColor(Color{1, 1, 1, 1});

    auto renderable = std::make_shared<TriangleRenderable>(renderer.get());
    renderer->addRenderable(renderable);

    MetalApp::run();

    return 0;
}
