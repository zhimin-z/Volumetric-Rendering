#pragma once
#include <scene/materials/material.h>
#include <raytracing/intersection.h>
#include <perlin/perlin.h>
#include <openGL/drawable.h>
#include <raytracing/ray.h>
#include <scene/transform.h>
#include <math.h>

#define NUM 100
#define TOTAL (NUM*NUM*NUM)
#define radius 0.4f

class Perlin;
class Material;
class Intersection;

class Cloud : public Geometry
{
public:
    Cloud();
    Intersection GetIntersection(Ray r);
    virtual glm::vec2 GetUVCoordinates(const glm::vec3 &point);
    virtual glm::vec4 ComputeNormal(const glm::vec4 &P);
    void create(){}

    virtual void ComputeArea(){}
    virtual glm::vec3 SampleLight(glm::vec2 rand);
    float GetDensity(glm::vec3 point);

private:
    int octaves, seed;
    float freq, amp, voxel[TOTAL];
};
