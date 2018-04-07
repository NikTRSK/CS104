#ifndef SCHEDULING__
#define SCHEDULING__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include "bst.h"
#include "avlbst.h"

/*
 * Parses through a file and loads up the classses and students maps
 * @param classes - a map of all the classes and the time assignments
 * @param students - a map of all the students and their class enrolments
 */
void parseFile(std::ifstream &input, AVLTree<int, int> &classes, AVLTree<std::string, std::vector<int> > &students) {
  std::string line;
  while (getline(input, line)) {
    std::string student; int exam; // student not really needed (can just use line). done for the sake of clarity
    std::stringstream ss;
    ss << line;
    ss >> student;
    std::vector<int> exams; // temp storage for the set. also could have looked up the map everytime.
    while (ss >> exam) {
      exams.push_back(exam);
      // insert the exam into the classes map. if duplicate just ignore the exception
      try {
        // initialize all times to 0
        classes.insert(std::pair<int, int>(exam, 0));
      }
      catch(std::exception const& e) {
        continue; // if duplicate that's ok, just igrnore it
      }
    }
    try {
      // initialize all times to 0
      students.insert(std::pair<std::string, std::vector<int> >(student, exams));
    }
    catch(std::exception const& e) {
      continue; // shouldn't happen if there is correct input
    }
  }
}

/*
 * Returns TRUE if the student doesn't have a class conflict
 * @param exams - a map of all the classes and the time assignments
 * @param classes - a vector of classes in which a student is enrolled
 */
bool checkClasses (AVLTree<int, int> &exams, std::vector<int> &classes) {
  for (unsigned int i = 0; i < classes.size(); i++) {
    for (unsigned int j = i+1; j < classes.size(); j++) {
      if (exams.find(classes.at(i))->second != 0 && exams.find(classes.at(j))->second != 0) {
        if (exams.find(classes.at(i))->second == exams.find(classes.at(j))->second)
          return false;
      }
    }
  }
  return true;
}

/*
 * returns TRUE if all students don't have a conflict
 * @param exams - a map of all the classes and the time assignments
 * @param students - a map of all the students and their class enrolments
 */
bool checkAllStudents(AVLTree<int, int> &exams, AVLTree<std::string, std::vector<int> > &students) {
  // loop trough all the students and check if they have a time conflict
  for (AVLTree<std::string, std::vector<int> >::iterator student = students.begin(); student != students.end(); ++student) {
    if (!checkClasses(exams, student->second))
      return false;
  }
  return true;
}

/*
 * Enumerates all the classes using recurssive backtracking
 * @param classes - a map of all the classes and the time assignments
 * @param students - a map of all the students and their class enrolments
 * @param assignedTimes - a set of all the assigned times. Used to check if all times are assigned
 * @param numTimeslots - number of possible timeslots
 * @param checkedTimes - number of check timeslots
 */
bool assignTime(AVLTree<int, int> &classes, AVLTree<std::string, std::vector<int> > &students, std::set<int> &assignedTimes, unsigned int numTimeslots, unsigned int checkedTimes, unsigned int numClasses) {
  // if all times are assigned then done so return true
  if (checkedTimes == numClasses) {
    if (assignedTimes.size() == numTimeslots)
      return true;
    else
      return false;
  }

  for (AVLTree<int, int>::iterator exam = classes.begin(); exam != classes.end(); ++exam) {
    for (unsigned int timeslot = 1; timeslot <= numTimeslots; timeslot++) {
      // if the exam doesn't have a timeslot assigned assign a time and test
      if (exam->second == 0) {
        try {
          classes.remove(exam->first);
          classes.insert(std::pair<int, int>(exam->first, timeslot));
          // exam->second = timeslot; I'm leaving this in as a comment. Make's hell of a lot more sense then add/remove combo
        }
        catch(std::exception const& e) {
          continue; // shouldn't happen if there is correct input
        }
        // if timeslot possible go to next class
        if (checkAllStudents(classes, students)) {
          assignedTimes.insert(timeslot);
          return assignTime(classes, students, assignedTimes, numTimeslots, checkedTimes+1, numClasses);
        }
        // try a different timeslot
        else {
          try {
            classes.remove(exam->first);
            classes.insert(std::pair<int, int>(exam->first, 0));
            //exam->second = 0; I'm leaving this in as a comment. Make's hell of a lot more sense then add/remove combo
          }
          catch(std::exception const& e) {
            continue; // shouldn't happen if there is correct input
          }
        }
      }
    }
  }
  // if no assignment possible for a given exam, solution doesn't exist
  return false;
}


/*
 * Prints the current exam times assignments. Doesn't check whether there is a solution.
 * The user has to check before calling this function.
 */
void printClassAssignments(AVLTree<int, int> &classes) {
  for (AVLTree<int, int>::iterator exam = classes.begin(); exam != classes.end(); ++exam)
    std::cout << exam->first << "  " << exam->second << std::endl;
}

#endif