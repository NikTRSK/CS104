#include "../lib/order.h"
#include <iostream>

// Constructor
Order::Order()
{
	items = new std::map<std::string, int>();
}

// Constructor which allocates one item
Order::Order(std::string i)
{
	// Allocate items
	items = new std::map<std::string, int>();

	// insert item = i, amount = 1
	// Only inserts if the map does not already contain an element with the key i
	items->insert(std::make_pair(i, 1));
	// can use (*items)[i] = 1, which does not care if the key already exists
}

// Copy Constructor - Part 1
Order::Order(const Order &rhs)
{
	// STUB
}

Order::~Order()
{
	delete items;
}

// Prints all items and their amounts.
void Order::displayOrder()
{
	std::cout << "The current order is: " << std::endl;

	// Check if empty
	if(items->empty())
	{
		std::cout << "Empty" << std::endl;
		return;
	}

	// Display each item and its amount
	std::map<std::string, int>::iterator it;
	for(it = items->begin(); it != items->end(); ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
}

// Deletes all items in variable ITEMS. - Part 2
void Order::clearOrder()
{
	// STUB
}

// Assigns Order RHS values to the current Order's values - Part 2
Order& Order::operator=(const Order &rhs)
{
	// Starter code: self-assignment can cause unseen problems. It won't
		// happen in this program, but let's get you in the habit early.
	if(this == &rhs)
		return *this;

	// STUB

	return *this;
}

/* 
Part 2
This operator should create a new Order that represents the
combined outcome of the current Order and the Order passed in via
parameter.
Note: It should not directly modify the current Order, but return
a copy of the combined Order instead. 
*/
Order Order::operator+(const Order &rhs)
{
	// Starter code: operator+ should not modify THIS, so we make a copy
	Order lhs(*this);

	// STUB

	return lhs;
}