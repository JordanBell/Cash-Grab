#pragma once
#define START_MONEY 5
#define COIN_INCREASE 1.25

class Wallet
{
public:
	static void IncCoins(void) { IncCoinsBy(1); }
	static void IncCoinsBy(int n);
	static void Remove(int num) { numCoins -= (num <= numCoins) ? num : numCoins; }

	static int GetCoins() { return numCoins; }
	static int GetTotalCoins() { return totalCollectedCoins; }

private:
	Wallet(void);
	~Wallet(void);

	static int numCoins;
	static int numTokens;

	static int totalCollectedCoins;
	static int highestCoinCount;
};

