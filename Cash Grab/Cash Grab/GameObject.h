#pragma once
#include "toolkit.h"

/*
A GameObject is an interface for an object that is both Updateable and Renderable
*/
class GameObject
{
protected:
	// The image surface that is rendered
	SDL_Surface* m_imageSurface;
	
	// The portion of the image that is rendered
	SDL_Rect* m_imageRect;

	// All active GameObjects are ordered by their renderPriority before the rendering process, allowing for render layering.
	int m_renderPriority;

public:
	// Construct a GameObject
	GameObject(int x, int y) 
		: m_renderPriority(1), m_imageRect(nullptr), x(x), y(y) {}

	// Destruct the GameObject
	virtual ~GameObject(void) {
        if (m_imageRect) {
            delete m_imageRect;
        }
    }

	// Position variables
	float x, y;

	// Update the data in this object. Called on each run of the game cycle.
	virtual void Update(int delta) {};

	// Render this object on the screen. Called on each run of the game cycle.
	virtual void Render(void) { apply_surface(x, y, m_imageSurface, screen, m_imageRect); }

	const int GetRenderPriority(void) const { return m_renderPriority; }

	// Get the center of this GameObject's image
	const SDL_Rect GetCenter(void);
};

