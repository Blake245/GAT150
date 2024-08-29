#pragma once
#include "Components/Component.h"

class RocketComponent : public Component
{
public:
	CLASS_DECLARATION(RocketComponent)
	CLASS_PROTOTYPE(RocketComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

public:
	float speed{ 0 };

	class PhysicsComponent* physics{ nullptr };

	Vector2 direction{ 0, 0 };
	float angle = 0;

};
