#pragma once

#include <SDL2/SDL.h>
#include <vector>

namespace brew65emu::interface
{
    class Renderer
    {
    public:
        Renderer(int w, int h, const char *font_path);
        ~Renderer();

        void draw_pixels(const uint8_t *pixels, int x, int y, int w, int h);
        void draw_text(const char *text, int x, int y, int size, uint8_t rgb332);

        void render();

    private:
        void draw_surface(SDL_Surface *surface, int x, int y);

        int w, h;
        const char *font_path;

        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_Texture *texture;
    };
}
