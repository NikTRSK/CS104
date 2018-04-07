#ifndef MAZESOLVER_H
#define MAZESOLVER_H


#include "visitedtracker.h"

#include "maze.h"

/*
 * I didn't want the students to have to deal
 * with function pointers, so I'm making the
 * MazeSolver an object with various solve
 * methods.
 *
 * I won't be offended if anyone wants to refactor
 * this to make specific functions for them to call.
 */

class MazeDisplay;
class Maze;

class MazeSolver
{
public:
    MazeSolver(Maze * m, MazeDisplay * md);

    void solveByBFS();

    void solveByDFSIterative();

    void solveByDFSRecursive();

    void solveByAStar(int heuristicChoice);

    void setMaze(Maze* m) { maze = m; }

private:

    int squareNumber(int r, int c) const;
    // helper function for DFS
    void DFSHelper(int r, int c, VisitedTracker & vt, int &numExplored, std::vector<Direction> & parent, std::vector<Direction> & path, bool &pathFound);
    // creates the path recursivelly
    void createPath(int r, int c, std::vector<Direction> &parent, VisitedTracker &vt, std::vector<Direction> &path);
    // calculates the heuristic
    int heuristic(std::pair<int, int> u, std::pair<int, int> v, int choice);

    Maze * maze;
    MazeDisplay * display;
};

#endif // MAZESOLVER_H
