#pragma once

#include <GL/glew.h>
#include <vector>
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

template<typename T, size_t T2>
class Buffer
{
    public:
        Buffer()
        {
            glGenBuffers(1, &this->m_handle);
        };

        void data(std::vector<T>&& d)
        {
            auto data = d.data(); // T*
#ifndef NDEBUG
            GLenum what;
            switch (T2)
            {
                case GL_ARRAY_BUFFER:
                    what = GL_ARRAY_BUFFER_BINDING;
                    break;
                case GL_ELEMENT_ARRAY_BUFFER:
                    what = GL_ELEMENT_ARRAY_BUFFER_BINDING;
                    break;
            };
            GLint t;
            glGetIntegerv(what, &t);
            assertm((uint)t == this->m_handle, "You forgot to bind a buffer, idiot");
#endif
            glNamedBufferData(this->m_handle, d.size() * sizeof(T), data, GL_STATIC_DRAW);
        };

        void bind()
        {
            glBindBuffer(T2, this->m_handle);
        };

        ~Buffer()
        {
            glDeleteBuffers(1, &this->m_handle);
        };

    private:
        GLuint m_handle;
};