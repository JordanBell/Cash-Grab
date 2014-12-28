#pragma once
#include "Collidable.h"
#include "PhysicsObject.h"
#include <list>

using namespace std;

class Throwable : public Collidable, public PhysicsObject, public Sprite
{
public:
	static list<Throwable*> ThrowablesAround(const int x, const int y, const int radius);
	static list<Throwable*> ThrowablesAroundPlayer(const int radius);

	Throwable(int start_x, int start_y, int end_x, int end_y);
	~Throwable(void);

	virtual void Update(int delta);
	virtual void OnCollect(void) = 0; // A throwable's effect when collected
	void BounceUp(void);

	void SetHoming(int distance, int speed) { m_homingDistance = distance; m_homingSpeed = speed; }
	void SetBouncy(bool bouncy) { m_isBouncy = bouncy; }

protected:

	// Adjust the animation speed, and handle other animation related changes accordingly
	void SetAnimationSpeed(const int newSpeed);
	
	const int GetAnimationSpeed(void) const { return m_animationSpeed; }
	
	// The number of sprites in the animation
	int m_numSprites;

private:
	// Effect variables
	int m_homingDistance; // The distance at which the throwable will stop homing
	float m_homingSpeed; // The pixels by which the throwable homes in each frame
	bool m_isBouncy;
	
	// The animation speed - [higher -> slower] and [lower -> faster]
	int m_animationSpeed;

	// Adjust coordinates for homing
	void HomeTowardPlayer(void);
};

extern list<Throwable*> g_throwables;
