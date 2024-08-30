#include "SkeletonComponent.h"
#include "Engine.h"

FACTORY_REGISTER(SkeletonComponent)

void SkeletonComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&SkeletonComponent::OnCollisionEnter, this, std::placeholders::_1);
	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void SkeletonComponent::Update(float dt)
{
	physics->SetVelocity(owner->transform.Forward() * speed);

	if (physics->velocity.x < -0.1) animation->hflip = true;
	else if (physics->velocity.x > 0.1) animation->hflip = false;
}

void SkeletonComponent::OnCollisionEnter(Actor* actor)
{

	/*EVENT_NOTIFY(PlayerDead)
	EVENT_NOTIFY_DATA(AddPoints, 100)*/
}

void SkeletonComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void SkeletonComponent::Write(json_t& value)
{
	//
}
