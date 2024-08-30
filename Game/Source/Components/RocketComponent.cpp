
#include "Engine.h"
#include "RocketComponent.h"
#include "Components/Box2DPhysicsComponent.h"

FACTORY_REGISTER(RocketComponent)

void RocketComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&RocketComponent::OnCollisionEnter, this, std::placeholders::_1);
	physics = owner->GetComponent<PhysicsComponent>();

	// sets angle of rocket to mouse position
	Vector2 mousePostion = owner->scene->engine->GetInput().GetMousePosition();
	angle = Math::Atan2(mousePostion.y - owner->transform.position.y, mousePostion.x - owner->transform.position.x);
	angle = Math::RadToDeg(angle);
	std::cout << mousePostion.x << " " << mousePostion.y << std::endl;
}

void RocketComponent::Update(float dt)
{
	owner->transform.rotation = angle;
	physics->SetVelocity(owner->transform.Forward() * speed);
}

void RocketComponent::OnCollisionEnter(Actor* actor)
{
	if (!actor->destroyed && (actor->tag == "enemy"))
	{
		actor->destroyed = true;
		owner->destroyed = true;
	}
	if (actor->tag == "Ground")
	{
		owner->destroyed = true;
	}

}

void RocketComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void RocketComponent::Write(json_t& value)
{
}