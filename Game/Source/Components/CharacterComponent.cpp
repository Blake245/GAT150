#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)


void CharacterComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void CharacterComponent::Update(float dt)
{
	bool onGround = (groundCount > 0);
	Vector2 direction{ 0, 0 };

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

	float modifier = (onGround) ? 1 : 0.5f;
	physics->ApplyForce(direction * speed * 10 * modifier);

	// jump
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && onGround)
	{
		//physics->SetVelocity({ 0, -1000 });
		physics->ApplyForce({ 0, -7000 * 15 });
		animation->SetAnimation("jump");
	}
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_F))
	{
		animation->SetAnimation("attack");
	}

	if (physics->velocity.x < -0.1) animation->hflip = true;
	else if (physics->velocity.x > 0.1) animation->hflip = false;

	if (Math::Abs(physics->velocity.x) > 1) animation->SetAnimation("run");
	else animation->SetAnimation("idle");

	if (physics->velocity.y > 0.1f) animation->SetAnimation("fall");
	else if (physics->velocity.y < -0.1f) animation->SetAnimation("jump");

	rocketTimer -= dt;
	if (owner->scene->engine->GetInput().GetMouseButtonDown(0) && !owner->scene->engine->GetInput().GetPrevMouseButtonDown(0) && rocketTimer <= 0)
	{
		auto bullet = Factory::Instance().Create<Actor>("rocket");
		bullet->transform.position = owner->transform.position - 32;
		owner->scene->AddActor(std::move(bullet), true);

		rocketTimer = 0.5;
	}
}

void CharacterComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "Ground") groundCount++;
}

void CharacterComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "Ground") groundCount--;
}

void CharacterComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void CharacterComponent::Write(json_t& value)
{

}