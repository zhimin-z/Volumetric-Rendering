#pragma once

#include <la.h>
#include <raytracing/ray.h>
#include <openGL/drawable.h>
#include <raytracing/samplers/pixelsampler.h>

//A perspective projection camera
//Receives its eye position and reference point from the scene XML file
class Camera : public Drawable
{
public:
    Camera();
    Camera(unsigned int w, unsigned int h);
    Camera(unsigned int w, unsigned int h, const glm::vec3 &e, const glm::vec3 &r, const glm::vec3 &worldUp);
    Camera(const Camera &c);

    void CopyAttributes(const Camera &c);

    float fovy, fovx;
    float focalDistance, lensRadius;
    unsigned int width, height;  // Screen dimensions
    float near_clip;  // Near clip plane distance
    float far_clip;  // Far clip plane distance

    //Computed attributes
    float aspect;

    glm::vec3 eye,      //The position of the camera in world space
              ref,      //The point in world space towards which the camera is pointing
              look,     //The normalized vector from eye to ref. Is also known as the camera's "forward" vector.
              up,       //The normalized vector pointing upwards IN CAMERA SPACE. This vector is perpendicular to LOOK and RIGHT.
              right,    //The normalized vector pointing rightwards IN CAMERA SPACE. It is perpendicular to UP and LOOK.
              world_up, //The normalized vector pointing upwards IN WORLD SPACE. This is primarily used for computing the camera's initial UP vector.
              V,        //Represents the vertical component of the plane of the viewing frustum that passes through the camera's reference point. Used in Camera::Raycast.
              H;        //Represents the horizontal component of the plane of the viewing frustum that passes through the camera's reference point. Used in Camera::Raycast.

    glm::mat4 PerspectiveProjectionMatrix();
    glm::mat4 ViewMatrix();
    glm::mat4 getViewProj();

    void RecomputeAttributes();

    Ray Raycast(const glm::vec2 &pt);         //Creates a ray in 3D space given a 2D point on the screen, in screen coordinates.
    Ray Raycast(float x, float y);            //Same as above, but takes two floats rather than a vec2.
    Ray RaycastNDC(float ndc_x, float ndc_y); //Creates a ray in 3D space given a 2D point in normalized device coordinates.

    void RotateAboutUp(float deg);
    void RotateAboutRight(float deg);

    void TranslateAlongLook(float amt);
    void TranslateAlongRight(float amt);
    void TranslateAlongUp(float amt);

    //Methods inherited from Drawable
    void create();

    virtual GLenum drawMode();

    std::mt19937 rng;
    std::uniform_real_distribution<float> u01;
    //std::uniform_real_distribution<float> uHalf;
};
