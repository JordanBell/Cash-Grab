#pragma once
#include "gameobject.h"

class Sprite :
	public GameObject
{
public:
	//Constructors
	Sprite(const int x, const int y) : GameObject(x, y), m_cycle(0) {}
	virtual ~Sprite(void) {}

	virtual void Update(int delta) { IncCycle(); UpdateImageRect(); }
	const int GetRenderPriority(void) const { return m_renderPriority; }

protected:
	//The Delay before cycling through each sprite. Make smaller to speed up the animation
	int m_animationDelay;

	// An incremented counter cycle used in animation
	int m_cycle;

	// The max number of cycles during animation
	int m_maxCycles;
	
	// Called by Sprite constructor, to be overridden by Sprite subclasses
	virtual void InitSprites(void) = 0;

	virtual void IncCycle(void) { m_cycle = (m_cycle >= (m_maxCycles-1)) ? 0 : m_cycle+1; }
	virtual void UpdateImageRect(void) { m_imageRect = nullptr; }
};

