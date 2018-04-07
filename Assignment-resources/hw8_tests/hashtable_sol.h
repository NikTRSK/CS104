#ifndef _HASH_TABLE_SOL_H
#define _HASH_TABLE_SOL_H

#include <string>
#include <vector>
#include <algorithm>

class HashTableSol
{
public:
    /**
    * Constructor that builds a hashtable with 31 indices. 
    */
    HashTableSol();

    /**
    * Reclaims the memory used for the hashtable.
    */
    ~HashTableSol();

    /**
    * Adds an item into the hashtable.
    *
    * @param newItem A pair that will be added into the hashtable. The first value will
    * be used as the key and the second value is the value in the hashtable.
    * @throws Throws an exception if the item already exists in the hashtable.
    */
    virtual void add_sol(const std::string& word);
    virtual void reportAll_sol(std::ostream& output);

private:

    std::string toLower(const std::string& word)
    {
        std::string temp = word;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return temp;
    }

    /**
    * Resizes the hash table when the load factor becomes greater than 1.
    */
    void resize();

    /**
    * Hashes the key value and returns the index in the hash table where the key
    * should be stored. 
    *
    * @param key The key to be hashed.
    * @return The hashed value associated with the key.
    */
    unsigned int hash(std::string key) const;

private:

    // The number of elements in the table.
    unsigned int mSize;

    int mCapIndex;

    // The number of indices available, i.e. the number of buckets in the hashtable.
    unsigned int mCapacity;

    // The actual hashtable where the information is stored. 
    std::pair<std::string, int>** mHashMap;

public:
    class iterator {
    friend class HashTableSol;
    public:
        /**
         * Initialize the internal members of the iterator
         */
        iterator() : mOwner(NULL), mIndex(0){}
        
        std::pair<std::string, int>& operator*(){
            return *(mOwner->mHashMap[mIndex]);
        }
        
        std::pair<std::string, int>* operator->(){
            return mOwner->mHashMap[mIndex]; 
        }
        
        /**
         * Checks if 'this' iterator's internals have the same value
         *  as 'rhs'
         */
        bool operator==(const iterator& rhs) const{
            return (mOwner == rhs.mOwner) && (mIndex == rhs.mIndex);
        }
        
        /**
         * Checks if 'this' iterator's internals have a different value
         *  as 'rhs'
         */
        bool operator!=(const iterator& rhs) const{
            return (mOwner != rhs.mOwner) || (mIndex != rhs.mIndex);
        }
        
        /**
         * Advances the iterator's location using an in-order sequencing
         */
        iterator& operator++(){
            mIndex = successor(mIndex);
            return *this;
        }
    
    protected:
        unsigned int successor(unsigned int me){
            unsigned int index = me + 1;
            while (index < mOwner->mCapacity && mOwner->mHashMap[index] == NULL){
                ++index;
            }
            return index;
        }

    protected:
        HashTableSol* mOwner;
        unsigned int mIndex;
        iterator(HashTableSol* me, unsigned int begin) : mOwner(me), mIndex(begin){}
      };

public:
    /**
     * Returns an iterator to the "smallest" item in the tree
     */
    iterator begin(){
        if (mHashMap[0] != NULL || mSize == 0)
        {
            iterator(this, mCapacity);
        }
        unsigned index = 0;
        while (mHashMap[index] == NULL)
        {
            ++index;
        }
        return iterator(this, index);
    }

    /**
     * Returns an iterator whose value means INVALID
     */
    iterator end(){
        return iterator(this, mCapacity);
    }
};

#endif