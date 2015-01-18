#include "Inventory.h"
#include "LaunchData.h"
#include "Camera.h"

const float Inventory::k_CoinIncrease = 1.25f;

Wallet* Inventory::GetCoinWallet(const int ele) 
{ 
	if (ele == Element::NORMAL)
		return GetInstance().normCoins;	
	else if (ele == Element::ICE)
		return GetInstance().iceCoins;	
	else if (ele == Element::FIRE)
		return GetInstance().fireCoins;	

	throw runtime_error("Element not recognised.");
}

Wallet* Inventory::GetCashWallet(const int ele) 
{ 
	if (ele == Element::NORMAL)
		return GetInstance().normCash;	
	else if (ele == Element::ICE)
		return GetInstance().iceCash;	
	else if (ele == Element::FIRE)
		return GetInstance().fireCash;

	throw runtime_error("Element not recognised.");
}