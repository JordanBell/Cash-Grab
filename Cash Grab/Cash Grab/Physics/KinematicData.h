#pragma once
#include "XY.h"
#include <math.h>

#define PI 3.14159265359f

class KinematicData 
{
public:
	KinematicData(void) : velocity(0, 0), angle(0), height(0) {}

	XY velocity;
	float angle, height;

	// Compute and Set the velocity vectors based on a scalar speed and the currently held angle of direction
	void SetVelocityFromScalar(const float speed)
	{
		velocity.x = speed * cos(angle);
		velocity.y = speed * sin(angle);
	}

	// Set the angle, in radians, based on a suppression value: The higher the suppression, the more shallow the angle
	void SetAngleBySuppression(const int angleSuppression) 
		{ angle = ComputeAngleBySuppression(angleSuppression); ToRadians(); }

	// Reduce the vertical velocity based on a gravity value
	void ApplyGravity(const float gravVal) 
		{ velocity.y -= gravVal; }

	// Update the height value by applying the vertical velocity
	void UpdateHeight(void)	
		{ height += velocity.y; }

	// Convert the angle from degrees to radians
	void ToRadians(void) 
		{ angle *= (2 * PI) / 360; }

	// Clear all values and reset to 0
	void Clear(void) 
		{ velocity.x = velocity.y = angle = height = 0; }
private:
	// Compute an angle, in degrees, based on a given suppression value
	static const float ComputeAngleBySuppression(const int angleSuppression);

};