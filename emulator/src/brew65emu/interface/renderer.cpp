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

    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (texture == nullptr)
    {
        throw std::runtime_error("SDL_CreateTexture failed");
    }

    uint32_t *pixels;
    this->update_start(&pixels, 0, 0, w, h);
    for (int i = 0; i < w * h; i++)
    {
        pixels[i] = 0xFF000000;
    }
    this->update_end();
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::update_start(uint32_t **pixels, int x, int y, int w, int h)
{
    auto lockArea = SDL_Rect{x, y, w, h};

    void *texturePixels;
    int pitch;
    SDL_LockTexture(this->texture, &lockArea, &texturePixels, &pitch);

    *pixels = reinterpret_cast<uint32_t *>(texturePixels);
}

void Renderer::update_pixel(uint32_t *pixels, int x, int y, uint32_t color)
{
    pixels[y * this->w + x] = color;
}

void Renderer::update_end()
{
    SDL_UnlockTexture(this->texture);
}

void Renderer::render()
{
    SDL_RenderCopy(this->renderer, this->texture, nullptr, nullptr);
    SDL_RenderPresent(this->renderer);
}
