#include "Wallet.h"
#include "LaunchData.h"
#include "Camera.h"

int Wallet::numCoins = START_MONEY;
int Wallet::numCash = 0;
int Wallet::totalCollectedCoins = 0;
int Wallet::highestCoinCount = 0;
std::vector<int> Wallet::heldKeyIDs = vector<int>();

void Wallet::IncCoinsBy(int n) 
{ 
	numCoins += n; 
	totalCollectedCoins += n;
	highestCoinCount += (highestCoinCount < totalCollectedCoins) ? n : 0;

	// Notify the launch data, as it changes based on the total number of coins collected
	g_camera->GetRoomFocus()->GetMachine()->GetProgress()->Notify(totalCollectedCoins);
}