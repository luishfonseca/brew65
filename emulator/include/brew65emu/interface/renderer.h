#pragma once

#include <SDL2/SDL.h>
#include <vector>

namespace brew65emu::interface
{
    class Renderer
    {
    public:
        Renderer(int w, int h);
        ~Renderer();

        void update_start(uint32_t **pixels, int x, int y, int w, int h);
        void update_pixel(uint32_t *pixels, int x, int y, uint32_t color);
        void update_end();

        void render();

    private:
        int w, h;

        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Texture *texture;
    };
}
