// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_VIZ_METAL_WINDOW_H_
#define INCLUDE_JET_VIZ_METAL_WINDOW_H_

#include <jet/macros.h>

#ifdef JET_MACOSX

#include <jet.viz/event.h>
#include <jet.viz/input_events.h>
#include <jet.viz/metal_app.h>
#include <jet.viz/metal_renderer.h>
#include <jet.viz/view_controller.h>

namespace jet {
namespace viz {

class MetalView;

//!
//! \brief Helper class for Metal-based window.
//!
//! \see MetalApp
//!
class MetalWindow final {
 public:
    MetalWindow(const std::string& title, int width, int height);
    ~MetalWindow();

    //! Returns Metal renderer.
    const MetalRendererPtr& renderer() const;

    MetalView* view() const;

    static void render(const MetalWindow& window);

 private:
    MetalView* _view;
    MetalRendererPtr _renderer;
};

typedef std::shared_ptr<MetalWindow> MetalWindowPtr;

}  // namespace viz
}  // namespace jet

#endif  // JET_MACOSX

#endif  // INCLUDE_JET_VIZ_METAL_WINDOW_H_
