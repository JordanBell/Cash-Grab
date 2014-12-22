#include "Wallet.h"
#include "LaunchData.h"

int Wallet::numCoins = START_MONEY;
int Wallet::numTokens = 0;
int Wallet::totalCollectedCoins = 0;
int Wallet::highestCoinCount = 0;

void Wallet::IncCoinsBy(int n) 
{ 
	numCoins += n; 
	totalCollectedCoins += n;
	highestCoinCount += (highestCoinCount < totalCollectedCoins) ? n : 0;

	// Notify the launch data, as it changes based on the total number of coins collected
	LaunchData::Notify(totalCollectedCoins);
}