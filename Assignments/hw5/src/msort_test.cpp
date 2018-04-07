#include <iostream>
#include "../lib/msort.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
  // generate a random string array
  vector<string> testList {"Acbdef", "acbdef", "acbdefghj", "bdefg", "cef", "bfdeq", "abcdef", "njakel", "adebhs"};
  // ALPHASTRCOMP sorting
  AlphaStrComp compAlpha;
  mergeSort(testList, compAlpha);
  
  cout << "***Sorted list using AlphaStrComp***" << endl;
  for (unsigned int i = 0; i < testList.size(); i++)
    cout << testList[i] << endl;

  // LENGTHSTRCOMP sorting
  LengthStrComp compLength;
  mergeSort(testList, compLength);
  
  cout << endl << "***Sorted list using LengthStrComp***" << endl;
  for (unsigned int i = 0; i < testList.size(); i++)
    cout << testList[i] << endl;
}