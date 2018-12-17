#ifndef GLESAPP01_NATIVERENDERER_H
#define GLESAPP01_NATIVERENDERER_H

#include <EGL/egl.h>
#include <GLES3/gl31.h>
#include <GLES3/gl3ext.h>

struct Vertex {
    GLfloat position[2];
    GLubyte rgba[4];
};

class NativeRenderer {
public:
    NativeRenderer();
    ~NativeRenderer();
    void draw();
    void changed(int width, int height);

private:
    float theta_ = 0.0;

    const EGLContext eglContext_;

    GLuint program_ = 0;
    GLuint pos_attrib_ = 0;
    GLuint color_attrib_ = 0;
    GLuint matrix_uniform_ = 0;

    GLuint vertex_buffer_ = 0;
};

#endif //GLESAPP01_NATIVERENDERER_H

