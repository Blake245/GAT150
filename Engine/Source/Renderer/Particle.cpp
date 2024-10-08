#include "Particle.h"

void Particle::Initialize(const Data& data)
{
	isActive = true;
	position = data.position;
	velocity = data.velocity;
	lifespan = data.lifespan;
	r = data.r;
	g = data.g;
	b = data.b;
	a = data.a;
}

void Particle::Update(float dt)
{
	position = position + (velocity * dt);
	if (lifespan != 0) lifespan -= dt;
	if (lifespan <= 0) isActive = false;
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0)
	{
		//renderer.DrawPoint(position.x, position.y);
		renderer.SetColor(r, g, b, a);
		renderer.DrawRect(position.x, position.y, 2.0f, 2.0f);
	}
}
