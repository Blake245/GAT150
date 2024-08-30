#include "SpaceGame.h"
#include "Engine.h"
#include <memory>

bool SpaceGame::Initialize()
{
	m_scene = std::make_unique<Scene>(m_engine);
	//"Scenes/tilemap.json", "Scenes/game.json"
	std::string sceneNames[] = {"Scenes/titlescreen.json"};
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
	m_scene->RemoveAll(true);
}

void SpaceGame::Update(float dt)
{
	/*auto bat = Factory::Instance().Create<Actor>("bat");
	bat->transform.position = Vector2{ randomf(800), randomf(600) };
	m_scene->AddActor(std::move(bat), true);*/
	std::string sceneNames[] = { "Scenes/tilemap.json", "Scenes/game.json", "Scenes/ui.json"};

	switch (state)
	{
	case SpaceGame::eState::TITLE:
		//owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)
		if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_scene->RemoveAll(true);
			state = eState::START_LEVEL;
		}
		break;
	case SpaceGame::eState::START_LEVEL:
		for (auto sceneName : sceneNames)
		{
			rapidjson::Document document;
			Json::Load(sceneName, document);
			m_scene->Read(document);
		}

		m_scene->Initialize();


		spawnTimer = 2;
		state = eState::GAME;
		break;
	case SpaceGame::eState::GAME:
		spawnTimer -= dt;
		if (spawnTimer <= 0)
		{
			auto bat = Factory::Instance().Create<Actor>("bat");
			bat->transform.position = Vector2{ randomf(32, 768), randomf(10, 300) };
			m_scene->AddActor(std::move(bat), true);

			auto skeleton = Factory::Instance().Create<Actor>("skeleton");
			skeleton->transform.position = Vector2{32, 400 };
			m_scene->AddActor(std::move(skeleton), true);
			
			spawnTimer = 2;
		}
		break;
	case SpaceGame::eState::GAME_OVER:
		//
		break;
	default:
		break;
	}

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
	std::string str = "score       " + std::to_string(m_score);

	auto score = m_scene->GetActor<Actor>("score");
	score->GetComponent<TextComponent>()->SetText(str);
}
