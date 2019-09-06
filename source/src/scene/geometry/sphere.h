#pragma once
#include <scene/geometry/geometry.h>

//A sphere is assumed to have a radius of 0.5 and a center of <0,0,0>.
//These attributes can be altered by applying a transformation matrix to the sphere.
class Sphere : public Geometry
{
public:
    Sphere();
    Intersection GetIntersection(Ray r);
    virtual glm::vec2 GetUVCoordinates(const glm::vec3 &point);
    virtual glm::vec4 ComputeNormal(const glm::vec4 &P);
    void create();

    virtual void ComputeArea();
    virtual glm::vec3 SampleLight(glm::vec2 rand);
};
