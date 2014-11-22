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

	void update(int delta);
	static list<Coin*> CoinsAround(int x, int y, int radius);
	static list<Coin*> CoinsAroundPlayer(int radius);

	virtual void OnCollect(void) { g_player->IncSpeed(SPEED_GAIN); }
	void render(void) override final;
protected:
    SDL_Rect* sprites[8];

	// When landing, slow the animation to a calmer speed
	void OnLanding(void) override final { SetAnimationSpeed(6); }

	// When launched, speed up the animation to spin faster
	void OnLaunch(void)  override final { SetAnimationSpeed(1); }

	void set_skin() override { skin = sprites[cycle/GetAnimationSpeed()]; }
	virtual void InitSheet() {}
};
