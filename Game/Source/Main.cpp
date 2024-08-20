#include "Engine.h"
#include "Components/PlayerComponent.h"
#include <iostream>
#include <vector>

void func1(int i) { std::cout << "Still broken: " << i << std::endl; }
void func2(int i) { std::cout << "Still broken part 2: " << i << std::endl; }

int main(int argc, char* argv[])
{
	void(*fp)(int);

	fp = &func1;
	fp(5);

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();


	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	/*std::string s;
	File::ReadFile("Scenes/scene.json", s);
	std::cout << s;*/

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();


	{
		// create texture
		//std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		//texture->Load("sword.png", engine->GetRenderer());

		/*res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Sword.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("ArcadeClassic.ttf", 20);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Sup", { 1, 0, 1, 1 });

		Transform t{ {300, 300} };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->transform = Transform{ {30, 30} };
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));*/

		while (!engine->isQuit())
		{
			//update
			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			auto* actor = scene->GetActor<Actor>();
			if (actor)
			{
				actor->transform.rotation += engine->GetTime().GetDeltaTime();
			}

			// render
			engine->GetRenderer().SetColor(100, 100, 100, 0);
			engine->GetRenderer().BeginFrame();

			//draw
			scene->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}
	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}