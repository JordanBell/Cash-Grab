#pragma once
#include "Coin.h"

class CoinBronze :
	public Coin
{
public:
	CoinBronze(int start_x, int start_y, int end_x, int end_y) 
		: Coin(start_x, start_y, end_x, end_y) { InitSheet(); }

	void OnCollect(void) override final;
	
	static int value;
protected:
	void InitSheet(void) override final;
};