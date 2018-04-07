#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  int floors;
  int *floorsizes;
  int **numitems;
  string ***trojans;
  string curr;

  input >> floors;
  trojans = new string**[floors];

  //keeps track of number of people are on each floor.
  floorsizes = new int[floors];
  // keeps track of number of items for each student
  numitems = new int*[floors];

  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
	  numitems[i] = NULL;
  }

  // Gets rid of the /n after the number. Without this the first command is \n
  input.ignore (1, '\n'); 

  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;
	  if (curr == "MOVEIN") {
		  int i,k;
		  ss >> i;
		  ss >> k;
		  if (ss.fail() || (i < 0 || k < 0) || (ss >> std::ws).peek() != -1)	// error checking
			  output << "Error - incorrect command" << endl;
		  else {
		  	if (floors <= i)
		  		output << "Error - MOVEIN: Floor " << i << " doesn't exist" << endl;
		  	else if (floorsizes[i] > 0)
		  		output << "Error - MOVEIN: floor " << i << " is not empty" << endl;
	  		else {
			  	trojans[i] = new string*[k];	// allocate space for k students on floor i
			  	floorsizes[i] = k;	// set the floor sizes to k
			  	numitems[i] = new int[k];	// allocate space for # of items of k students
			  	// set the pointers to null
			  	for (int s = 0; s < k; s++) {
			  		trojans[i][s] = NULL;
			  		numitems[i][s] = 0;
			  	}
			  }
		  }
	  }
	  else if (curr == "MOVEOUT") {
	  	int i;
	  	ss >> i;
	  	if (ss.fail() || i < 0)	// error checking
			  output << "Error - incorrect command" << endl;
		  else {
		  	if (floors <= i)
		  		output << "Error - MOVEOUT: Floor " << i << " doesn't exist" << endl;
		  	else if (floorsizes[i] == 0)
		  		output << "Error - MOVEOUT: Floor " << i << " is empty" << endl;
		  	else {
		  		// deallocate memory
		  		for (int s = 0; s < floorsizes[i]; s++)
		  			delete [] trojans[i][s];
		  		delete [] trojans[i];
		  		delete [] numitems[i];
		  		numitems[i] = NULL;
		  		trojans[i] = NULL;
		  		floorsizes[i] = 0;
		  	}
		  }
	  }
	  else if (curr == "OBTAIN") {
	  	int i,j,k;
	  	ss >> i;
	  	ss >> j;
	  	ss >> k;
	  	if (ss.fail() || floors < i || (i < 0 || j < 0 || k < 0))	// error checking
			  output << "Error - incorrect command" << endl;
	  	else {
	  		if (floorsizes[i] <= j)
	  			output << "Error - OBTAIN: there is no student " << j << " on floor " << i << endl;
	  		else if (numitems[i][j] != 0)
	  			output << "Error - OBTAIN: the student " << j << " on floor " << i << " alredy has possesions" << endl;
		  	else {
		  		trojans[i][j] = new string[k];
		  		numitems[i][j] = k;
		  		for (int item = 0; item < k; item++)
		  			ss >> trojans[i][j][item];
		  		// check for extra items or missing items (invalid input)
		  		bool fail = ss.fail(); int peek = (ss >> std::ws).peek();
		  		if ((peek != -1) || fail) {
						output << "Error - incorrect command" << endl;
						// if bad command also delete "bad" memory
						delete [] trojans[i][j];
						trojans[i][j] = NULL;
						numitems[i][j] = 0;
					}
		  	}		  		
	  	}
	  }
	  else if (curr == "OUTPUT") {
	  	int i,j;
	  	ss >> i;
	  	ss >> j;
	  	if (ss.fail() || (i < 0 || j < 0))	// error checking
			  output << "Error - incorrect command" << endl;
		  else {
	  		if (floors <= i || floorsizes[i] <= j)
					output << "Error - OUTPUT: there is no student " << j << " on floor " << i << endl;
	  		else if (numitems[i][j] == 0)
	  			output << "Error - OUTPUT: student " << j << " has no possesions" << endl;
	  		else {
		  		for (int item = 0; item < numitems[i][j]; item++)
		  			output << trojans[i][j][item] << endl;
				}
	  	}
		}
	  else
	  	output << "Error - incorrect command" << endl;
  }
  // deallocate memory
  for (int i = 0; i < floors; i++)
	{
		for (int j = 0; j < floorsizes[i]; j++)
			delete [] trojans[i][j];
		delete [] trojans[i];
		delete [] numitems[i];
	}
  delete [] floorsizes;
  delete [] trojans;
	delete [] numitems;

	// close files
	input.close();
  output.close();

  return 0;
}