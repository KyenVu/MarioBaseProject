#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}
Texture2D::~Texture2D()
{
    Free();
}

bool Texture2D::LoadFromFile(string path)
{
    Free();
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface == nullptr)
    {
        cout << "Failed to load image at " << path << "! Error: " << IMG_GetError() << endl;
        return false;
    }
    SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));
    m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
    if (m_texture == nullptr)
    {
        cout << "Unable to create texture from surface! Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        m_width = p_surface->w;
        m_height = p_surface->h;
    }

    SDL_FreeSurface(p_surface);
    return m_texture != nullptr;
}

void Texture2D::Free()
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
    //set where to render the texture
    SDL_Rect renderLocation = { newPosition.x, newPosition.y, m_width, m_height };
    // render to screen
    SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, angle, nullptr, flip);
}

void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle)
{
    SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angle, NULL, flip);
}