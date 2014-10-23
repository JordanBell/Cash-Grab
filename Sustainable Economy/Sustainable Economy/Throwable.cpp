#include "Coin.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Resources.h"
#include <time.h>
#include <stdlib.h>
#include "Player.h"

Throwable::Throwable(int start_x, int start_y, int end_x, int end_y) 
	: Collidable(start_x, start_y), moving(true), speed(16), height(0), LOOP_SPEED(1)
{
	// Default hitbox values may be overriden later
	m_HitBox->w = 32;
    m_HitBox->h = 32;

	max_cycles = 8 * LOOP_SPEED;

	LaunchTo(end_x, end_y);
}

void Throwable::LaunchTo(int _x, int _y, int angleSuppression)
{
	// Coins spin faster in the air
	LOOP_SPEED = 1;
	max_cycles = 8 * LOOP_SPEED;

	moving = true;
	// Launch the coin towards the end coordinates
	start.x = x;
	start.y = y;
	end.x = _x;
	end.y = _y;
	
	//Initialise the kinematics fields
	InitKin(angleSuppression);
}

void Throwable::InitKin(int angleSuppression)
{
	/* Compute Planar Velocities (horizontal & vertical) */

	// Calculate the angle of the trajectory
	if (ADAPT_ANGLE) angle = ComputeAngleForDistance();
	else
	{
		// Get a reasonably random angle
		if (angleSuppression <= 0)
			angle = (rand() % 14) + 75;
		else if (angleSuppression == 1)
			angle = (rand() % 10) + 70;
		else if (angleSuppression == 2)
			angle = 45;
		else if (angleSuppression == 3)
			angle = 30;
		else if (angleSuppression == 4)
			angle = 15;
		else if (angleSuppression >= 5)
			angle = 1;

		// Convert to radians
		angle *= (2 * M_PI) / 360;

		// Get the planar x and y velocities (planar being the movement in a 3D space, where y is vertical and x is horizontal
		speed = ComputeSpeedForDistance();
	}

	planar.x = speed * cos(angle);
	planar.y = speed * sin(angle);



	/* Computing Angle of horizontal planar motion */

	//The angle travelled along the floor in 2D space, from start to end
	bool aimingRight = start.x < end.x;
	bool aimingUp  = start.y > end.y;

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
		float relativeAngle = aimingUp ? THREEQ_ANGLE : RIGHT_ANGLE;
		relativeAngle = RIGHT_ANGLE;

		bool posPol = ((!aimingRight && !aimingUp) || (aimingRight && aimingUp));
		int polarity = posPol ? 1 : -1;
		
		alpha = relativeAngle + (polarity * alpha);
	}



	/* Initial Velocities */

	//Use previous information to calculate the velocity.
	angleInducedVelocity.x = planar.x * cos(alpha);
	angleInducedVelocity.y = planar.x * sin(aimingUp ? (alpha*-1) : alpha);

	// Determine the on-screen velocities
	velocity.x = angleInducedVelocity.x;
	velocity.y = angleInducedVelocity.y + (planar.y * -3/4); // Multiply by a negative as the axis for the coordinates are swapped
} 

float Throwable::ComputeAngleForDistance()
{
	float r_angle;

	float distance = DistanceToEnd();
	
	r_angle = asin((distance * gravityStruct.norm) / (speed * speed));
	r_angle = M_PI - r_angle;
	r_angle /= 2;

	if (!(r_angle > 0)) printf("Error with coin, sent to (0, 0). Coin launch strength not strong enough to reach position (%f, %f)", end.x, end.y);
	
	return r_angle;
}

float Throwable::ComputeSpeedForDistance()
{
	float r_speed;

	float distance = DistanceToEnd();

	r_speed = sqrt( (distance * gravityStruct.norm) / sin(2*angle) );
	return r_speed;
}

float Throwable::DistanceToEnd()
{
	//Angle of horizontal movement, with regards to the horizontal of the screen.
	bool aimingRight = start.x < end.x;

	float dy = end.y - start.y; //The difference in y coordinates from start to end.
	float dx = aimingRight ? (end.x - start.x) : (start.x - end.x); // The difference in x coordinates from start to end.

	return sqrt(dy*dy + dx*dx);
}

float Throwable::ComputeVariableGravity()
{
	// It's a cold, hard equation. Just plug in the values.
	return (gravityStruct.gravityConstant * height * height / (speed * speed * sin(angle) * sin(angle)) + gravityStruct.mid) * /* Subtract a bit, because science */ (0.85 - 0.2);
}

void Throwable::update(int delta)
{
	if (moving) move();
    else
    {
        x = end.x;
        y = end.y;
    }

    Collidable::update(delta);
}

void Throwable::move()
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
		LOOP_SPEED = 6; // Coins spin slower on the ground
		max_cycles = 8 * LOOP_SPEED;
		velocity.x = velocity.y = planar.x = planar.y = 0; //Stop all movement
	}
}