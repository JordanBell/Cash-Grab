#pragma once
#include "PhysicsObject.h"
#include "ToolKit.h"
#include "Game.h"
#include <list>

class ParticleSimple :
	public PhysicsObject
{
public:
	ParticleSimple(int start_x, int start_y, int end_x, int end_y);
	~ParticleSimple(void);

	// Change the color of the particle surface
	void SetColor(const Uint32 color);
	
	// Render this particle on screen
	void Render(void) { apply_surface(m_pos.x, m_pos.y, m_surface, screen); }

protected:
	// When the particle has landed, remove it // TODO: Or, create a timer that fades it out
	void OnLanding(void) override { /* g_game->removeEntity(this); */ }

private:
	Dimensions m_size;
	SDL_Surface* m_surface;
};

typedef ParticleSimple Particle;

extern std::list<Particle*> g_particles;
