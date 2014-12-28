#pragma once
#define START_MONEY 5
#define COIN_INCREASE 1.25
#include <vector>

class Key;

class Wallet
{
public:
	static void IncCoins(void) { IncCoinsBy(1); }
	static void IncCoinsBy(int n);
	static void Remove(int num) { numCoins -= (num <= numCoins) ? num : numCoins; }

	static int GetCash(void) { return numCash; }
	static int GetCoins(void) { return numCoins; }
	static int GetTotalCoins(void) { return totalCollectedCoins; }

	static void AddCash(int amount) { numCash += amount; }
	static void AddKeyID(int keyID) { heldKeyIDs.push_back(keyID); }
	static std::vector<int> GetKeys(void) { return heldKeyIDs; }

private:
	Wallet(void);
	~Wallet(void);

	static std::vector<int> heldKeyIDs;

	static int numCoins;
	static int numCash;

	static int totalCollectedCoins;
	static int highestCoinCount;
};

