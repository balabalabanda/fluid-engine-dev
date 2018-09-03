// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_VIZ_METAL_SHADER_H_
#define INCLUDE_JET_VIZ_METAL_SHADER_H_

#ifdef JET_MACOSX

#include <jet.viz/shader.h>

namespace jet {
namespace viz {

class MetalDevice;
class MetalLibrary;
class MetalFunction;

//! Metal shader.
class MetalShader final : public Shader {
 public:
    //!
    //! Constructs a shader with user-given render parameters.
    //!
    //! \param userRenderParams User-given render parameters.
    //!
    MetalShader(const RenderParameters& userRenderParams);

    //!
    //! Constructs a shader with user-given render parameters, vertex format,
    //! vertex shader, and fragment shader.
    //!
    //! \param device           Metal device.
    //! \param userRenderParams User-given render parameters.
    //! \param shaderSource     Shader in string.
    //!
    MetalShader(const MetalDevice* device,
                const RenderParameters& userRenderParams,
                const std::string& shaderSource);

    //! Destructor.
    virtual ~MetalShader();

    //! Clears the contents.
    void clear() override;

    //!
    //! Loads vertex and fragment shaders.
    //!
    //! \param device       Metal device.
    //! \param shaderSource Shader in string.
    //!
    void load(const MetalDevice* device, const std::string& shaderSource);

    //! Returns Metal Library pointer.
    MetalLibrary* library() const;

    //! Returns Metal Function pointer for vertex function (shader).
    MetalFunction* vertexFunction() const;

    //! Returns Metal Function pointer for fragment function (shader).
    MetalFunction* fragmentFunction() const;

 private:
    MetalLibrary* _library = nullptr;
    MetalFunction* _vertFunc = nullptr;
    MetalFunction* _fragFunc = nullptr;

    void onBind(const Renderer* renderer) override;

    void onUnbind(const Renderer* renderer) override;
};

typedef std::shared_ptr<MetalShader> MetalShaderPtr;

}  // namespace viz
}  // namespace jet

#endif  // JET_MACOSX

#endif  // INCLUDE_JET_VIZ_METAL_SHADER_H_
