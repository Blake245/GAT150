#pragma once
#include "Font.h"
#include "Renderer.h"
#include "Color.h"
#include "../Engine.h"

class Text
{
public:
	Text() = default;
	Text(res_t<Font> font) : m_font{ font } {}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

private:
	//Font* m_font{ nullptr };
	res_t<Font> m_font;
	SDL_Texture* m_texture{ nullptr };
};
