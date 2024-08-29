#pragma once
#include "Framework/Game.h"
#include "Event/EventSystem.h"
#include <memory>
class SpaceGame : public Game, public Observer
{
public:
	enum class eState
	{
		TITLE,
		START_LEVEL,	
		GAME,
		GAME_OVER
	};
	SpaceGame() = default;
	SpaceGame(Engine* engine) : Game{engine} {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	// events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);

private:
	eState state{ eState::TITLE };
	std::unique_ptr<Scene> m_scene;
	float spawnTimer = 0;
};
