// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_VIZ_TRIANGLE_RENDERABLE_H_
#define INCLUDE_JET_VIZ_TRIANGLE_RENDERABLE_H_

#include "renderable.h"
#include "shader.h"
#include "texture2.h"
#include "vertex_buffer.h"

#include <jet/triangle3.h>

namespace jet {

namespace viz {

//! Renderable for triangle.
class TriangleRenderable final : public Renderable {
 public:
    //! Constructs the renderable.
    explicit TriangleRenderable(Renderer* renderer);

    //! Sets a triangle to be rendered.
    void setTriangle(const Triangle3& triangle);

 private:
    Renderer* _renderer;
    ShaderPtr _shader;
    VertexBufferPtr _vertexBuffer;

    void render(Renderer* renderer) override;
};

//! Shared pointer type for TriangleRenderable.
typedef std::shared_ptr<TriangleRenderable> TriangleRenderablePtr;

}  // namespace viz

}  // namespace jet

#endif  // INCLUDE_JET_VIZ_TRIANGLE_RENDERABLE_H_
