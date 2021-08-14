#include "window.h"
#include "rect.h"
#include <iostream>

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

    Uint32 lastUpdate = SDL_GetTicks();
    while(!window.isClosed()) {
        Uint32 start = SDL_GetPerformanceCounter();
        pollEvents(window, rect);

        Uint32 current = SDL_GetTicks();

    	float dT = (current - lastUpdate) / 1000.0f;
        window._dT = dT;

        std::cout << "dT: " << std::to_string(window._dT) << std::endl;

        lastUpdate = current;

        rect.draw();
        window.clear(); 

        Uint32 end = SDL_GetPerformanceCounter();

        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        //Cap at 60 FPS.
        SDL_Delay(std::floor(16.666f - elapsedMS));
    }
}