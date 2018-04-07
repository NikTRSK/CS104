/*
    llistint.h 
    Header file for a doubly-linked list that tracks integers. 
*/

#ifndef _LLISTINT_H
#define _LLISTINT_H

class LListInt 
{
    public:
        struct Item 
        {
            Item(int aVal, Item *aNext, Item *aPrev) : val(aVal), prev(aPrev), next(aNext) { }
            int val;
            Item *prev;
            Item *next;
        };

    public:
        /**
        * Default constructor.
        */
        LListInt();

        /**
        * Destructor.
        */
        ~LListInt();

        /**
        * Returns the size of the list.
        * @return The size of the list.
        */
        int size() const;

        /**
        * Checks whether or not the list is empty.
        * @return A boolean value, which is true if the list is empty and false otherwise.
        */
        bool empty() const;

        /**
        * Inserts a value into the list at the given position. Takes no action if an invalid location is provided. 
        * @param pos The position in the list where the item should be interted.
        * @param val The value that will be inserted into the list.
        */
        void insert(int pos, const int& val);

        /**
        * Removes an item from the list at a given position. Takes no action if an invalid location is provided. 
        * @param pos The position of the list that will be removed.
        */
        void remove(int pos);

        /**
        * Sets the value of an item at a given position. Takes no action if an invalid location is provided. 
        * @param pos The position in the list where the item will be set. 
        * @param val The value that will be inserted at the given position. 
        */
        void set(int pos, const int& val);

        /**
        * Returns the value from the list at a given position. Provides mutator access.
        * @param pos The position of the list where the user wants the value.
        * @return The value of the item at the given position.
        * @throws An exception is thrown if the position is out of bounds.
        */
        int& get(int pos);

        /**
        * Returns the value from the list at a given position. Provides const access.
        * @param pos The position of the list where the user wants the value.
        * @return The value of the item at the given position.
        * @throws An exception is thrown if the position is out of bounds.
        */
        int const & get(int pos) const;

        /**
        * Clears the contents of the list by deleting all memory and resetting the 
        * values. 
        */
        void clear();

    private:
        /**
        * A helper function to return an Item at a given position.
        * @param pos The position of the Item in the list.
        * @return A pointer to the item in the list. If the position is out of bounds
        *         for the list, NULL is returned instead. 
        */
        Item *getNodeAt(int pos) const;

    private:
        Item *mHead;
        Item *mTail;
        int mSize;
};

#endif