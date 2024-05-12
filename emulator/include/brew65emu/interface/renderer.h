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

        void draw_pixels(const uint8_t *pixels, int x, int y, int w, int h);
        void draw_pixels(const uint32_t *pixels, int x, int y, int w, int h);

        void render();

    private:
        void draw_surface(SDL_Surface *surface, int x, int y);

        int w, h;

        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Texture *texture;
    };
}
