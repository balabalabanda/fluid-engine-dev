// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#import <jet.viz/metal_renderer.h>
#import <jet.viz/metal_shader.h>
#import <jet.viz/metal_window.h>

#import "metal_preset_shaders.h"
#import "metal_view.h"
#import "mtlpp_wrappers.h"

#import <MetalKit/MetalKit.h>

using namespace jet::viz;

namespace {

MetalShaderPtr g_shader;
mtlpp::Buffer g_vertexBuffer;

mtlpp::Drawable GetDrawable(const MetalWindow* window) {
    return ns::Handle{
        (__bridge void*)((__bridge MTKView*)window->view()->GetPtr())
            .currentDrawable};
}

mtlpp::RenderPassDescriptor GetRenderPassDescriptor(const MetalWindow* window) {
    return ns::Handle{
        (__bridge void*)((__bridge MTKView*)window->view()->GetPtr())
            .currentRenderPassDescriptor};
}

}  // namespace

MetalRenderer::MetalRenderer() {
    const float vertexData[] = {
        0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
    };
    _device = new MetalDevice(mtlpp::Device::CreateSystemDefaultDevice());
    _commandQueue = new MetalCommandQueue(_device->value.NewCommandQueue());

    g_shader = std::make_shared<MetalShader>(_device, RenderParameters(),
                                             kSimpleColorShader);

    g_vertexBuffer = _device->value.NewBuffer(
        vertexData, sizeof(vertexData),
        mtlpp::ResourceOptions::CpuCacheModeDefaultCache);

    mtlpp::RenderPipelineDescriptor renderPipelineDesc;
    renderPipelineDesc.SetVertexFunction(g_shader->vertexFunction()->value);
    renderPipelineDesc.SetFragmentFunction(g_shader->fragmentFunction()->value);
    renderPipelineDesc.GetColorAttachments()[0].SetPixelFormat(
        mtlpp::PixelFormat::BGRA8Unorm);
    _renderPipelineState = new MetalRenderPipelineState(
        _device->value.NewRenderPipelineState(renderPipelineDesc, nullptr));
}

MetalRenderer::~MetalRenderer() {
    delete _device;
    delete _commandQueue;
    delete _renderPipelineState;
}

VertexBufferPtr MetalRenderer::createVertexBuffer(const ShaderPtr& shader,
                                                  const float* vertices,
                                                  size_t numberOfPoints) {
    return nullptr;
}

IndexBufferPtr MetalRenderer::createIndexBuffer(
    const VertexBufferPtr& vertexBuffer, const uint32_t* indices,
    size_t numberOfIndices) {
    return nullptr;
}

Texture2Ptr MetalRenderer::createTexture2(
    const ConstArrayView2<ByteColor>& data) {
    return nullptr;
}

Texture2Ptr MetalRenderer::createTexture2(const ConstArrayView2<Color>& data) {
    return nullptr;
}

Texture3Ptr MetalRenderer::createTexture3(
    const ConstArrayView3<ByteColor>& data) {
    return nullptr;
}

Texture3Ptr MetalRenderer::createTexture3(const ConstArrayView3<Color>& data) {
    return nullptr;
}

ShaderPtr MetalRenderer::createPresetShader(
    const std::string& shaderName) const {
    RenderParameters params;

    if (shaderName == "simple_color") {
        return std::make_shared<MetalShader>(_device, params,
                                             kSimpleColorShader);
    }

    return nullptr;
}

void MetalRenderer::setPrimitiveType(PrimitiveType type) {}

void MetalRenderer::draw(size_t numberOfVertices) {}

void MetalRenderer::drawIndexed(size_t numberOfIndices) {}

void MetalRenderer::render(const MetalWindow* window) {
    mtlpp::CommandBuffer commandBuffer = _commandQueue->value.CommandBuffer();

    mtlpp::RenderPassDescriptor renderPassDesc =
        GetRenderPassDescriptor(window);
    if (renderPassDesc) {
        mtlpp::RenderCommandEncoder renderCommandEncoder =
            commandBuffer.RenderCommandEncoder(renderPassDesc);
        renderCommandEncoder.SetRenderPipelineState(
            _renderPipelineState->value);
        renderCommandEncoder.SetVertexBuffer(g_vertexBuffer, 0, 0);
        renderCommandEncoder.Draw(mtlpp::PrimitiveType::Triangle, 0, 3);
        renderCommandEncoder.EndEncoding();
        commandBuffer.Present(GetDrawable(window));
    }

    commandBuffer.Commit();
    commandBuffer.WaitUntilCompleted();
}

MetalDevice* MetalRenderer::device() const { return _device; }

MetalCommandQueue* MetalRenderer::commandQueue() const { return _commandQueue; }

MetalRenderPipelineState* MetalRenderer::renderPipelineState() const {
    return _renderPipelineState;
}

void MetalRenderer::onRenderBegin() {}

void MetalRenderer::onRenderEnd() {}

void MetalRenderer::onResize(const Viewport& viewport) {}

void MetalRenderer::onSetRenderStates(const RenderStates& states) {}
