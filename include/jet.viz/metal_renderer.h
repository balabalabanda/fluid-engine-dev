// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_VIZ_METAL_RENDERER_H_
#define INCLUDE_JET_VIZ_METAL_RENDERER_H_

#include <jet.viz/renderer.h>
#include <jet/macros.h>

#ifdef JET_MACOSX

namespace jet {
namespace viz {

class MetalWindow;
class MetalDevice;
class MetalCommandQueue;
class MetalRenderPipelineState;

class MetalRenderer final : public Renderer {
 public:
    MetalRenderer();
    ~MetalRenderer();

    //!
    //! Creates a vertex buffer with given parameters.
    //!
    //! \param shader Shader object for the buffer.
    //! \param vertices Vertex data.
    //! \param numberOfPoints Number of vertices.
    //! \return New vertex buffer.
    //!
    VertexBufferPtr createVertexBuffer(const ShaderPtr& shader,
                                       const float* vertices,
                                       size_t numberOfPoints) override;

    //!
    //! Creates an index buffer with given parameters.
    //!
    //! \param vertexBuffer Vertices for the index buffer.
    //! \param indices Index data.
    //! \param numberOfIndices Number of indices.
    //! \return New index buffer.
    //!
    IndexBufferPtr createIndexBuffer(const VertexBufferPtr& vertexBuffer,
                                     const uint32_t* indices,
                                     size_t numberOfIndices) override;

    //!
    //! Creates a 2-D texture with 8-bit image and given parameters.
    //!
    //! \param data 8-bit texture image data.
    //! \param size Size of the data.
    //! \return New 2-D texture.
    //!
    Texture2Ptr createTexture2(const ConstArrayView2<ByteColor>& data) override;

    //!
    //! Creates a 2-D texture with 32-bit image and given parameters.
    //!
    //! \param data 32-bit texture image data.
    //! \param size Size of the data.
    //! \return New 2-D texture.
    //!
    Texture2Ptr createTexture2(const ConstArrayView2<Color>& data) override;

    //!
    //! Creates a 3-D texture with 8-bit image and given parameters.
    //!
    //! \param data 8-bit texture image data.
    //! \param size Size of the data.
    //! \return New 3-D texture.
    //!
    Texture3Ptr createTexture3(const ConstArrayView3<ByteColor>& data) override;

    //!
    //! Creates a 3-D texture with 32-bit image and given parameters.
    //!
    //! \param data 32-bit texture image data.
    //! \param size Size of the data.
    //! \return New 3-D texture.
    //!
    Texture3Ptr createTexture3(const ConstArrayView3<Color>& data) override;

    //!
    //! Creates a shader object with given preset shader name.
    //!
    //! \param shaderName Preset shader name.
    //! \return New shader.
    //!
    ShaderPtr createPresetShader(const std::string& shaderName) const override;

    //!
    //! Sets current render primitive type state for drawing.
    //!
    //! \param type Primitive type.
    //!
    void setPrimitiveType(PrimitiveType type) override;

    //!
    //! Draws currently bound object.
    //!
    //! \param numberOfVertices Number of vertices.
    //!
    void draw(size_t numberOfVertices) override;

    //!
    //! Draws currently bound indexed object.
    //!
    //! \param numberOfIndices Number of indices.
    //!
    void drawIndexed(size_t numberOfIndices) override;

    void render(const MetalWindow* window);

    MetalDevice* device() const;
    MetalCommandQueue* commandQueue() const;
    MetalRenderPipelineState* renderPipelineState() const;

 protected:
    //! Called when rendering a frame begins.
    void onRenderBegin() override;

    //! Called when rendering a frame ended.
    void onRenderEnd() override;

    //! Called when the view has resized.
    void onResize(const Viewport& viewport) override;

    //! Called when the render states has changed.
    void onSetRenderStates(const RenderStates& states) override;

 private:
    MetalDevice* _device = nullptr;
    MetalCommandQueue* _commandQueue = nullptr;
    MetalRenderPipelineState* _renderPipelineState = nullptr;
};

typedef std::shared_ptr<MetalRenderer> MetalRendererPtr;

}  // namespace viz
}  // namespace jet

#endif  // JET_MACOSX

#endif  // INCLUDE_JET_VIZ_METAL_RENDERER_H_
