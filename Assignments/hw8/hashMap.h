#ifndef _HASH_MAP_H
#define _HASH_MAP_H

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdexcept>
#include "Map.h"
#include <math.h>

class hashMap : public Map
{
public:
  hashMap();
  virtual ~hashMap();
  /**
  * Adds a word to the map. If this is the first time the word
  * has been encountered, it is added with a count of 1. Otherwise,
  * the count for the word is incremented by 1.
  */
  virtual void add(const std::string& word);

  /**
  * Reports the contents of the map. Each pair of <word, count> is
  * printed to a new line of the stream. The words should appear in
  * order they appear in the hash map, and the count should be separated
  * from the word by a space.
  */
  virtual void reportAll(std::ostream& output);

private:
  int size;       // holds the current size of the hash table
  int numItems;   // holds the number of items in the table
  std::vector<std::pair<std::string, int> > *data;  // holds the values for the hash table

  // Helper functions
  /**
   * approximately doubles the number of buckets available.
   * Triggered when load factor > 0.5.
   * The # of buckets should follow this sequence:
   * 11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961.
   */
  void resize();
  /*
   * takes a string as input, and outputs a pseudo-random index to store it at.
   */
  int hash(const std::string& word);
  std::vector<int> bitHash(const std::string& substr);
  // calculates the hasg for quadratic probe
  int calculateHash(int prevHash, int i);
  std::list<int> sizes;
};

#endif