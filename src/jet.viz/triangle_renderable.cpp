// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#include <pch.h>

#include <jet.viz/renderer.h>
#include <jet.viz/triangle_renderable.h>

using namespace jet;
using namespace viz;

TriangleRenderable::TriangleRenderable(Renderer* renderer)
    : _renderer(renderer) {
    _shader = renderer->createPresetShader("simple_color");

    Triangle3 triangle;
    triangle.points[0] = Vector3D(0, 1, 0);
    triangle.points[1] = Vector3D(-1, -1, 0);
    triangle.points[2] = Vector3D(1, -1, 0);

    setTriangle(triangle);
}

void TriangleRenderable::setTriangle(const Triangle3& triangle) {
    std::array<VertexPosition3, 3> vertices;

    for (int i = 0; i < 3; ++i) {
        vertices[i].x = static_cast<float>(triangle.points[i].x);
        vertices[i].y = static_cast<float>(triangle.points[i].y);
        vertices[i].z = static_cast<float>(triangle.points[i].z);
    }

    if (_vertexBuffer) {
        _vertexBuffer->update(reinterpret_cast<const float*>(vertices.data()));
    } else {
        _vertexBuffer = _renderer->createVertexBuffer(
            _shader, reinterpret_cast<const float*>(vertices.data()), 3);
    }
}

void TriangleRenderable::render(Renderer* renderer) {
    if (_shader && _vertexBuffer) {
        renderer->bindShader(_shader);
        renderer->bindVertexBuffer(_vertexBuffer);
        renderer->setPrimitiveType(PrimitiveType::Triangles);

        renderer->draw(_vertexBuffer->numberOfVertices());

        renderer->unbindVertexBuffer(_vertexBuffer);
        renderer->unbindShader(_shader);
    }
}
