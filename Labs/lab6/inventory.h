#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <map>
#include <string>

class Inventory : private std::map<std::string, int> {
public:
	Inventory();

	/* Add an item to the inventory with the given name and amount. */
	void addItem(std::string, int);
	/* Remove all items with this name from the inventory. */
	void removeItem(std::string);
	/* Return the number of items with this name from the inventory. */
	int getNumItems(std::string);

	/* Print all the items in this format:
		key value
		key value
		key value
	*/
	void printAllItems();
};

#endif