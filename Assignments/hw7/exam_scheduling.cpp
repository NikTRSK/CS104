#include "scheduling.h"

using namespace std;

int main(int argc, char* argv[]) {
  if(argc < 2) {
    cerr << "Please provide an input file." << endl;
    return 1;
  }
  ifstream input(argv[1]);
  if (!input) {
    cout << "Cannot open " << argv[1] << "!" << endl;
    return 1;
  }
  // load up the count variables
  int numExams, numStudents, numTimeslots;
  input >> numExams; input >> numStudents; input >> numTimeslots;

  input.ignore(1, '\n'); // ignore the newline

  AVLTree<string, std::vector<int> >* students = new AVLTree<string, std::vector<int> >; // student->classes_enrolled map
  AVLTree<int, int>* classes = new AVLTree<int, int>; // class->timeslot map
  set<int> assignedTimes;

  // parse through the file and load up the maps
  parseFile(input, *classes, *students);

  if (assignTime(*classes, *students, assignedTimes, numTimeslots, 0, numExams)) {
    cout << "========= SCHEDULE =========\n";
    printClassAssignments(*classes);
  }
  else {
    cout << "No valid solution." << endl;
  }

  delete students;
  delete classes;

  return 0;
}