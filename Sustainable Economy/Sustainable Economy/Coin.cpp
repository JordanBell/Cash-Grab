#include "Coin.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"

Coin::Coin(int start_x, int start_y, int end_x, int end_y) : Entity(x, y)
{ 
	start.x = start_x;
	start.y = start_y;
	end.x = end_x;
	end.y = end_y;
	Coin(start_x, start_y);
}

Coin::Coin(int x, int y) : Entity(x, y), moving(true)
{
	delay = 200;
	max_cycles = 8;

	//Initialise the kinematics fields
	init_kin();

	//Initialise the clips of the sprite_sheet
	init_sheet();
}

void Coin::init_sheet()
{
	for (int i = 0; i < 8; i++)
	{
		SDL_Rect* clip = new SDL_Rect();

		clip->x = clip->y = TILE_SIZE * i;
		clip->w = clip->h = TILE_SIZE;
        
        sprites[i] = clip;
	}
}

void Coin::init_kin()
{
	moving = false; //Testing only. Skips animation

	//Randomise the angle of initial trajectory.
	angle = (rand() % 35) + 10; //Angle between 10 and 45 degrees
	angle *= 2 * M_PI / 360;	//Convert to Radians

	//Get the planar x and y velocities (planar being the movement in a 3D space, where y is vertical and x is horizontal
	planar.x = speed * cos(angle);
	planar.y = speed * sin(angle);

	//Angle of horizontal movement, with regards to the horizontal of the screen.
	int alpha; //The angular between start and end position
	bool aiming_right = start.x < end.x;
	int dy = end.y - start.y; //The difference in y coordinates from start to end.
	int dx = aiming_right ? (end.x - start.x) : (start.x - end.x); // The difference in x coordinates from start to end.
	alpha = atan(dx / dy);
	alpha = aiming_right ? 90 - alpha : 90 + alpha;

	//Use this information to calculate the velocity.
	velocity.x = planar.x * cos(alpha);
	initial_vertical = velocity.y = planar.x * sin(alpha);
}

void Coin::update()
{
    inc_cycle();

	if (moving) move();
	else
	{
		x = end.x;
		y = end.y;
	}
}

void Coin::move()
{
	//planar.y changes based on height
	planar.y -= gravity;

	if (planar.y <= 0) //Has hit the ground
	{
		moving = false;
		x = end.x;
		y = end.y;
		velocity.x = velocity.y = planar.x = planar.y = 0; //Stop all movement
	}
	else
	{
		velocity.y = initial_vertical + planar.y;
		x += velocity.x;
		y += velocity.y;
	}
}