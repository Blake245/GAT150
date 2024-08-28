#include "SpaceGame.h"
#include "Engine.h"
#include <memory>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);

	std::string sceneNames[] = {"Scenes/tilemap.json", "Scenes/game.json"};
	for (auto sceneName : sceneNames)
	{
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);
	}

	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead)
	ADD_OBSERVER(AddPoints, SpaceGame::OnAddPoints)

    return false;
}

void SpaceGame::Shutdown()
{
	m_scene->RemoveAll();
}

void SpaceGame::Update(float dt)
{
	/*auto bat = Factory::Instance().Create<Actor>("bat");
	bat->transform.position = Vector2{ randomf(800), randomf(600) };
	m_scene->AddActor(std::move(bat), true);*/

	m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	std::cout << "game player dead\n";
}

void SpaceGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
}
