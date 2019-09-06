#include <scene/geometry/mesh.h>
#include <scene/geometry/boundingbox.h>

BoundingBox::BoundingBox(){
    maxBound = glm::vec3(0.5);
    minBound = glm::vec3(-0.5);
}

//GLenum BoundingBox::drawMode(){
//    return GL_LINES;
//}

//void BoundingBox::create(){
//    glm::vec3 cub_vert_pos[CUB_POS_COUNT];

//    //Front Face
//    //UR
//    cub_vert_pos[0] = glm::vec3(maxBound.x,maxBound.y,maxBound.z);
//    //LR
//    cub_vert_pos[1] = glm::vec3(maxBound.x,minBound.y,maxBound.z);
//    //LL
//    cub_vert_pos[2] = glm::vec3(minBound.x,minBound.y,maxBound.z);
//    //UL
//    cub_vert_pos[3] = glm::vec3(minBound.x,maxBound.y,maxBound.z);

//    //Back Face
//    //UR
//    cub_vert_pos[4] = glm::vec3(minBound.x, maxBound.y, minBound.z);
//    //LR
//    cub_vert_pos[5] = glm::vec3(minBound.x, minBound.y, minBound.z);
//    //LL
//    cub_vert_pos[6] = glm::vec3(maxBound.x, minBound.y, minBound.z);
//    //UL
//    cub_vert_pos[7] = glm::vec3(maxBound.x, maxBound.y, minBound.z);

//    glm::vec3 cub_vert_col[CUB_COL_COUNT];

//    for(int i = 0; i < CUB_COL_COUNT; i++)
//        cub_vert_col[i] =glm::vec3(0.8,0.6,0.2);

//    std::vector<GLuint> idx;

//    idx.push_back(0);idx.push_back(7);
//    idx.push_back(1);idx.push_back(6);
//    idx.push_back(2);idx.push_back(5);
//    idx.push_back(3);idx.push_back(4);

//    idx.push_back(0);idx.push_back(1);
//    idx.push_back(1);idx.push_back(2);
//    idx.push_back(2);idx.push_back(3);
//    idx.push_back(3);idx.push_back(0);

//    idx.push_back(4);idx.push_back(5);
//    idx.push_back(5);idx.push_back(6);
//    idx.push_back(6);idx.push_back(7);
//    idx.push_back(7);idx.push_back(4);

//    count = idx.size();

//    bufIdx.create();
//    bufIdx.bind();
//    bufIdx.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    bufIdx.allocate(idx.data(), count * sizeof(GLuint));

//    bufPos.create();
//    bufPos.bind();
//    bufPos.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    bufPos.allocate(cub_vert_pos, CUB_POS_COUNT * sizeof(glm::vec3));

//    bufCol.create();
//    bufCol.bind();
//    bufCol.setUsagePattern(QOpenGLBuffer::StaticDraw);
//    bufCol.allocate(cub_vert_col, CUB_COL_COUNT * sizeof(glm::vec3));
//}
