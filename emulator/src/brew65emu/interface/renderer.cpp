#include <brew65emu/interface/renderer.h>

#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <cassert>
#include <sstream>

using namespace brew65emu::interface;

Renderer::Renderer(int w, int h, const char *font_path)
{
    this->w = w;
    this->h = h;
    this->font_path = font_path;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::stringstream ss;
        ss << "SDL_Init failed: " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    this->window = SDL_CreateWindow("Brew65 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        std::stringstream ss;
        ss << "SDL_CreateWindow failed: " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::stringstream ss;
        ss << "SDL_CreateRenderer failed: " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if (texture == nullptr)
    {
        std::stringstream ss;
        ss << "SDL_CreateTexture failed: " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    if (TTF_Init())
    {
        std::stringstream ss;
        ss << "TTF_Init failed: " << TTF_GetError();
        throw std::runtime_error(ss.str());
    }

    std::vector<uint8_t> pixels(w * h, 0);
    this->draw_pixels(pixels.data(), 0, 0, w, h);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

void Renderer::draw_pixels(const uint8_t *pixels, int x, int y, int w, int h)
{
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom((void *)pixels, w, h, 8, w, SDL_PIXELFORMAT_RGB332);
    draw_surface(surface, x, y);

    SDL_FreeSurface(surface);
}

void Renderer::draw_text(const char *text, int x, int y, int size, uint8_t rgb332)
{
    TTF_Font *font = TTF_OpenFont(this->font_path, size);
    if (font == nullptr)
    {
        std::stringstream ss;
        ss << "TTF_OpenFont failed: " << TTF_GetError();
        throw std::runtime_error(ss.str());
    }

    SDL_Color rgb888 = {static_cast<Uint8>(rgb332 >> 5),
                        static_cast<Uint8>((rgb332 >> 2) & 0b111),
                        static_cast<Uint8>(rgb332 & 0b11)};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, rgb888);
    draw_surface(surface, x, y);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
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
