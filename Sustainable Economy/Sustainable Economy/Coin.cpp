#include "Coin.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Resources.h"
#include <time.h>
#include <stdlib.h>

Coin::Coin(int start_x, int start_y, int end_x, int end_y) : Collidable(start_x, start_y), moving(true), speed(16), height(0), LOOP_SPEED(1)
{ 
	sprite_sheet = g_resources->GetCoinSheet();
	m_HitBox->w = 16;
    m_HitBox->h = 16;

	max_cycles = 8 * LOOP_SPEED;

	// Coordinates
	start.x = start_x;
	start.y = start_y;
	end.x = end_x;
	end.y = end_y;

	//Initialise the clips of the sprite_sheet
	InitSheet();
	
	//Initialise the kinematics fields
	InitKin();
}

void Coin::InitSheet()
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();
		
		clip->x = TILE_SIZE * i;
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}

void Coin::InitKin()
{
	ComputeInitPlanar();
	ComputeInitXAngle();
	ComputeInitVelocities();
}

void Coin::ComputeInitPlanar(void)
{
	// Calculate the angle of the trajectory
	if (ADAPT_ANGLE) angle = ComputeAngleForDistance();
	else
	{
		// Get a reasonably random angle
		angle = (rand() % 14) + 75;
		angle *= (2 * M_PI) / 360;

		// Get the planar x and y velocities (planar being the movement in a 3D space, where y is vertical and x is horizontal
		speed = ComputeSpeedForDistance();
	}

	planar.x = speed * cos(angle);
	planar.y = speed * sin(angle);
} 

void Coin::ComputeInitXAngle(void)
{
	//Angle of horizontal movement, with regards to the horizontal of the screen.
	bool aimingRight = start.x < end.x;

	float dy = end.y - start.y; //The difference in y coordinates from start to end.
	float dx = aimingRight ? (end.x - start.x) : (start.x - end.x); // The difference in x coordinates from start to end.

	// Calculate the alpha (angle between start and end points)
	if (dy == 0) // Avoid division by 0
	{ 
		alpha = aimingRight ? 0 : HALF_ANGLE; 
	}
	else // Continue as planned
	{
		alpha = atan(dx / dy);
		alpha = aimingRight ? (RIGHT_ANGLE - alpha) : (RIGHT_ANGLE + alpha);
	}
}

void Coin::ComputeInitVelocities(void)
{
	//Use previous information to calculate the velocity.
	angleInducedVelocity.x = planar.x * cos(alpha);
	angleInducedVelocity.y = planar.x * sin(alpha);

	// Determine the on-screen velocities
	velocity.x = angleInducedVelocity.x;
	velocity.y = angleInducedVelocity.y + (planar.y* -3/4); // Multiply by a negative as the axis for the coordinates are swapped
}

float Coin::ComputeAngleForDistance()
{
	float r_angle;

	float distance = DistanceToEnd();
	
	r_angle = asin((distance * gravityStruct.norm) / (speed * speed));
	r_angle = M_PI - r_angle;
	r_angle /= 2;

	if (!(r_angle > 0)) printf("Error with coin, sent to (0, 0). Coin launch strength not strong enough to reach position (%f, %f)", end.x, end.y);
	
	return r_angle;
}

float Coin::ComputeSpeedForDistance()
{
	float r_speed;

	float distance = DistanceToEnd();

	r_speed = sqrt( (distance * gravityStruct.norm) / sin(2*angle) );
	return r_speed;
}

float Coin::DistanceToEnd()
{
	//Angle of horizontal movement, with regards to the horizontal of the screen.
	bool aimingRight = start.x < end.x;

	float dy = end.y - start.y; //The difference in y coordinates from start to end.
	float dx = aimingRight ? (end.x - start.x) : (start.x - end.x); // The difference in x coordinates from start to end.

	return sqrt(dy*dy + dx*dx);
}

float Coin::ComputeVariableGravity()
{
	// It's just a cold, hard equation. Just plug in the values.
	return (gravityStruct.gravityConstant * height * height / (speed * speed * sin(angle) * sin(angle)) + gravityStruct.mid) * /* Subtract a bit, because science */ (0.85 - 0.2);
}

void Coin::update(int delta)
{
    IncCycle();
	
	if (moving) move();
	else
	{
		x = end.x;
		y = end.y;
        moving = false;
	}
    
    Collidable::update(delta);
}

void Coin::move()
{
	//planar.y changes based on gravity
	if (VARY_GRAVITY) planar.y -= ComputeVariableGravity();
	else planar.y -= gravityStruct.norm;
	// Keep track of the height, to know when the coin has landed
	height += planar.y;

	// Update velocity and position values
	velocity.y = angleInducedVelocity.y + (planar.y* -3/4);
	x += velocity.x;
	y += velocity.y;

	if (height < 0) //Has hit the ground
	{
		moving = false;
		LOOP_SPEED = 6;
		max_cycles = 8 * LOOP_SPEED;
		velocity.x = velocity.y = planar.x = planar.y = 0; //Stop all movement
	}
}