#include "other.h"
#include <iostream>

void other::die(std::string message)
{
    auto err_text = "An error has occurred, this program must now close.\n\n" + message;
    SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_ERROR,
        "Fatal Error",
        err_text.c_str(),
        NULL);
    std::cout << err_text << std::endl;
    std::exit(1);
}