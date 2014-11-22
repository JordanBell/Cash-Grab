#include "ParticleSimple.h"

std::list<Particle*> g_particles;

ParticleSimple::ParticleSimple(int start_x, int start_y, int end_x, int end_y) 
		: PhysicsObject(start_x, start_y, end_x, end_y), GameObject(start_x, start_y), m_size(3, 3) 
{ 
	Uint32 color = 0xFF705030; // Soft brown
	
	// Create a square surface of this particle's color and size TODO: Create all surfaces in video memory (HWSURFACE)
	m_imageSurface = SDL_CreateRGBSurface(0, m_size.x, m_size.y, 32,
									 0,0,0,0);
	SetColor(color);
	
	// Set render priority above coins TODO: Dynamically change the render priority of coins and particles when they launch and land
	m_renderPriority = 3;

	g_game->addGameObject(this);
}

ParticleSimple::~ParticleSimple(void) 
{ 
	printf("Deleting particle.\n"); 
	SDL_FreeSurface(m_imageSurface);
}

void ParticleSimple::SetColor(const Uint32 color)
{
	// Lock the surface
	/*if (SDL_MUSTLOCK(m_surface))
		SDL_LockSurface(m_surface);*/

	// Change the pixels to the new color
	SDL_FillRect(m_imageSurface, NULL, color);

	// Unlock the surface
	/*if (SDL_MUSTLOCK(m_surface))
		SDL_UnlockSurface(m_surface);*/
}

