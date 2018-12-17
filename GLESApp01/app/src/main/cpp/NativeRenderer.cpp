

#include <cmath>
#include <cassert>
#include "NativeRenderer.h"

static const GLchar vcode[] =
"#version 300 es\n"
"in vec2 p;\n"
"in vec4 color;\n"
"uniform mat2 matTransform;\n"
"out vec4 vColor;\n"
"void main() {\n"
"    vec2 p2 = matTransform * p;"
"    gl_Position = vec4(p2.x, p2.y, 0.0, 1.0);\n"
"    vColor = color;\n"
"}\n";

static const GLchar fcode[] =
"#version 300 es\n"
"precision mediump float;\n"
"in vec4 vColor;\n"
"out vec4 outColor;\n"
"void main() {\n"
"    outColor = vColor;\n"
"}\n";

const Vertex triangle[] = {
        {{-0.7f, -0.7f}, {0x00, 0xFF, 0x00, 0xFF}},
        {{ 0.7f, -0.7f}, {0x00, 0x00, 0xFF, 0xFF}},
        {{ 0.0f,  0.0f}, {0xFF, 0x00, 0x00, 0xFF}},

        {{ 0.7f,  0.7f}, {0x00, 0xFF, 0x00, 0xFF}},
        {{-0.7f,  0.7f}, {0x00, 0x00, 0xFF, 0xFF}},
        {{ 0.0f,  0.0f}, {0xFF, 0x00, 0x00, 0xFF}},
};

GLuint create_shader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    return shader;
}

NativeRenderer::NativeRenderer()
        : eglContext_(eglGetCurrentContext())
{
    GLuint vs = create_shader(GL_VERTEX_SHADER, vcode);
    GLuint fs = create_shader(GL_FRAGMENT_SHADER, fcode);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    int valid = GL_FALSE;
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);
    assert(valid==GL_TRUE);

    glDeleteShader(vs);
    glDeleteShader(fs);
    glReleaseShaderCompiler(); // hint

    program_ = program;

    pos_attrib_ = glGetAttribLocation(program, "p");
    color_attrib_ = glGetAttribLocation(program, "color");
    matrix_uniform_ = glGetUniformLocation(program, "matTransform");

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), &triangle[0], GL_STATIC_DRAW);
}

NativeRenderer::~NativeRenderer()
{
    if (eglGetCurrentContext() != eglContext_)
        return;
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteProgram(program_);
}

void NativeRenderer::draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glUseProgram(program_);

    float m[] = {
         cos(theta_), sin(theta_),
        -sin(theta_), cos(theta_)};
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glVertexAttribPointer(pos_attrib_, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, position));
    glVertexAttribPointer(color_attrib_, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, rgba));
    glEnableVertexAttribArray(pos_attrib_);
    glEnableVertexAttribArray(color_attrib_);
    glUniformMatrix2fv(matrix_uniform_, 1, false, m);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    theta_ += 2.0 * 3.14 / 60.0;
    if (theta_>2*3.14) theta_ = 0;
}

void NativeRenderer::changed(int width, int height)
{
    glViewport(0, 0, width, height);
}