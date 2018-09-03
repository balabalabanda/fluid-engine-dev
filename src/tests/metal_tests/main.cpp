// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#include <jet.viz/metal_app.h>
#include <jet.viz/metal_window.h>

using namespace jet::viz;

int main() {
    MetalApp::initialize();

    auto window = MetalApp::createWindow("Metal Tests", 1280, 720);

    MetalApp::run();

    return 0;
}
