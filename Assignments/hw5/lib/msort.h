#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <vector>
#include <math.h>

/*============================
=========COMPARATORS==========
==============================*/
// STRING BASED COMAPRATORS
struct AlphaStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs) 
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs < rhs; 
  }
};

// Ascending comparator
struct AlphaStrCompAsc {
  bool operator()(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) 
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs.first < rhs.first; 
  }
};

// Descending comparator
struct AlphaStrCompDec {
  bool operator()(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs)
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs > rhs; 
  }
};

// String Lenght comparator
struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs) 
  { // Uses string's built in operator< 
    // to do lexicographic (alphabetical) comparison
    return lhs.size() < rhs.size(); 
  }
};

// INT BASED COMPARATORS
// Ascending comparator
struct NumberCompAsc {
  bool operator()(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) 
  {
    return lhs.second < rhs.second; 
  }
};

struct NumberCompDec {
  bool operator()(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) 
  {
    return lhs.second > rhs.second; 
  }
};


/*============================
==========MERGE SORT==========
==============================*/
template <typename T, class Comparator>
void merge (std::vector<T>& myArray, int left, int right, int middle, Comparator comp) {
  T tempArray[right+1-left];
  // set the strting points of the two subarrays
  int i = left, j = middle+1, k = 0;

  while (i <= middle || j <= right) {
    if (i <= middle && (j > right || comp(myArray[i], myArray[j]))) {
      // next smallest in the left subarray
      tempArray[k] = myArray[i]; i++; k++;
    }
    else {
      // next smallest element in the right subarray
      tempArray[k] = myArray[j]; j++; k++;
    }
  }
  // copy over the sorted tempArray into the actual array
  for (int k = 0; k < right+1-left; k++)
    myArray[k+left] = tempArray[k];
}

template <typename T, class Comparator>
void mergeHelper (std::vector<T>& myArray, int left, int right, Comparator comp) {
  if (left < right) { // Call mergeSort if >1 element. One element is already sorted. Nothing to be done
    int middle = floor((left+right)/2);
    mergeHelper(myArray, left, middle, comp);
    mergeHelper(myArray, middle+1, right, comp);
    merge(myArray, left, right, middle, comp); // the magic sauce. This function does the actual merging.
  }
}

template <typename T, class Comparator>
void mergeSort (std::vector<T>& myArray, Comparator comp) {
  mergeHelper(myArray, 0, myArray.size()-1, comp);
}

#endif