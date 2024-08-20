#pragma once
#include "../Math/Vector2.h"
#include "../Resources/Resource.h"
#include <string>

class Texture : public Resource
{
public:
	Texture() = default;
	Texture(struct SDL_Texture* texture) : m_texture{ texture } {};
	~Texture();

	bool Create(std::string name, ...) override;

	bool Load(const std::string& filename, class Renderer& renderer);

	Vector2 GetSize();

	friend class Renderer;
private:
	struct SDL_Texture* m_texture = nullptr;

};
