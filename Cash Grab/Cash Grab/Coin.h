#pragma once
#include "Collidable.h"
#include <list>
#include "Throwable.h"
#include "Game.h"

using namespace std;
class Coin;
extern list<Coin*> g_coins;

#define SPEED_GAIN 0.03

class Coin : public Throwable
{
public:
	Coin(const int start_x, const int start_y, const int end_x, const int end_y, const int ele);
	~Coin(void);

	static list<Coin*> CoinsAround(int x, int y, int radius);
	static list<Coin*> CoinsAroundPlayer(int radius);
protected:
    SDL_Rect* sprites[8];

	// The element of the coin
	int m_Element;

	// When landing, slow the animation to a calmer speed
	void OnLanding(void) override final;

	// When launched, speed up the animation to spin faster
	void OnLaunch(void)  override final;

	// TODO: Merge this with PowerUp's UpdateImageRect function
	void UpdateImageRect(void) override { m_imageRect = sprites[m_cycle/GetAnimationSpeed()]; }
};
