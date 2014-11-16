#pragma once
#include "Collidable.h"
#include <list>

#define RIGHT_ANGLE (M_PI/2)
#define HALF_ANGLE (M_PI)
#define THREEQ_ANGLE (3*M_PI/2)
#define VARY_GRAVITY false // Unstable feature - Setting this as true may cause instability with coin landing positions
#define ADAPT_ANGLE false
using namespace std;

class Throwable : public Collidable
{
public:
	bool moving;

	Throwable(int start_x, int start_y, int end_x, int end_y);
	~Throwable(void);

	virtual void update(int delta);
	virtual void OnCollect(void) = 0; // A throwable's effect when collected
	void SetHoming(int distance, int speed) { m_homingDistance = distance; m_homingSpeed = speed; }
	void SetBouncy(bool bouncy) { m_isBouncy = bouncy; }
	void LaunchTo(int _x, int _y, int angleSuppression = 0);
	void BounceUp(void);

	static list<Throwable*> ThrowablesAround(int x, int y, int radius);
	static list<Throwable*> ThrowablesAroundPlayer(int radius);

protected:
	int LOOP_SPEED;

private:
	void InitKin(int angleSuppression = 0, int speedOverride = -1);

	// Values used in the calculation of variable gravity, used to create an Ease effect
	const struct Gravity { 
		float mid;			// The average gravity value
		float norm;			// The value to use if not using easing
		float rangeRatio;	// Vary the gravity between -(rangeConst)% and mid
		float range;		// The amount that the gravity will vary by
		float min;			// The lower bound for gravity

		/* The portion of the variable gravity equation that involves the constant 
		values held within this struct. This is then applied to the variable, height, 
		to determine the gravity at a given height. */
		float gravityConstant; 

		Gravity() : mid(0.05),
                    norm(mid*10),
					rangeRatio(0.5),
					min(mid - (rangeRatio * mid / 2)),
					gravityConstant(4 * (rangeRatio * mid) * mid) {}
	} gravityStruct;

	// Effects
	int m_homingDistance; // The distance at which the throwable will stop homing
	float m_homingSpeed; // The pixels by which the throwable homes in each frame
	bool m_isBouncy;

	//Kinematics
	struct XY { float x, y; };
	XY start, end, planar, velocity, angleInducedVelocity;
	float initial_vertical;

	float angle;	//The trajectory angle, from the ground horizontal
	float alpha;	//The angle between start and end position
	float height;	//The "height" off the ground
	float speed;	//The strength of the initial launch
	float gravity;	//The measure of gravity acting down
	
	void move();
	float DistanceToEnd();
	float ComputeAngleForDistance();
	float ComputeSpeedForDistance();
	float ComputeVariableGravity();
};

extern list<Throwable*> g_throwables;
