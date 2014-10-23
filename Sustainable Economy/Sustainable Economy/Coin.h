#pragma once
#include "Collidable.h"
#include <list>
#include "Throwable.h"

class Coin : public Throwable
{
public:
	Coin(int start_x, int start_y, int end_x, int end_y);
	~Coin(void);

	void update(int delta);
	static std::list<Coin*> CoinsAround(int x, int y, int radius);
	static std::list<Coin*> CoinsAroundPlayer(int radius);

	virtual void OnCollect(void) override = 0;

protected:
    SDL_Rect* sprites[ 8 ];
	
	void set_skin() { skin = sprites[cycle/LOOP_SPEED]; }
	virtual void InitSheet() {}
};

extern std::list<Coin*> g_coins;
