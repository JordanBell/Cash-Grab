#include "GameObject.h"

const SDL_Rect GameObject::GetCenterRect(void) 
{ 
	// Skin width and height, depending on whether or not it's
	int skinW, skinH;
	skinW = m_imageRect ? m_imageRect->w : m_imageSurface->w;
	skinH = m_imageRect ? m_imageRect->h : m_imageSurface->h;

	// The position, held within a rect object
	const SDL_Rect pos = {static_cast<Sint16>(x+(skinW/2)), static_cast<Sint16>(y+(skinH/2)), 0, 0};
	return pos; 
}

const Position GameObject::GetCenter(void) 
{ 
	// Skin width and height, depending on whether or not it's
	int skinW, skinH;
	skinW = m_imageRect ? m_imageRect->w : m_imageSurface->w;
	skinH = m_imageRect ? m_imageRect->h : m_imageSurface->h;

	// The position, held within a rect object
	return Position(x + (skinW/2), y + (skinH/2)); 
}