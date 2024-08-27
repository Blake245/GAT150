#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
class TextureComponent : public RenderComponent
{
public:
	CLASS_DECLARATION(TextureComponent)
	CLASS_PROTOTYPE(TextureComponent)

	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

public:
	Rect source;
	std::string textureName;
	res_t<Texture> texture;
};
