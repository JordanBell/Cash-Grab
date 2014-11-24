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
	~ParticleSimple(void) { SDL_FreeSurface(m_imageSurface); s_instanceList.remove(this); }

	// Change the color of the particle surface
	void SetColor(const Uint32 color) { SDL_FillRect(m_imageSurface, NULL, color); }
	void Update(int delta) override;

protected:
	// When the particle has landed, change its render priority
	void OnLanding(void) override { m_renderPriority = LAYER_GROUND; }

private:
	Dimensions m_size;
	int m_fadeCounter;
	int m_age;

	static std::list<ParticleSimple*> s_instanceList;
	static Uint32 s_color; // Soft brown

	void StartFade(void);
};

typedef ParticleSimple Particle;

extern std::list<Particle*> g_particles;
