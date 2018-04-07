#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
  	cerr << "Please provide an input file" << endl;
  	return 1;
  }

  ifstream inputFile(argv[1]);	// load in the input file

  int n = -1; // holds the number of words in the file

  inputFile >> n;	// load up the number of words

  // check if the number of words have been provided
  if (inputFile.fail())
    {
      cerr << "Error: Number of words not provided... Exiting" << endl;
      return -1;
    }

  string *words = new string[n];	// create a string array to store the words

  for (int i = 0; i < n; i++)
  		inputFile >> words[i];

  for (int i = (n-1); i >= 0; i--)
  	cout << words[i] << endl;

  delete [] words;
}