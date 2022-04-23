#pragma once

#include <GL/glew.h>

class Vao
{
    public:
        Vao()
        {
            glGenVertexArrays(1, &this->m_handle);
        };

        void bind()
        {
            glBindVertexArray(this->m_handle);
        };

    private:
        unsigned int m_handle;
};