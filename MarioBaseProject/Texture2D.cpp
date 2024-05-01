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
    m_renderer = nullptr;
}

void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_width = 0;
		m_height = 0;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	//set where to render the texture
	SDL_Rect renderLocation = { 0,0,m_width, m_height };

	//render to screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, SDL_FLIP_NONE);
}
bool Texture2D::LoadFromFile(string path)
{
    // The final texture
    m_texture = nullptr;

    // Load image at specified path
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface == nullptr)
    {
        cout << "Unable to load image " << path << ". SDL_image Error: " << IMG_GetError();
        // colour key the image to be transparent
        SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface -> format, 0, 0XFF, 0XFF));
    }
    else
    {
        // Create texture from surface pixels
        m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
        if (m_texture == nullptr)
        {
            cout << "Unable to create texture from " << path << ". SDL Error: " << SDL_GetError();
        }
        else
        {
            m_width = p_surface->w;
            m_height = p_surface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(p_surface);
    }

    return m_texture != nullptr;
}

