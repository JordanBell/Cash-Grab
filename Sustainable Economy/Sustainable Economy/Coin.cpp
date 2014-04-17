#include "Coin.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Resources.h"
#include <time.h>
#include <stdlib.h>

Coin::Coin(int start_x, int start_y, int end_x, int end_y) : Entity(start_x, start_y), moving(true), speed(10), height(0)
{ 
	sprite_sheet = g_resources->GetCoinSheet();

	start.x = start_x;
	start.y = start_y;
	end.x = end_x;
	end.y = end_y;

	delay = 200;
	max_cycles = 8 * LOOP_SPEED;
	
	// Get the random number generator going
	srand(time(NULL));
	
	//Initialise the kinematics fields
	InitKin();

	//Initialise the clips of the sprite_sheet
	InitSheet();
}

void Coin::InitKin()
{
	moving = true; //Testing only. Skips animation

	CalcInitPlanar();
	CalcInitXAngle();
	CalcInitVelocities();
}

void Coin::CalcInitPlanar(void)
{
	//Randomise the angle of initial trajectory.
			//angle = (rand() % 35) + 10; //Angle between 10 and 45 degrees
			angle = 85;
	angle *= 2 * M_PI / 360;	//Convert to Radians

	//Get the planar x and y velocities (planar being the movement in a 3D space, where y is vertical and x is horizontal
	planar.x = speed * cos(angle);
	planar.y = speed * sin(angle);
}

void Coin::CalcInitXAngle(void)
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
	else
	{
		alpha = atan(dx / dy);
		alpha = aimingRight ? (RIGHT_ANGLE - alpha) : (RIGHT_ANGLE + alpha);
	}
}

void Coin::CalcInitVelocities(void)
{
	//Use previous information to calculate the velocity.
	velocity.x = planar.x * cos(alpha);
	initial_vertical = velocity.y = (planar.x * sin(alpha) + planar.y) * -1;
}

float Coin::ComputeVariableGravity()
{
	// It's just a cold, hard equation. Just plug in the values.
	/*printf("GravConst: %f", gravityStruct.gravityConstant);
	printf("Height: %f", height);
	printf("Min: %f", gravityStruct.min);
	printf("Denominator: %f", (speed * speed * sin(angle) * sin(angle)));*/
	return gravityStruct.gravityConstant * height / (speed * speed * sin(angle) * sin(angle)) + gravityStruct.min;
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

void Coin::update(int delta)
{
    IncCycle();
	
	if (moving) move();
	else
	{
		/*x = end.x;
		y = end.y;*/
	}
}

void Coin::move()
{
	/*printf("Moving... ");
	printf("px: %f, py: %f\n", planar.x, planar.y);
	printf("vx: %f, vy: %f\n", velocity.x, velocity.y);
	printf("x: %f, y: %f\n", x, y);
	printf("height: %f\n\n", height);*/

	//planar.y changes based on height
	printf("Gravity Computed as: %f\n", ComputeVariableGravity());
	planar.y -= ComputeVariableGravity();
	height += planar.y;

	if (height < 0) //Has hit the ground
	{
		printf("CRASH\n");
		moving = false;
		/*x = end.x;
		y = end.y;*/
		velocity.x = velocity.y = planar.x = planar.y = 0; //Stop all movement
	}
	else
	{
		velocity.y = planar.y* -3/4;
		//velocity.y *= -1;
		x += velocity.x;
		y += velocity.y;
	}
}