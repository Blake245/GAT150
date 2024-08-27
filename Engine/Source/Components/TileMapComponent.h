#pragma once
#include "Component.h"
#include <vector>

class TileMapComponent : public Component
{
public:
	TileMapComponent() = default;

	CLASS_DECLARATION(TileMapComponent)
	CLASS_PROTOTYPE(TileMapComponent)

	void Initialize() override;
	void Update(float dt) override;
public:
	int numColumns = 0;
	int numRows = 0;
	Vector2 tileSize{ 0, 0 };
	
	std::vector<std::string> tileNames;
	std::vector<int> tiles;
};

