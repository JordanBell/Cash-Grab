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

	OnLaunch();
	
	// The spatial launch angle
	m_spatialKin.SetAngleBySuppression(angleSuppression);

	// The scalar launch speed
	int speed = (speedOverride >= 0)? speedOverride : ComputeSpeedForDistance();

	// Derive the velocity from the speed and angle
	m_spatialKin.SetVelocityFromScalar(speed);
	
	// Compute the on-screen angle of travel
	m_screenKin.angle = ComputeScreenAngle();
	
	m_additiveScreenVelocity = XY (
		m_spatialKin.velocity.x * cos(m_screenKin.angle),
		m_spatialKin.velocity.x * sin((m_pos.y > m_endPos.y) ? (m_screenKin.angle*-1) : m_screenKin.angle)
	); 

	// Determine the on-screen velocities
	m_screenKin.velocity.x = m_additiveScreenVelocity.x;
	m_screenKin.velocity.y = m_additiveScreenVelocity.y + (m_spatialKin.velocity.y * -3/4); // Multiply by a negative as the axis for the coordinates are swapped
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
	// Get the distance from here to the endPos
	float distance = ComputeDistanceToEnd();

	// Use a physics equation to determine the speed needed to reach that distance
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
			// Any subclass's overriden, virtual OnLanding code
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