#pragma once
#define START_MONEY 5
#define COIN_INCREASE 1.25
#include <vector>
// Inventory::GetInstance().normCoins->GetAmount()
class Key;
class Inventory;

// Currencies used in the Wallet
class Wallet
{
public:
	void Add(const int n) { m_Amount += n; m_TotalCollected += n; }
	void Remove(const int n) { m_Amount -= n; }

	const int GetAmount(void) const { return m_Amount; }
	const int GetTotal(void) const { return m_TotalCollected; }

private:
	Wallet(const int n)
		: m_Amount(n), m_TotalCollected(0) {}

	int m_Amount;
	int m_TotalCollected;

	friend class Inventory; // Can construct new wallets
};

class Inventory
{
public:
	static Inventory& GetInstance(void)
	{
		static Inventory instance;
		return instance;
	}

	// Get a coin wallet object based on the element
	static Wallet* GetCoinWallet(const int ele);

	// Get a cash wallet object based on the element
	static Wallet* GetCashWallet(const int ele);

	Wallet *normCoins, *normCash, 
		   *iceCoins,  *iceCash, 
		   *fireCoins, *fireCash;

	void AddKeyID(const int keyID) { heldKeyIDs.push_back(keyID); }
	std::vector<int> const& GetKeys(void) const { return heldKeyIDs; }

private:
	Inventory(void) 
		: normCoins(new Wallet(START_MONEY)), normCash(0),
		iceCoins(new Wallet(START_MONEY)), iceCash(0),
		fireCoins(new Wallet(START_MONEY)), fireCash(0),
		heldKeyIDs()
	
	{}

    Inventory(Inventory const& i);            // Copy construction not allowed
    Inventory& operator=(Inventory const& i); // Assignment not allowed

	std::vector<int> heldKeyIDs;
};

