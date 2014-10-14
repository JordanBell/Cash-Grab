#pragma once
#include "coin.h"
class CoinFive :
	public Coin
{
public:
	CoinFive(int start_x, int start_y, int end_x, int end_y) 
		: Coin(start_x, start_y, end_x, end_y) { InitSheet(); }

	void OnCollect(void) override final;

protected:
	void InitSheet(void) override final;
};

