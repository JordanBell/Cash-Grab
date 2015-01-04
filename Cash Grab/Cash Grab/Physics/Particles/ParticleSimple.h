#pragma once
#include "PhysicsObject.h"
#include "ToolKit.h"
#include "Game.h"
#include <list>

class ParticleSimple :
	public PhysicsObject, public GameObject
{
public:
	ParticleSimple(int end_x, int end_y, int height);
	ParticleSimple(int start_x, int start_y, int end_x, int end_y);
    virtual ~ParticleSimple(void) { SDL_FreeSurface(m_imageSurface); s_instanceList.remove(this); }

	// Change the color of the particle surface
	void Update(int delta) override;
	void Render(void) override;

protected:
	int m_AgeLimit;

	// When the particle has landed, change its render priority
	void OnLanding(void) override { m_renderPriority = LAYER_GROUND; }

	Uint32 GetColor(void) { return m_color; }
	Dimensions GetSize(void) { return m_size; }

	void SetColor(const Uint32 color) { SDL_FillRect(m_imageSurface, NULL, color); m_color = color; }
	void SetFadeLength(const int newLength) { m_fadeCounter = newLength; }
	void SetSize(const Dimensions& size) { m_size = size; m_imageSurface = SDL_CreateRGBSurface(0, m_size.x, m_size.y, 32, 0,0,0,0); SetColor(m_color); }
	void SetAgeLimit(int newLimit) { m_AgeLimit = newLimit; }

private:
	Dimensions m_size;
	int m_fadeCounter;
	int m_age;
	Uint32 m_color;

	static std::list<ParticleSimple*> s_instanceList;
	static Uint32 s_color; // Soft brown

	void StartFade(void);
};

typedef ParticleSimple Particle;

extern std::list<Particle*> g_particles;
