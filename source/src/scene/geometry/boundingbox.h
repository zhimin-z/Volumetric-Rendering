#pragma once
#include <openGL/drawable.h>

//static const int CUB_COL_COUNT = 12;
//static const int CUB_POS_COUNT = 8;

class BoundingBox// : public Drawable
{
public:
    BoundingBox();
    //void create();
    //GLenum drawMode();

    glm::vec3 maxBound;
    glm::vec3 minBound;
};
