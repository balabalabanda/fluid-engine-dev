// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_VERTEX_CENTERED_SCALAR_GRID3_H_
#define INCLUDE_JET_VERTEX_CENTERED_SCALAR_GRID3_H_

#include <jet/array3.h>
#include <jet/scalar_grid3.h>
#include <utility>  // just make cpplint happy..

namespace jet {

//!
//! \brief 3-D Vertex-centered scalar grid structure.
//!
//! This class represents 3-D vertex-centered scalar grid which extends
//! ScalarGrid3. As its name suggests, the class defines the data point at the
//! grid vertices (corners). Thus, A x B x C grid resolution will have
//! (A+1) x (B+1) x (C+1) data points.
//!
class VertexCenteredScalarGrid3 final : public ScalarGrid3 {
 public:
    //! Constructs zero-sized grid.
    VertexCenteredScalarGrid3();

    //! Constructs a grid with given resolution, grid spacing, origin and
    //! initial value.
    VertexCenteredScalarGrid3(
         size_t resolutionX,
         size_t resolutionY,
         size_t resolutionZ,
         double gridSpacingX = 1.0,
         double gridSpacingY = 1.0,
         double gridSpacingZ = 1.0,
         double originX = 0.0,
         double originY = 0.0,
         double originZ = 0.0,
         double initialValue = 0.0);

    //! Constructs a grid with given resolution, grid spacing, origin and
    //! initial value.
    VertexCenteredScalarGrid3(
        const Size3& resolution,
        const Vector3D& gridSpacing = Vector3D(1.0, 1.0, 1.0),
        const Vector3D& origin = Vector3D(),
        double initialValue = 0.0);

    //! Copy constructor.
    VertexCenteredScalarGrid3(const VertexCenteredScalarGrid3& other);

    //! Returns the actual data point size.
    Size3 dataSize() const override;

    //! Returns data position for the grid point at (0, 0, 0).
    //! Note that this is different from origin() since origin() returns
    //! the lower corner point of the bounding box.
    Vector3D dataOrigin() const override;

    //! Returns the copy of the grid instance.
    std::shared_ptr<ScalarGrid3> clone() const override;

    //!
    //! \brief Swaps the contents with the given \p other grid.
    //!
    //! This function swaps the contents of the grid instance with the given
    //! grid object \p other only if \p other has the same type with this grid.
    //!
    void swap(Grid3* other) override;

    //! Sets the contents with the given \p other grid.
    void set(const VertexCenteredScalarGrid3& other);

    //! Sets the contents with the given \p other grid.
    VertexCenteredScalarGrid3& operator=(
        const VertexCenteredScalarGrid3& other);

    //! Returns the grid builder instance.
    static ScalarGridBuilder3Ptr builder();
};

//! A grid builder class that returns 3-D vertex-centered scalar grid.
class VertexCenteredScalarGridBuilder3 final : public ScalarGridBuilder3 {
 public:
    //! Returns a vertex-centered grid for given parameters.
    ScalarGrid3Ptr build(
        const Size3& resolution,
        const Vector3D& gridSpacing,
        const Vector3D& gridOrigin,
        double initialVal) const override;
};

}  // namespace jet

#endif  // INCLUDE_JET_VERTEX_CENTERED_SCALAR_GRID3_H_
