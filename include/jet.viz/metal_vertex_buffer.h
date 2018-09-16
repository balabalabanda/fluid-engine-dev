// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_VIZ_METAL_VERTEX_BUFFER_H_
#define INCLUDE_JET_VIZ_METAL_VERTEX_BUFFER_H_

#ifdef JET_MACOSX

#include <jet.viz/gl_common.h>
#include <jet.viz/vertex_buffer.h>

#include <map>
#include <string>

namespace jet {
namespace viz {

class MetalPrivateBuffer;
class MetalPrivateDevice;

//!
//! \brief Dynamic vertex buffer implementation for Metal.
//!
//! This class implements Metal version of vertex buffer. This vertex
//! buffer is dynamic, meaning that the contents can be updated dynamically
//! (TODO).
//!
class MetalVertexBuffer final : public VertexBuffer {
 public:
    //! Default constructor.
    MetalVertexBuffer(MetalPrivateDevice* device, const ShaderPtr& shader,
                      const float* vertices, size_t numberOfVertices);

    //! Destructor.
    virtual ~MetalVertexBuffer();

    //!
    //! Updates the buffer with given vertex array.
    //!
    //! \param vertices Vertex array.
    //!
    void update(const float* vertices) override;

    MetalPrivateBuffer* buffer() const;

 private:
    MetalPrivateBuffer* _buffer = nullptr;

    void onClear() override;

    void onResize(const ShaderPtr& shader, const float* vertices,
                  size_t numberOfVertices) override;

    void onBind(Renderer* renderer) override;

    void onUnbind(Renderer* renderer) override;
};

//! Shared pointer type for MetalVertexBuffer.
typedef std::shared_ptr<MetalVertexBuffer> MetalVertexBufferPtr;

}  // namespace viz
}  // namespace jet

#endif  // JET_MACOSX

#endif  // INCLUDE_JET_VIZ_METAL_VERTEX_BUFFER_H_
