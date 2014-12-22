#include "PhysicsObject.h"
#include <iostream>
#include <math.h>
#include <cmath>

void PhysicsObject::LaunchTo(int _x, int _y, int angleSuppression, int speedOverride)
{
	// Launch the coin towards the end coordinates
	m_endPos.x = _x;
	m_endPos.y = _y;

	// Main launch function - computes initial kinematics
	Launch(angleSuppression, speedOverride);
}

void PhysicsObject::Launch(int angleSuppression, int speedOverride)
{
	m_airborne = true;

	// Call any overridden OnLaunch code
	OnLaunch();
	
	// The spatial launch angle
	m_spatialKin.SetAngleBySuppression(angleSuppression);

	// The scalar launch speed
	int speed = (speedOverride >= 0)? speedOverride : ComputeSpeedForDistance();

	// Derive the velocity from the speed and angle
	m_spatialKin.SetVelocityFromScalar(speed);
	
	// Compute the on-screen angle of travel
	m_screenKin.angle = ComputeScreenAngle();
	
	/* This is hard to explain: Image this as the velocity of the object's shadow along 
	the ground. The x and y values are the components of the spatial horizontal velocities. */
	m_additiveScreenVelocity = XY (
		m_spatialKin.velocity.x * cos(m_screenKin.angle),
		m_spatialKin.velocity.x * sin((m_pos.y > m_endPos.y) ? (m_screenKin.angle*-1) : m_screenKin.angle)
	); 

		// Determine the on-screen velocities
	// X is mapped directly as it is on screen
	m_screenKin.velocity.x = m_additiveScreenVelocity.x;

	/* 
	* Y is what you'd expect: 
	* The y component of the horiztonal spatial velocity, 
	* plus a fraction of the spatial vertical velocity
	*/
	m_screenKin.velocity.y = m_additiveScreenVelocity.y + (m_spatialKin.velocity.y * -3/4); 
}

void PhysicsObject::Drop(void)
{
	m_airborne = true;

	// Set spatial stats
	m_spatialKin.height = m_DropHeight;
	m_spatialKin.velocity.x = m_spatialKin.velocity.y = 0;
	
	// Compute the on-screen angle of travel
	m_screenKin.angle = ComputeScreenAngle();
	
	m_additiveScreenVelocity = XY (0, 0); 

	// Determine the on-screen velocities
	m_screenKin.velocity.x = m_additiveScreenVelocity.x;
	m_screenKin.velocity.y = m_additiveScreenVelocity.y + (m_spatialKin.velocity.y * -3/4); // Multiply by a negative as the axis for the coordinates are swapped
}

const float PhysicsObject::ComputeScreenAngle(void) const
{
	// Get the angle travelled along the floor in 2D space, from start to end
	bool aimingRight = m_pos.x < m_endPos.x;
	bool aimingUp	 = m_pos.y > m_endPos.y;

	float dy = m_endPos.y - m_pos.y; //The difference in y coordinates from start to end.
	float dx = aimingRight ? (m_endPos.x - m_pos.x) : (m_pos.x - m_endPos.x); // The difference in x coordinates from start to end.

	// Calculate the screen angle (angle between start and end points on screen)
	if (dy == 0) // Avoid division by 0
	{ 
		return (aimingRight ? 0 : HALF_ANGLE); 
	}
	else // Continue as planned
	{
		float trigAngle = atan(dx / dy);

		int anglePolarity = (aimingRight == aimingUp) ? 1 : -1;
		return (RIGHT_ANGLE + (anglePolarity * trigAngle));
	}
}

const float PhysicsObject::ComputeDistanceToEnd(void) const
{
	const float dx = m_endPos.x - m_pos.x; // The difference in x coordinates from start to end.
	const float dy = m_endPos.y - m_pos.y; // The difference in y coordinates from start to end.

	return sqrt(dx*dx + dy*dy);
}

const float PhysicsObject::ComputeSpeedForDistance(void) const
{
	/*
	Let's walk through how this works. If we're computing a speed needed to reach a distance, we are calculating how 
	hard throw ourselves into the air. Our airtime dermines how far we go. How far we go is determined by the start 
	and end positions - those we know.	So airtime is the main factor here. Time spent in the air before we hit the 
	ground is determined by the vertical spatial velocity. 
	
	Gravity decreases the vertical velocity, which eventually starts to move the object to the ground. Once it does, 
	we want to have reached the end point. But we don't know the exact value of our vertical velocity yet.  The vertical 
	velocity is made up of a scalar and a direction - the direction we know: m_spatialKin.angle. Now all we need is the 
	scalar: our speed.

	So this can be figured out from the angle, the distance to the end point, and the force of gravity.
	
	Let's find the horizontal and vertical components of our initial launch
		initialVertVelocity = speed * sin(launchAngle)
		initialHoriVelocity = speed * cos(launchAngle)   --- This never changes, as we don't factor in air resistance

	initialVertVelocity == -initialVertVelocity when the object has hit the ground
		total change in vertVelocity = 2*initialVertVelocity
	This is done by gravity, so:
		total change in vertVelocity = time*gravity
	Let's get that in terms of time
		2*initialVertVelocity = time*gravity
		time = 2*initialVertVelocity / gravity

	Horizontal velocity determines how far the object flies across the ground (distance)
		distance = time*initialHoriVelocity

	Substitute in time from above
		distance = (2*initialVertVelocity / gravity) * initialHoriVelocity  

	Rearrange it bro
		distance = (2*initialVertVelocity*initialHoriVelocity / gravity)

	Substitute in the velocities
		distance = (2 * (speed * sin(launchAngle)) * (speed * cos(launchAngle)) ) / gravity

	Rearrange! Make all that in terms of speed, our unknown
		distance * gravity = 2 * (speed * sin(launchAngle)) * (speed * cos(launchAngle))
		distance * gravity = 2 * speed*speed * sin(launchAngle) * cos(launchAngle)
		speed * speed = distance*gravity / ( 2 * sin(launchAngle) * cos(launchAngle) )

	Here's a Trigonometry Identity that we can use to simplify that
	2sin(x)cos(x) = sin2x

	Therefore:
		speed * speed = distance*gravity / sin(2*launchAngle)
		speed = sqrt( distance*gravity / sin(2*launchAngle)
	Which is finally calculated below as:
		return sqrt( (distance * m_gravityForce) / sin(2*m_spatialKin.angle) );
	*/

	// Get the distance from here to the endPos (pythagorus)
	float distance = ComputeDistanceToEnd();

	// Determine the speed needed to reach that distance
	return sqrt( (distance * m_gravityForce) / sin(2*m_spatialKin.angle) );
}

void PhysicsObject::MoveUpdate(void)
{
	if (m_airborne)
	{
		// Apply gravity to vertical spatial velocity
		m_spatialKin.ApplyGravity(m_gravityForce);
	
		// Keep track of the height, to know when the object has landed
		m_spatialKin.UpdateHeight();

		// Update velocity and position values
		m_screenKin.velocity.y = m_additiveScreenVelocity.y - m_spatialKin.velocity.y;
		m_pos.x += m_screenKin.velocity.x;
		m_pos.y += m_screenKin.velocity.y;
	
		if (m_spatialKin.height < 0) //Has hit the ground
		{
			// Call any overridden OnLanding code
			OnLanding();

			// This is no longer airborne
			m_airborne = false;

			// Snap the PhysicsObject to its target position (just to make sure, completely and surely)
			m_pos.x = m_endPos.x;
			m_pos.y = m_endPos.y;

			//Stop all movement
			m_spatialKin.Clear();
			m_screenKin.Clear();
		}
	}
}