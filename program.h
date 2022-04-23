#pragma once

#include <shader.h>

class Program
{
    public:
        Program();
        void add(Shader&& sh);
        void link();
        void use();

    private:
        unsigned int m_gl_handle;
};