#pragma once
#include <la.h>
#include <ctime>
#include <chrono>
#include <scene/scene.h>
#include <raytracing/ray.h>
#include <scene/geometry/cloud.h>
#include <raytracing/intersection.h>
#include <raytracing/intersectionengine.h>

class Scene;

#define epsilon .05f
#define sample 20
#define damp 1.f

//The Integrator class recursively evaluates the path a ray takes throughout a scene
//and computes the color a ray becomes as it bounces.
//It samples the materials, probability density functions, and BRDFs of the surfaces the ray hits
//to do this.

class Integrator
{
public:
    Integrator();
    Integrator(Scene *s);
    glm::vec3 TraceRay(Ray r, unsigned int depth);
    void SetDepth(unsigned int depth);
    glm::vec3 RayMarch(Intersection isx, Geometry *light, glm::vec3 light_position, glm::vec3 march_direction, float &T);

    Scene* scene;
    IntersectionEngine* intersection_engine;

protected:
    unsigned int max_depth;//Default value is 5.
};
