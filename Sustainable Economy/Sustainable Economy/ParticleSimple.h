#pragma once
#include "PhysicsObject.h"

class ParticleSimple :
	public PhysicsObject
{
public:
	ParticleSimple(int start_x, int start_y, int end_x, int end_y) 
		: PhysicsObject(start_x, start_y, end_x, end_y) { }

	// Set the color of this particle
	//void SetColor(SDL_Color particleColor) { m_color = particleColor; }
	
	void render(void);

private:
	//SDL_Color m_color;
};

