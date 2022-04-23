#include <other.h>
#include <cstdio>
#include <SDL2/SDL.h>
#include "window.h"
#include <memory>

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        other::die("SDL_Init failed");
    }

    std::unique_ptr<Window> win;
    win = std::unique_ptr<Window>(new Window(800, 600, "OpenGL"));
    win->run();

    return 0;
}