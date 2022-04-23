#include "program.h"
#include <GL/glew.h>
#include "other.h"
#include <fmt/core.h>

Program::Program()
{
    this->m_gl_handle = glCreateProgram();
}

void Program::add(Shader&& sh)
{
    unsigned int the_handle = sh.handle();
    glAttachShader(this->m_gl_handle, the_handle);
}

void Program::link()
{
    glLinkProgram(this->m_gl_handle);
    GLint ok = 42069;
    glGetProgramiv(this->m_gl_handle, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        char* log = new char[65535];
        GLsizei _NOT_USED = 0;
        glGetShaderInfoLog(this->m_gl_handle, 65535, &_NOT_USED, log);
        auto message = fmt::format("Shader linkedn't: {}", log);
        other::die(message);
    }
}

void Program::use()
{
    glUseProgram(this->m_gl_handle);
}