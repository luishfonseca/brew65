#include <brew65emu/interface/renderer.h>

#include <stdexcept>
#include <cassert>

using namespace brew65emu::interface;

Renderer::Renderer(int w, int h)
{
    this->w = w;
    this->h = h;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("SDL_Init failed");
    }

    this->window = SDL_CreateWindow("Brew65 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        throw std::runtime_error("SDL_CreateWindow failed");
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        throw std::runtime_error("SDL_CreateRenderer failed");
    }

    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if (texture == nullptr)
    {
        throw std::runtime_error("SDL_CreateTexture failed");
    }

    std::vector<uint8_t> pixels(w * h, 0);
    this->draw_pixels(pixels.data(), 0, 0, w, h);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::draw_pixels(const uint8_t *pixels, int x, int y, int w, int h)
{
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom((void *)pixels, w, h, 8, w, SDL_PIXELFORMAT_RGB332);
    draw_surface(surface, x, y);

    SDL_FreeSurface(surface);
}

void Renderer::draw_pixels(const uint32_t *pixels, int x, int y, int w, int h)
{
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom((void *)pixels, w, h, 32, w, SDL_PIXELFORMAT_ARGB8888);
    draw_surface(surface, x, y);

    SDL_FreeSurface(surface);
}

void Renderer::draw_surface(SDL_Surface *surface, int x, int y)
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (texture == nullptr)
    {
        throw std::runtime_error("SDL_CreateTextureFromSurface failed");
    }

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_SetRenderTarget(this->renderer, this->texture);
    SDL_RenderCopy(this->renderer, texture, nullptr, &rect);

    SDL_DestroyTexture(texture);
}

void Renderer::render()
{
    SDL_SetRenderTarget(this->renderer, nullptr);
    SDL_RenderCopy(this->renderer, this->texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}
