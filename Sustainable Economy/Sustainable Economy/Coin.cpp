#include "Coin.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Resources.h"
#include <time.h>
#include <stdlib.h>
#include "Player.h"

list<Coin*> g_coins;

Coin::Coin(int start_x, int start_y, int end_x, int end_y) : Throwable(start_x, start_y, end_x, end_y)
{
	g_coins.push_back(this);

	sprite_sheet = g_resources->GetCoinSheet();
	m_HitBox->w = 16;
    m_HitBox->h = 16;

	// Initialise the clips of the sprite_sheet
	InitSheet();
}

Coin::~Coin(void)
{
    for (int i = 0; i < 8; i++)
    {
       delete sprites[i];
    }
	g_coins.remove(this);
}

std::list<Coin*> Coin::CoinsAround(int px, int py, int radius)
{
	std::list<Coin*> r_coins;

	for (Coin* c : g_coins)
	{
		if (!c->moving) {
			int dx = g_player->x - c->x;
			int dy = g_player->y - c->y;
			int distance = sqrt(dx*dx + dy*dy);

			if (distance <= radius)
				r_coins.push_back(c);
		}
	}

	return r_coins;
}

std::list<Coin*> Coin::CoinsAroundPlayer(int radius) 
{ 
	return
		CoinsAround(g_player->x, g_player->y, radius); 
}

void Coin::update(int delta)
{
    Throwable::update(delta);
    IncCycle();
    
	if (!moving) // Only take effect when on the ground
    {
		// Soon: Refactor magnetism to the player's update

		//if (g_player->IsMagnetic()) // Only if magnetism is enabled
		//{
		//	if (sqrt(pow((g_player->x - x), 2) + pow((g_player->y - y), 2)) < 50)
		//	{
		//		{
		//			x = x + 0.25 * (g_player->x - x);
		//			y = y + 0.25 * (g_player->y - y);
		//		}
		//	}
		//}
    }

}