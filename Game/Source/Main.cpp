#include "Engine.h"

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());

	//auto a = Factory::Instance().Create("Actor");

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();

	//ResourceManager rm = ResourceManager();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	std::string s;
	File::ReadFile("json.txt", s);
	std::cout << s;

	rapidjson::Document document;
	Json::Load("json.txt", document);

	std::string name;
	int age;
	bool isAwake;
	Vector2 position;
	Color color;
	
	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);

	Json::Read(document, "age", age);
	Json::Read(document, "name", name);
	Json::Read(document, "isAwake", isAwake);
	Json::Read(document, "position", position);
	Json::Read(document, "color", color);
	std::cout << age << std::endl;
	std::cout << name << std::endl;
	std::cout << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << " " << std::endl;

	{
		// create texture
		//std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		//texture->Load("sword.png", engine->GetRenderer());

		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Sword.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("ArcadeClassic.ttf", 20);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Sup", { 1, 0, 1, 1 });

		Transform t{ {300, 300} };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(t);
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->isQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(100, 100, 100, 0);
			engine->GetRenderer().BeginFrame();

			// draw texture
			engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
			actor->Draw(engine->GetRenderer());
			text->Draw(engine->GetRenderer(), 500, 200);

			engine->GetRenderer().EndFrame();
		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}