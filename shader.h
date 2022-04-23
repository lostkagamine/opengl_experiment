#pragma once

#include <string>

enum SHADER_TYPE
{
    SHADER_VERTEX,
    SHADER_FRAGMENT
};

class Shader
{
    public:
        Shader(std::string filepath, SHADER_TYPE type);
        unsigned int handle();

    private:
        unsigned int m_handle;

};