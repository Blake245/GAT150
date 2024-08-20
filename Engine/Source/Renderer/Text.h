#pragma once
#include "Font.h"
#include "Renderer.h"
#include "Color.h"
#include "../Engine.h"

class Texture;

class Text
{
public:
	Text() = default;
	Text(res_t<Font> font) : m_font{ font } {}
	~Text() = default;

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, float x, float y, float angle = 0);

	void SetFont(res_t<Font> font) { m_font = font; }
	res_t<Texture> GetTexture() { return m_texture; }

private:
	res_t<Font> m_font{ nullptr };
	res_t<Texture> m_texture{ nullptr };

};
