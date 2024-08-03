#pragma once
// ** core **
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/ETime.h"

// ** systems **
// renderer
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"
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
	bool isQuit() { return quit; }
private:
	bool quit{ false };

	std::unique_ptr<Time> m_time;
	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_ParticleSystem;
};


