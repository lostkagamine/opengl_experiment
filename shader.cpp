#include "shader.h"
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "other.h"
#include <fmt/core.h>

Shader::Shader(std::string filepath, SHADER_TYPE type)
{
    // read source
    std::ifstream ifs (filepath);
    std::stringstream buf;
    buf << ifs.rdbuf();

    auto source = buf.str();

    GLuint s_type;
    switch (type)
    {
        case SHADER_VERTEX:
            s_type = GL_VERTEX_SHADER;
            break;
        case SHADER_FRAGMENT:
            s_type = GL_FRAGMENT_SHADER;
            break;
    }

    this->m_handle = glCreateShader(s_type);

    auto c_source = source.c_str();
    auto c_length = (GLint)source.length();

    glShaderSource(this->m_handle, 1, &c_source, &c_length);
    glCompileShader(this->m_handle);

    GLint is_it_good = 42069;
    glGetShaderiv(this->m_handle, GL_COMPILE_STATUS, &is_it_good);

    if (!is_it_good)
    {
        char* bitch = new char[65535];
        GLint _NOT_USED = 0;
        glGetShaderInfoLog(this->m_handle, 65535, &_NOT_USED, bitch);
        auto error = fmt::format("Shader {} compiledn't: {}", filepath, bitch);
        other::die(error);
    }
}

unsigned int Shader::handle()
{
    return this->m_handle;
}