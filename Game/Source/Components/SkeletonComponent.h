#pragma once
#include "Components/Component.h"

class SkeletonComponent : public Component
{
public:
	CLASS_DECLARATION(SkeletonComponent)
	CLASS_PROTOTYPE(SkeletonComponent)

	void Initialize() override;

	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

public:
	float speed{ 0 };

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };

};
