#include "Text.h"
#include "Texture.h"
#include <SDL_ttf.h>
#include <iostream>


bool Text::Create(Renderer& renderer, const std::string& text, const Color& color)
{
	// create a surface using the font, text string and color
	SDL_Color c{ Color::ToInt(color.r), Color::ToInt(color.g), Color::ToInt(color.b), Color::ToInt(color.a) };
	SDL_Surface* surface = TTF_RenderText_Solid(m_font->GetFont(), text.c_str(), c);
	if (surface == nullptr)
	{
		std::cerr << "Could not create surface.\n";
		return false;
	}

	// create a texture from the surface, only textures can render to the renderer
 	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.GetRender(), surface);
	if (texture == nullptr)
	{
		SDL_FreeSurface(surface);
		std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
		return false;
	}


	// free the surface, no longer needed after creating the texture
	SDL_FreeSurface(surface);

	m_texture = std::make_shared<Texture>(texture);

	return true;
}

void Text::Draw(Renderer& renderer, float x, float y, float angle)
{
	assert(m_texture);
	
	renderer.DrawTexture(m_texture, x, y, angle);
	
}
