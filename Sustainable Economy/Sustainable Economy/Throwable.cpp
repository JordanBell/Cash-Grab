#include "Coin.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Resources.h"
#include <time.h>
#include <stdlib.h>
#include "Player.h"

#define HOMING_THRESHOLD 450.0f
#define HOMING_SPEED 1.0f

list<Throwable*> g_throwables;

Throwable::Throwable(int start_x, int start_y, int end_x, int end_y) 
	: Collidable(start_x, start_y), PhysicsObject(start_x, start_y, end_x, end_y), m_homingDistance(0), m_homingSpeed(0), m_isBouncy(false)
{
	g_throwables.push_back(this);

	// Default hitbox values may be overriden later
	m_HitBox->w = 32;
    m_HitBox->h = 32;

	// Set the highest render priority for throwables
	m_renderPriority = 2;
}

Throwable::~Throwable(void) 
{ 
	g_throwables.remove(this); 
}

void Throwable::BounceUp(void)
{
	/// Repeat code from LaunchTo
    /*cycle /= LOOP_SPEED;
	LOOP_SPEED = 1;
	max_cycles = 8 * LOOP_SPEED;*/

	//moving = true;
	// Launch the coin towards the end coordinates
	/*start.x = x;
	start.y = y;
	end.x = x;
	end.y = y;*/
	
	//Initialise the kinematics fields
	Launch(-1, (rand()%15) + 5);
}

list<Throwable*> Throwable::ThrowablesAround(const int px, const int py, const int radius)
{
	list<Throwable*> r_throwables;

	for (Throwable* t : g_throwables)
	{
		if (!t->IsAirborne()) {
			const int dx = g_player->x - t->x;
			const int dy = g_player->y - t->y;
			const int distance = sqrt(dx*dx + dy*dy);

			if (distance <= radius)
				r_throwables.push_back(t);
		}
	}

	return r_throwables;
}

list<Throwable*> Throwable::ThrowablesAroundPlayer(const int radius) 
{ 
	return
		ThrowablesAround(g_player->x, g_player->y, radius); 
}

void Throwable::HomeTowardPlayer(void)
{
	// Home in on player
	SDL_Rect playerCenter = g_player->GetCenter();
	SDL_Rect thisCenter = this->GetCenter();

	XY dif;
	dif.x = (playerCenter.x - thisCenter.x);
	dif.y = (playerCenter.y - thisCenter.y);

	float angle = atan(dif.y / dif.x);

	XY vel;
	float distance = sqrt(dif.x*dif.x + dif.y*dif.y);

	vel.x = m_homingSpeed * cos(angle);
	vel.y = m_homingSpeed * sin(angle);

	// Trigonometry is unkind; here's a lazy fix
	vel.x *= (dif.x < 0) ? -1 : 1;
	vel.y *= (dif.x < 0) ? -1 : 1;

	// Change position based on velocity
	x += vel.x;
	y += vel.y;
		
	// Stop homing if out of range.
	if (distance > m_homingDistance)
		m_homingDistance = 0;
}

void Throwable::SetAnimationSpeed(const int newSpeed)
{
	// Set the cycle: decode the old speed, encode the new one
    //cycle *= newSpeed / m_animationSpeed;
    cycle = 0;

	// Set the new speed
	m_animationSpeed = newSpeed;

	// Adjust number of cycles accordingly
	max_cycles = m_numSprites * m_animationSpeed;
}

void Throwable::update(int delta)
{
	if (m_airborne) 
	{
		PhysicsObject::MoveUpdate();

		// Take on the position calculated as a physics object
		x = m_pos.x;
		y = m_pos.y;
	}
	else if (m_isBouncy) 
		BounceUp();
    else if (m_homingDistance > 0)
		HomeTowardPlayer();
	else
		m_homingDistance = 0;


    Collidable::update(delta);
}