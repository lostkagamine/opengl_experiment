#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window
{
    public:
        Window(int width, int height, std::string title);
        void run();
        ~Window();
    
    private:
        SDL_Window* m_window;
        int m_width;
        int m_height;
        std::string m_title;
        SDL_GLContext m_glcontext;
};