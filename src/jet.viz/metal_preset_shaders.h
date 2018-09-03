// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef SRC_JET_VIZ_METAL_PRESET_SHADERS_H_
#define SRC_JET_VIZ_METAL_PRESET_SHADERS_H_

namespace jet {

namespace viz {

const char kSimpleColorShader[] = R"metal(
    #include <metal_stdlib>
    using namespace metal;

    vertex float4 vertFunc(
        const device packed_float3* vertexArray [[buffer(0)]],
        unsigned int vID[[vertex_id]])
    {
        return float4(vertexArray[vID], 1.0);
    }

    fragment half4 fragFunc()
    {
        return half4(1.0, 0.0, 0.0, 1.0);
    }
)metal";
}

}  // namespace jet

#endif  // SRC_JET_VIZ_METAL_PRESET_SHADERS_H_
