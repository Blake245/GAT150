#pragma once
// ** core **
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/ETime.h"
#include "Core/Json.h"
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Core/EString.h"

// ** systems **
// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
//input
#include "Input/Input.h"
//audio
#include "Audio/Audio.h"

// ** math **
#include "Math/Vector2.h"
#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Transform.h"

// ** framework **
#include "framework/Actor.h"
#include "Framework/Scene.h"
#include "Framework/Game.h"

// ** resources **
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// ** event system **
#include "Event/EventSystem.h"

// ** components **
#include "Components/TextureComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/EnginePhysicsComponent.h"
#include "Components/TextComponent.h"

// ** physics **
#include "Physics/Physics.h"

// ** third party **
#include <SDL.h>
#include <fmod.hpp>
#include <memory>

#define RENDERER g_engine.GetRenderer()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	Time& GetTime() { return *m_time; }
	ParticleSystem& GetPS() { return *m_ParticleSystem; }
	Physics& GetPhysics() { return *m_physics; }
	bool isQuit() { return quit; }
private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_ParticleSystem;
	std::unique_ptr<Physics> m_physics;
};


