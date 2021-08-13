#include "window.h"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Renderer *Window::renderer = nullptr;

Window::Window(const std::string &title, int width, int height) :
_title(title), _height(height), _width(width)
{
    _closed = !init();
}

Window::~Window() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}

bool Window::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initiate SDL. \n";;
        return false;
    }

    if(IMG_Init(IMG_INIT_PNG) < 0) {
        std::cout << "Could not initiate PNG from SDL_Image!\n";
        return false;
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

    if(_window == nullptr) {
        std::cout << "Failed to create window.\n";
        return false;
    }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr) {
        std::cout << "Failed to create renderer.\n";
        return false;
    }

    return true;
}

void Window::pollEvents(SDL_Event &e) {
    switch (e.type) {
    case SDL_QUIT:
        _closed = true;
        break;
    case SDL_KEYDOWN:
        switch(e.key.keysym.sym) {
            case SDLK_ESCAPE:
                _closed = true;
                break;
        }
        break;
    case SDL_MOUSEMOTION:
        std::cout << e.motion.x << ", " << e.motion.y << "\n";
        break;
    case SDL_MOUSEBUTTONDOWN:
        std::cout << "You clicked your mouse button!\n";
        break;
    default:
        break;
    }
}

void Window::clear() const {
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
    SDL_RenderClear(renderer);
}

