#pragma once
#include <list>
#include <functional>
#include "XY.h"
#include "CoinSilver.h"
using namespace std;

// Default value indicating that no element belongs to the throwable. -1 is a good value for this as only the Element enumeration will be passed.
#define NULL_ELEMENT -1

template<class Throw_Type>
class ThrowableQuantity;

class ThrowableQuantity_Base
{
public:
	// Construct with a start quantity
	ThrowableQuantity_Base(const int quantity, const int element)
		: m_Quantity(quantity), m_Element(element) {}

	virtual ~ThrowableQuantity_Base(void) {}

	int GetQuantity(void) 
		{ return m_Quantity; }

	const bool IsEmpty(void) const 
		{ return m_Quantity <= 0; }

	virtual ThrowableQuantity_Base* Splice(const int amount) = 0;

	virtual void Throw(Position const& from, Position const& to) = 0;
	virtual void Throw(Position const& from, Position const& to, const int count) = 0;
	virtual void Throw(Position const& from, function<Position ()> GetLaunchTo, const int count = 1) = 0;
	virtual void Throw(function<Position ()> GetLaunchFrom, function<Position ()> GetLaunchTo, const int count = 1) = 0;

	virtual void ThrowAll(Position const& from, function<Position ()> GetLaunchTo) = 0;
	virtual void ThrowAll(function<Position ()> GetLaunchFrom, function<Position ()> GetLaunchTo) = 0;

protected:
	int m_Quantity;
	int m_Element;

	ThrowableQuantity_Base(ThrowableQuantity_Base const& tq) {}            // Copy construction not allowed
	ThrowableQuantity_Base& operator=(ThrowableQuantity_Base const& tq) {} // Assignment not allowed
};

// A DispenseList is a list of ThrowableQuantites, used by Dispensers.
typedef list<ThrowableQuantity_Base*> DispenseList;

template <class Throw_Type>
class ThrowableQuantity 
	: public ThrowableQuantity_Base
{
	static const int k_AngleSuppression = 1;

public:
	ThrowableQuantity(const int quantity, const int element = NULL_ELEMENT)
		: ThrowableQuantity_Base(quantity, element) {}

	// Remove an amount and return a copy with that number
	ThrowableQuantity<Throw_Type>* Splice(const int amount) override final
	{
		if (m_Quantity >= amount)
		{
			m_Quantity -= amount;
			return new ThrowableQuantity<Throw_Type>(amount, m_Element);
		}
		else
			throw runtime_error("Not enough in ThrowableQuantity to splice that amount.");
	}

	// Throw one throwable between two positions
	void Throw(Position const& from, Position const& to)
	{
		if (m_Quantity > 0)
		{
			// Create a new throwable for that destination
			Throw_Type* throwable;

			// Pass the element to the throwable if an element was passed to the constructor
			if (m_Element == NULL_ELEMENT)
				throwable = new Throw_Type(from.x, from.y, to.x, to.y);
			else
				throwable = new Throw_Type(from.x, from.y, to.x, to.y, m_Element);
		
			// Cast the Throw_Type to a Throwable
			Throwable* t = dynamic_cast<Throwable*>( throwable );

			// Launch it
			t->Launch(k_AngleSuppression);

			// Add it to the collidables list
			g_game->addCollidable(t);

			m_Quantity--;
		}
		else
		{
			printf("Trying to throw a throwable when no quantity remains.");
		}
	}

	// Throw a number of these throwables from a start to an end position
	void Throw(Position const& from, Position const& to, const int count)
	{
		for (int i = 0; (i < count) && (m_Quantity > 0); i++)
			Throw(from, to);
	}

	// Throw to a position using a function to determine a new position for each one thrown
	void Throw(Position const& from, function<Position ()> GetLaunchTo, const int count = 1)
	{
		for (int i = 0; (i < count) && (m_Quantity > 0); i++)
			Throw(from, GetLaunchTo());
	}

	// Throw to a position using a function to determine a new position for each one thrown
	void Throw(function<Position ()> GetLaunchFrom, function<Position ()> GetLaunchTo, const int count = 1)
	{
		for (int i = 0; (i < count) && (m_Quantity > 0); i++)
			Throw(GetLaunchFrom(), GetLaunchTo());
	}

	void ThrowAll(Position const& from, function<Position ()> GetLaunchTo)
		{ Throw(from, GetLaunchTo, m_Quantity); }

	virtual void ThrowAll(function<Position ()> GetLaunchFrom, function<Position ()> GetLaunchTo)
		{ Throw(GetLaunchFrom, GetLaunchTo, m_Quantity); }

private:
	ThrowableQuantity(ThrowableQuantity const& tq) {}            // Copy construction not allowed
	ThrowableQuantity& operator=(ThrowableQuantity const& tq) {} // Assignment not allowed
};


//// Base Class
//class MyBase {
//public:
//	MyBase(int a) {}
//
//	virtual void Print() = 0;
//};
//
//// Subclass ONE
//class MySub_One : 
//	public MyBase 
//{
//public:
//	MySub_One(int a) 
//		: MyBase(a) {}
//
//	virtual void Print() override { printf("Sub One\n"); }
//};
//
//// Subclass TWO
//class MySub_Two : 
//	public MyBase 
//{
//public:
//	MySub_Two(int a) 
//		: MyBase(a) {}
//
//	virtual void Print() override { printf("Sub Two\n"); }
//};
//
//class MyTemplateBase
//{
//public:
//	virtual void CreateAndPrint() = 0;
//};
//
//
//// Template Class
//template <class T>
//class MyTemplate : public MyTemplateBase
//{
//public:
//	MyTemplate() {}
//
//	void CreateAndPrint()
//	{
//		T* obj = new T(0); // Compiler says, "error C2259: 'MyBase' Cannot instantiate abstract class."
//
//		obj = dynamic_cast<MyBase>( obj );
//		obj->Print(); 
//	}
//};
//
//void thing(void)
//{
//	list<MyTemplateBase*> testList = list<MyTemplateBase*>();
//	testList.push_back( new MyTemplate<MySub_One>() ); // This is a problem too
//}

