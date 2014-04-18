#ifndef __SustainableEconomy__Coin__
#define __SustainableEconomy__Coin__

#include "entity.h"

#define RIGHT_ANGLE (M_PI/2)
#define HALF_ANGLE (M_PI)
#define VARY_GRAVITY true

class Coin : public Entity
{
public:
	Coin(int start_x, int start_y, int end_x, int end_y);
	~Coin(void) {}

	void update(int delta);

protected:
	void set_skin() { skin = sprites[cycle/LOOP_SPEED]; };

private:
	//Init
    
	void InitSheet();
	void InitKin();
		void ComputeInitPlanar(void);
		void ComputeInitXAngle(void);
		void ComputeInitVelocities(void);

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

		Gravity::Gravity() : mid(0.05), 
							 norm(mid*10),
							 rangeRatio(0.5),  
							 min(mid - (rangeRatio * mid / 2)),
							 gravityConstant(4 * (rangeRatio * mid) * mid) {}
	} gravityStruct;

	//Graphics
    SDL_Rect* sprites[ 8 ];

	//Kinematics
	struct XY { float x, y; };
	XY start, end, planar, velocity, angleInducedVelocity;
	float initial_vertical;

	bool moving;
	int LOOP_SPEED;
	float angle;	//The trajectory angle, from the ground horizontal
	float alpha;	//The angle between start and end position
	float height;	//The "height" off the ground
	float speed;	//The strength of the initial launch
	float gravity;	//The measure of gravity acting down
	
	void move();
	float DistanceToEnd();
	float ComputeAngleForDistance();
	float ComputeVariableGravity();
};

#endif

