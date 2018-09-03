// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#include <pch.h>

#include "mtlpp_wrappers.h"

#include <jet.viz/metal_renderer.h>
#include <jet.viz/metal_shader.h>

using namespace jet::viz;

MetalShader::MetalShader(const RenderParameters& userRenderParams)
    : Shader(userRenderParams) {}

MetalShader::MetalShader(const MetalDevice* device,
                         const RenderParameters& userRenderParams,
                         const std::string& shaderSource)
    : Shader(userRenderParams) {
    load(device, shaderSource);
}

MetalShader::~MetalShader() { clear(); }

void MetalShader::clear() {
    if (_library != nullptr) {
        delete _library;
        _library = nullptr;
    }

    if (_vertFunc != nullptr) {
        delete _vertFunc;
        _vertFunc = nullptr;
    }

    if (_fragFunc != nullptr) {
        delete _fragFunc;
        _fragFunc = nullptr;
    }
}

void MetalShader::load(const MetalDevice* device,
                       const std::string& shaderSource) {
    mtlpp::Device d = device->value;
    _library = new MetalLibrary(d.NewLibrary(
        shaderSource.c_str(), mtlpp::CompileOptions(), nullptr));

    _vertFunc = new MetalFunction(_library->value.NewFunction("vertFunc"));
    _fragFunc = new MetalFunction(_library->value.NewFunction("fragFunc"));
}

MetalLibrary* MetalShader::library() const { return _library; }

MetalFunction* MetalShader::vertexFunction() const { return _vertFunc; }

MetalFunction* MetalShader::fragmentFunction() const { return _fragFunc; }

void MetalShader::onBind(const Renderer* renderer) {
    UNUSED_VARIABLE(renderer);
}

void MetalShader::onUnbind(const Renderer* renderer) {
    UNUSED_VARIABLE(renderer);
}
