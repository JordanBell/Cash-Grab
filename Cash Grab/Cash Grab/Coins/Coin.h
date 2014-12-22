#pragma once
#include "Collidable.h"
#include <list>
#include "Throwable.h"
#include "Player.h"

using namespace std;
class Coin;
extern list<Coin*> g_coins;

#define SPEED_GAIN 0.03

class Coin : public Throwable
{
public:
	Coin(int start_x, int start_y, int end_x, int end_y);
	~Coin(void);

	// When collected, increase the player speed. Subclasses increase the wallet's money accordingly.
	virtual void OnCollect(void) override { g_player->IncSpeed(SPEED_GAIN); }

	static list<Coin*> CoinsAround(int x, int y, int radius);
	static list<Coin*> CoinsAroundPlayer(int radius);
protected:
    SDL_Rect* sprites[8];

	// When landing, slow the animation to a calmer speed
	void OnLanding(void) override final;

	// When launched, speed up the animation to spin faster
	void OnLaunch(void)  override final;

	// TODO: Merge this with PowerUp's UpdateImageRect function
	void UpdateImageRect(void) override { m_imageRect = sprites[m_cycle/GetAnimationSpeed()]; }
};
