#include "Engine.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();

	//ResourceManager rm = ResourceManager();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;
	{
		// create texture
		//std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		//texture->Load("sword.png", engine->GetRenderer());

		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Sword.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("ArcadeClassic.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Sup", { 1, 1, 0, 1 });

		Transform t{ {300, 300} };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->isQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(255, 255, 255, 0);
			engine->GetRenderer().BeginFrame();

			// draw texture
			engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
			text->Draw(engine->GetRenderer(), 200, 200);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}