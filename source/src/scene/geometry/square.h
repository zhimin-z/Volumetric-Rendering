#pragma once
#include <scene/geometry/geometry.h>

//A square is aligned with the XY plane with a normal aligned with the positive Z axis. Its side length is 1, and it is centered at the origin.
//These attributes can be altered by applying a transformation matrix to the square.
class SquarePlane : public Geometry
{
public:
    SquarePlane();
    Intersection GetIntersection(Ray r);
    virtual glm::vec2 GetUVCoordinates(const glm::vec3 &point);
    virtual glm::vec4 ComputeNormal(const glm::vec4 &P);
    void create();

    virtual void ComputeArea();
    virtual glm::vec3 SampleLight(glm::vec2 rand);
};
