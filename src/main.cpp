#include "window.h"
#include "rect.h"

void pollEvents(Window &window, Rect &rect) 
{
    SDL_Event e;

    if(SDL_PollEvent(&e)) {
        rect.pollEvents(e);
        window.pollEvents(e);
    }
}

int main()
{
    Window window("SDL!", 640, 380);
    Rect rect(200, 200, 100, 100, "res/tennis.png");

    while(!window.isClosed()) {
        pollEvents(window, rect);
        rect.draw();
        window.clear();
    }
}