#include <openGL/drawable.h>

Drawable::Drawable()
    : bufIdx(QOpenGLBuffer::IndexBuffer),
      bufPos(QOpenGLBuffer::VertexBuffer),
      bufNor(QOpenGLBuffer::VertexBuffer),
      bufCol(QOpenGLBuffer::VertexBuffer)
{}

Drawable::~Drawable()
{
    destroy();
}

void Drawable::recreate()
{
    destroy();
    create();
}

void Drawable::destroy()
{
    bufIdx.destroy();
    bufPos.destroy();
    bufNor.destroy();
    bufCol.destroy();
}

GLenum Drawable::drawMode(){return GL_TRIANGLES;}
int Drawable::elemCount(){return count;}
bool Drawable::bindIdx(){return bufIdx.bind();}
bool Drawable::bindPos(){return bufPos.bind();}
bool Drawable::bindNor(){return bufNor.bind();}
bool Drawable::bindCol(){return bufCol.bind();}
