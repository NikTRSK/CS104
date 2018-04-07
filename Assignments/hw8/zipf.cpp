#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>   // tolower
#include <algorithm>  // transform

#include "Map.h"
#include "bst.h"
#include "splayTree.h"
#include "hashMap.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Missing parameters.\nUsage: ./zipf option [4 | 5] input_file\n";
    return 1;
  }

  // check if valid values
  string input;
  Map *ds;
  if (stoi(argv[1]) == 4)
    ds = new splayTree();
  else if (stoi(argv[1]) == 5)
    ds = new hashMap();
  else {
    cerr << "Invalid values.\nUse 4 for Splay Tree and 5 for Hash Table!!!\n";
    return 1;
  }

  // read in the file
  ifstream iFile(argv[2]);
  if (!iFile) {
    cerr << "Can't open file!!!";
    return 1;
  }

  // splayTree ds;

  // setup clock
  clock_t start;
  double duration;

  start = clock();

  // consume input
  while (iFile >> input) {
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    try {
      ds->add(input);
    }
    catch (std::exception const& e) {
      cerr << e.what() << endl;
      return 1;
    }
  }
  
  duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

  // report values
  ds->reportAll(cout);

  // report duration
  cout << "The duration for all adds using a ";
  if (stoi(argv[1]) == 4)
    cout << "Splay Tree";
  else if (stoi(argv[1]) == 5)
    cout << "Hash Table";
  cout <<" was : " << duration << endl;
  // clear memory
  delete ds;
  return 0;
}