#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "Components/CollisionComponent.h"
#include <algorithm>

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();
	}
}


void Scene::Update(float dt)
{
	// update
	for (auto& actor : actors)
	{
		if (actor->active) actor->Update(dt);
	}

	// collision
	for (auto& actor1 : actors)
	{
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		if (collision1 == nullptr) continue;

		for (auto& actor2 : actors)
		{
			if (actor1 == actor2) continue;
			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if(collision1 == nullptr) continue;

			if (collision1->CheckCollision(collision2))
			{
				if (actor1->OnCollisionEnter) actor1->OnCollisionEnter(actor2.get());
				if (actor2->OnCollisionEnter) actor2->OnCollisionEnter(actor1.get());
			}
		}
	}

	// destroy
	// 
	// The std::remove_if algorithm reorders the elements in the range [m_actors.begin(), m_actors.end()]
	// such that the elements that satisfy the predicate (i.e., those that should be removed) are moved
	// to the end of the range. The algorithm returns an iterator to the beginning of the "removed" range,
	// which is the new logical end of the container.
	//m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](Actor* actor) {return actor->m_destroyed; }), m_actors.end());
	std::erase_if(actors, [](auto& actor) { return actor->destroyed; });
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{
		if(actor->active) actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	actors.clear();
}

void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}
