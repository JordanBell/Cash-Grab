#pragma once
#include "XY.h"
#include "KinematicData.h"

#define RIGHT_ANGLE (PI/2)
#define HALF_ANGLE (PI)
#define THREEQ_ANGLE (3*PI/2)

class PhysicsObject
{
public:		
	virtual ~PhysicsObject(void) {}
	
	void Drop(void);
	void Launch(int angleSuppression = 0, int speedOverride = -1);
	void LaunchTo(int _x, int _y, int angleSuppression = 0, int speedOverride = -1);
	void Bounce(int speed) { Launch(-1, speed); }

	const bool IsAirborne(void) const { return m_airborne; }

	// Update movement variables
	void MoveUpdate();

protected:

	// A default value for a PhysicsObject's speed of descent
	static const float k_DefaultGravity;

	// Can be contructed above a ground position
	PhysicsObject(int end_x, int end_y, int height) 
		: m_pos(end_x, end_y - height), 
		m_endPos(end_x, end_y), 
		m_DropHeight(height),
		m_gravityForce(k_DefaultGravity), 
		m_airborne(true) {}

	// Can be constructed with specific start coordinates, initially stationary
	PhysicsObject(int _x, int _y) 
		: m_pos(_x, _y), 
		m_endPos(_x, _y), 
		m_gravityForce(k_DefaultGravity), 
		m_airborne(false) {}

	// Can be constructed with a start and end coordinate
	PhysicsObject(int start_x, int start_y, int end_x, int end_y)
		: m_pos(start_x, start_y), 
		m_endPos(end_x, end_y), 
		m_gravityForce(k_DefaultGravity),
		m_airborne(false) {}

	Position const& GetPOPosition(void) { return m_pos; }

	Position const& GetEndPosition(void) { return m_endPos; }

	const int GetHeight(void) { return m_spatialKin.height; }

	// The force of gravity on this object
	float m_gravityForce;

	// Override the value of gravity
	void SetGravity(float newGrav) { m_gravityForce = newGrav; }

	// A pixel velocity, derived from spatial velocity, that is added to screen velocity
	Vector2 m_additiveScreenVelocity;

	// Whether or not this is currently moving through the air
	bool m_airborne; 

	// Called upon landing; to be overridden
	virtual void OnLanding(void) {}

	// Called upon launching; to be overridden
	virtual void OnLaunch(void) {}

private:
	// If applicable, the drop height
	int m_DropHeight;

	// Initialise kinematic values
	void InitKin(void);

	// Current render position
	XY m_pos; 

	// Target end position of an airborne launch
	XY m_endPos; 

	// Kinematic data for airborne physics
	KinematicData m_spatialKin, m_screenKin;

	// Copy construction inaccessible
	PhysicsObject(PhysicsObject& _po) {}
	
	// Compute the distance from the current position to the current end position value
	const float ComputeDistanceToEnd(void) const;

	// Compute the scalar speed value required to reach the current end position value via the current spatial angle
	const float ComputeSpeedForDistance(void) const;

	// Compute the screen-relative movement angle
	const float ComputeScreenAngle(void) const;

};
