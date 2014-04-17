#ifndef __SustainableEconomy__Coin__
#define __SustainableEconomy__Coin__

#include "entity.h"

class Coin : public Entity
{
public:
	Coin(int start_x, int start_y, int end_x, int end_y);
	Coin(int x, int y);
	~Coin(void) {}

	void update(int delta);

protected:
	void set_skin() { skin = sprites[cycle]; };

private:
	//Init
    
    /**
     * Init sheet.
     */
	void InitSheet();
	void InitKin();

	//Graphics
    SDL_Rect* sprites[ 8 ];

	//Kinematics
	struct XY {int x; int y;};
	XY start, end, planar, velocity;

	int initial_vertical;
	bool moving;
	int angle;
	static const int speed = 200;
	static const int gravity = 1;

	void move();
};

#endif

