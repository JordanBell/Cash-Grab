#pragma once
#include "Coin.h"

class CoinGold :
	public Coin
{
public:
	CoinGold(int start_x, int start_y, int end_x, int end_y, const int ele = NORMAL) 
		: Coin(start_x, start_y, end_x, end_y, ele) { InitSprites(); }

	void OnCollect(void) override final;

	static int value;

protected:
	void InitSprites(void) override final;
};