#include "ParticleSimple.h"
#include "Resources.h"

std::list<Particle*> g_particles;
std::list<Particle*> ParticleSimple::s_instanceList;
Uint32 ParticleSimple::s_color = 0x00655c5c; // Tile-ish
//Uint32 ParticleSimple::s_color = 0x00705030; // Soft brown
//Uint32 ParticleSimple::s_color = 0x0066CCCC; // Blue
//Uint32 ParticleSimple::s_color = 0x00237556; // Blue

#define INSTANCE_LIMIT 1000000
#define AGE_LIMIT 10
#define FADE_LENGTH 35

ParticleSimple::ParticleSimple(int end_x, int end_y, int height) 
		: PhysicsObject(end_x, end_y, height), GameObject(end_x, end_y-height), m_size(3, 3), m_fadeCounter(FADE_LENGTH), m_age(0), m_AgeLimit(AGE_LIMIT)
{ 
	// Create a square surface of this particle's color and size TODO: Create all surfaces in video memory (HWSURFACE)
	m_imageSurface = SDL_CreateRGBSurface(0, m_size.x, m_size.y, 32,
									 0,0,0,0);
	SetColor(s_color);

	//m_imageSurface = g_resources->GetSpeedParticle();
	
	// Set render priority above coins
	m_renderPriority = LAYER_AIR;

	s_instanceList.emplace_back(this);
}

ParticleSimple::ParticleSimple(int start_x, int start_y, int end_x, int end_y) 
		: PhysicsObject(start_x, start_y, end_x, end_y), GameObject(start_x, start_y), m_size(3, 3), m_fadeCounter(FADE_LENGTH), m_age(0)
{ 
	
	// Create a square surface of this particle's color and size TODO: Create all surfaces in video memory (HWSURFACE)
	m_imageSurface = SDL_CreateRGBSurface(0, m_size.x, m_size.y, 32,
									 0,0,0,0);
	SetColor(s_color);

	//m_imageSurface = g_resources->GetSpeedParticle();
	
	// Set render priority above coins
	m_renderPriority = LAYER_AIR;

	s_instanceList.emplace_back(this);
}

void ParticleSimple::StartFade(void)
{
	// Remove this from the static list
	s_instanceList.pop_front();

	// The start of the fade is triggered by a fade counter != FADE_LENGTH
	m_fadeCounter--;
}

void ParticleSimple::Render(void)
{
	// Find the rendering rectangle based on position and size.
	//SDL_Rect renderRect = { x + s_renderingOffset_x, y + s_renderingOffset_y, m_size.x, m_size.y };

	// Fill the rect onto the screen - cheaper than blitting a surface
	//SDL_FillRect(screen, &renderRect, m_color);
	
	// SDL_FillRect(m_imageSurface, NULL, color);
	// Normal GameObject rendering
	apply_surface(x, y, m_imageSurface, screen, m_imageRect);
}


void ParticleSimple::Update(int delta) 
{ 
	// Update the PhysicsObject portion
	PhysicsObject::MoveUpdate();

	// Update the GameObject portion
	GameObject::Update(delta); 
	
	// Sync GameObject position with PhysicsObject position
	x = m_pos.x; 
	y = m_pos.y; 

	// Increment age
	if (!this->IsAirborne())
		m_age++;

	// Check if a fade has started
	if (m_fadeCounter == FADE_LENGTH)
	{
		// Check to see if this should be removed
		bool isTooOld = !m_airborne && (m_age >= m_AgeLimit);

		// Fade if too old
		if (isTooOld)
			StartFade();
		else 
		{
			// Check to see if the instance limit had been reached
			bool limitReached = (s_instanceList.size() > INSTANCE_LIMIT);
			bool isFront = (s_instanceList.front() == this);

			// Fade away if so
			if (limitReached && isFront)
				StartFade();
		}
	}
	else if (m_fadeCounter == 0)
	{
		g_game->removeGameObject(this);
	}
	else // Between the max (FADE_LENGTH) and minimum (0)
	{
		// Decrement counter
		m_fadeCounter--;

		// Change the alpha value of the rect
		float alphaPercentage = (float)m_fadeCounter / (float)FADE_LENGTH;
		Uint8 newAlpha = alphaPercentage * 0xFF;
		SDL_SetAlpha(m_imageSurface, SDL_SRCALPHA | SDL_RLEACCEL, newAlpha);
	}

}