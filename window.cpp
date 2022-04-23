#include "window.h"
#include <string>
#include <GL/glew.h>
#include "other.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex.h"
#include "vao.h"

Window::Window(int w, int h, std::string title)
{
    this->m_width = w;
    this->m_height = h;
    this->m_title = title;
    
    auto sdl_win = SDL_CreateWindow(
        this->m_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->m_width,
        this->m_height,
        SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN
    );

    this->m_window = sdl_win;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    this->m_glcontext = SDL_GL_CreateContext(this->m_window);

    if (!this->m_glcontext)
    {
        other::die("Fuck (SDL_GL_CreateContext)");
    }

    if (glewInit() != GLEW_OK)
    {
        other::die("Fuck (OpenGL failed)");
    }
}

Window::~Window()
{
    SDL_DestroyWindow(this->m_window);
}

void Window::run()
{
    SDL_GL_SetSwapInterval(1);

    // Compile some shaders
    auto test_v = Shader("shader/test.vs", SHADER_VERTEX);
    auto test_f = Shader("shader/test.fs", SHADER_FRAGMENT);
    auto program = Program();
    program.add(std::move(test_v));
    program.add(std::move(test_f));
    program.link();

    auto vertices = Buffer<Vertex, GL_ARRAY_BUFFER>();

    auto vao = Vao();
    vao.bind();

    vertices.bind();
    vertices.data({ 
        {{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f }},
        {{  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f }},
        {{  0.0f,  0.5f, 0.0f }, { 0.0f, 1.0f }}
    });
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //auto indices = Buffer<uint, GL_ELEMENT_ARRAY_BUFFER>();
    //indices.data({
    //    0, 1, 2,
    //});
    //indices.bind();

    SDL_Event evt;
    for(;;)
    {
        SDL_PollEvent(&evt);
        switch (evt.type)
        {
            case SDL_QUIT:
                goto exit_loop;
                break;
            case SDL_KEYDOWN:
                switch (evt.key.keysym.scancode)
                {
                    case SDL_SCANCODE_ESCAPE:
                        goto exit_loop;
                        break;
                    default:
                        break;
                }
                break;
        }

        glClearColor(0, 0, 0, 255);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        program.use();
        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(this->m_window);
    }
    exit_loop: ;
}