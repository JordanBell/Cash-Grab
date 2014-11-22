#pragma once
#include "PhysicsObject.h"
#include "ToolKit.h"
#include "Game.h"
#include <list>

class ParticleSimple :
	public PhysicsObject, GameObject
{
public:
	ParticleSimple(int start_x, int start_y, int end_x, int end_y);
	~ParticleSimple(void);

	// Change the color of the particle surface
	void SetColor(const Uint32 color);
	void Update(int delta) override { printf("Updating!"); x = m_pos.x; y = m_pos.y; PhysicsObject::MoveUpdate(); GameObject::Update(delta); }

protected:
	// When the particle has landed, remove it // TODO: Or, create a timer that fades it out
	void OnLanding(void) override { printf("Landed.\n"); g_game->removeGameObject(this); }

private:
	Dimensions m_size;
};

typedef ParticleSimple Particle;

extern std::list<Particle*> g_particles;
