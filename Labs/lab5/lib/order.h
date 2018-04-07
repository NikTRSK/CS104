#include <map>
#include <string>

class Order
{
	public:
		Order();
		Order(std::string);
		Order(const Order &o);
		~Order();
		void displayOrder();
		void clearOrder();
		Order& operator=(const Order &rhs);
		Order operator+(const Order &rhs);

		// Variables
		std::map<std::string, int> *items;	// Key = item name, Value = amount of that item
};