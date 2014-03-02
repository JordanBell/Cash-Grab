#ifndef __SustainableEconomy__Coin__
#define __SustainableEconomy__Coin__

#include "entity.h"

class Coin : public Entity
{
public:
	Coin(int start_x, int start_y, int end_x, int end_y);
	Coin(void);
	~Coin(void) {}

	void update();

protected:
	void set_skin() { skin = sprites[cycle]; };

private:
	//Init
    
    /**
     * Init sheet.
     */
	void init_sheet();
	void init_kin();

	//Graphics
	static const int square_size = 32;
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

