#include <SDL2/SDL_image.h>
#include <iostream>
#include "rect.h"

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a) :
_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{
}

Rect::Rect(int w, int h, int x, int y, const std::string &img_path) :
_w(w), _h(h), _x(x), _y(y)
{
    auto surface = IMG_Load(img_path.c_str());
    if(!surface) {
        std::cout << "Failed to create surface.\n";
    }

    _texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if(!_texture) {
        std::cout << "Failed to create texture.\n";
    }
    SDL_FreeSurface(surface);
}

Rect::~Rect() 
{
    SDL_DestroyTexture(_texture);
}

void Rect::draw() const
{   
    SDL_Rect rect = {_x, _y, _w, _h};
    if(_texture) {
        SDL_RenderCopy(Window::renderer, _texture, nullptr, &rect);
    } else {
        SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
        SDL_RenderFillRect(Window::renderer, &rect);
    }
}

void Rect::pollEvents(SDL_Event &e) 
{
    if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
            case SDLK_LEFT:
                _x -= 10;
                break;
            case SDLK_RIGHT:
                _x += 10;
                break;
            case SDLK_UP:
                _y -= 10;
                break;
            case SDLK_DOWN:
                _y += 10;
                break;
        }
    }
}