#pragma once
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

	static const unsigned int k_StartMoney = 5;
	static const float k_CoinIncrease;

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
		: normCoins(new Wallet(k_StartMoney)), normCash(0),
		iceCoins(new Wallet(k_StartMoney)), iceCash(0),
		fireCoins(new Wallet(k_StartMoney)), fireCash(0),
		heldKeyIDs()
	
	{}

    Inventory(Inventory const& i);            // Copy construction not allowed
    Inventory& operator=(Inventory const& i); // Assignment not allowed

	std::vector<int> heldKeyIDs;
};

