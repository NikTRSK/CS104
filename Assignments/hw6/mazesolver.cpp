#include "mazesolver.h"
#include "mazedisplay.h"
#include "visitedtracker.h"
#include <QMessageBox>
#include <queue>
#include <stack>
#include <vector>
#include "heap.h"
#include <cmath> // abs, sqrt, pow

#include <iostream>
#include <climits>


MazeSolver::MazeSolver(Maze * m, MazeDisplay * md)
    : maze(m), display(md)
{}

void MazeSolver::DFSHelper(int r, int c, VisitedTracker & vt, int &numExplored, std::vector<Direction> & parent, std::vector<Direction> & path, bool &pathFound) {
  // if Goal found. We're done. Base case
  if (pathFound) return;
  numExplored++;  // we are checking the node so increse the counter
  if ((r == maze->getGoalRow() && c == maze->getGoalCol())) {
    vt.setVisited(r, c);
    pathFound = true;
    return;
  }
  // explore only if not explored previously
  if (!vt.isVisited(r, c)) {
    vt.setVisited(r, c);

    if (maze->canTravel(RIGHT, r, c) && !vt.isVisited(r, c+1)) {
      parent[squareNumber(r, c+1)] = RIGHT;
      DFSHelper(r, c+1, vt, numExplored, parent, path, pathFound);
    }
    if (maze->canTravel(LEFT, r, c) && !vt.isVisited(r, c-1)) {
      parent[squareNumber(r, c-1)] = LEFT;
      DFSHelper(r, c-1, vt, numExplored, parent, path, pathFound);
    }
    if (maze->canTravel(DOWN, r, c) && !vt.isVisited(r+1, c)) {
      parent[squareNumber(r+1, c)] = DOWN;
      DFSHelper(r+1, c, vt, numExplored, parent, path, pathFound);
    }
    if (maze->canTravel(UP, r, c) && !vt.isVisited(r-1, c)) {
      parent[squareNumber(r-1, c)] = UP;
      DFSHelper(r-1, c, vt, numExplored, parent, path, pathFound);
    }
  }
}

void MazeSolver::solveByDFSRecursive() {
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    // create tracker array
    VisitedTracker vt(maze->numRows(), maze->numCols());
    // create predecessor vector & path vector
    std::vector<Direction> parent( numSquares );
    std::vector<Direction> path;
    int numExplored = 0;
    r = maze->getStartRow(); c = maze->getStartCol(); // grab start node
    bool pathFound = false;
    DFSHelper(r, c, vt, numExplored, parent, path, pathFound);  // run the DFS recursive algorithm
    createPath(maze->getGoalRow(), maze->getGoalCol(), parent, vt, path); // backtrack and generate path
    display->reportSolution(path, vt, numExplored); // report the solution
}

void MazeSolver::solveByAStar(int choice) {
  int r, c;
  int numSquares = maze->numRows() * maze->numCols();
  // create f and g functions. init f to infinity (well INT_MAX)
  // f = g + h => g = cost from start to current Node; h = heuristic cost from current Node do finish
  int f[numSquares];
  int g[numSquares];
  for (int i = 0; i < numSquares; i++)
    f[i] = INT_MAX;

  // explored tracker
  bool explored[maze->numRows()][maze->numCols()];
  for (int i = 0; i < maze->numRows(); i++) {
    for (int j = 0; j < maze->numCols(); j++)
      explored[i][j] = false;
  }

  VisitedTracker vt(maze->numRows(), maze->numCols());  // tracks visited nodes
  std::vector<Direction> parent(numSquares); // predecessors for visited fields

  // get Goal Node. simpler for passing in.
  std::pair<int, int> goalNode(maze->getGoalRow(), maze->getGoalCol());

  int numExplored = 0;
  MinHeap<std::pair<int,int> > pq(2); // create a priority queue
  
  // init costs for start node to 0
  f[squareNumber(maze->getStartRow(), maze->getStartCol())] = 0;
  g[squareNumber(maze->getStartRow(), maze->getStartCol())] = 0;
  pq.add(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()), f[squareNumber(maze->getStartRow(), maze->getStartCol())]);  // add start node to the PQ

  while (!pq.isEmpty()) {
    std::pair<int, int> v = pq.peek();
    pq.remove();  // node visited, so remove it
    
    r = v.first;
    c = v.second;
    // explore if not visited already
    if (!explored[r][c]) {
      explored[r][c] = true;
      numExplored++; 
      if( r == maze->getGoalRow() && c == maze->getGoalCol() ) {
        // create the path
        std::vector<Direction> path;
        createPath(r, c, parent, vt, path); // call me slick. Recursive backtracking
        display->reportSolution(path, vt, numExplored);
        return;
      }

      if (maze->canTravel(UP, r, c)) {
        if (!vt.isVisited(r-1, c) || (g[squareNumber(r, c)]+1 + heuristic(std::pair<int, int>(r-1, c), goalNode, choice) < f[squareNumber(r-1, c)])) {
          g[squareNumber(r-1, c)] = g[squareNumber(r,c)]+1;
          f[squareNumber(r-1, c)] = g[squareNumber(r-1, c)] + heuristic(std::pair<int, int>(r-1, c), goalNode, choice);
          parent[squareNumber(r-1, c)] = UP;
          vt.setVisited(r-1, c);
          pq.add(std::pair<int,int>(r-1, c), f[squareNumber(r-1, c)]);
        }
      }
      if (maze->canTravel(DOWN, r, c)) {
        if (!vt.isVisited(r+1, c) || (g[squareNumber(r, c)]+1 + heuristic(std::pair<int, int>(r+1, c), goalNode, choice) < f[squareNumber(r+1, c)])) {
          g[squareNumber(r+1, c)] = g[squareNumber(r,c)]+1;
          f[squareNumber(r+1, c)] = g[squareNumber(r+1, c)] + heuristic(std::pair<int, int>(r+1, c), goalNode, choice);
          parent[squareNumber(r+1, c)] = DOWN;
          vt.setVisited(r+1, c);
          pq.add(std::pair<int,int>(r+1, c), f[squareNumber(r+1, c)]);
        }
      }
      if (maze->canTravel(LEFT, r, c)) {
        if (!vt.isVisited(r, c-1) || (g[squareNumber(r, c)]+1 + heuristic(std::pair<int, int>(r, c-1), goalNode, choice) < f[squareNumber(r, c-1)])) {
          g[squareNumber(r, c-1)] = g[squareNumber(r, c)]+1;
          f[squareNumber(r, c-1)] = g[squareNumber(r, c-1)] + heuristic(std::pair<int, int>(r, c-1), goalNode, choice);
          parent[squareNumber(r, c-1)] = LEFT;
          vt.setVisited(r, c-1);
          pq.add(std::pair<int,int>(r, c-1), f[squareNumber(r, c-1)]);
        }
      }
      if (maze->canTravel(RIGHT, r, c)) {
        if (!vt.isVisited(r, c+1) || (g[squareNumber(r, c)]+1 + heuristic(std::pair<int, int>(r, c+1), goalNode, choice) < f[squareNumber(r, c+1)])) {
          g[squareNumber(r, c+1)] = g[squareNumber(r, c)]+1;
          f[squareNumber(r, c+1)] = g[squareNumber(r, c+1)] + heuristic(std::pair<int, int>(r, c), std::pair<int, int>(r, c+1), choice);
          parent[squareNumber(r, c+1)] = RIGHT;
          vt.setVisited(r, c+1);
          pq.add(std::pair<int,int>(r, c+1), f[squareNumber(r, c+1)]);
        }
      }
    }
  }
}

void MazeSolver::solveByDFSIterative() {
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::stack<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while( ! q.empty() )
    {
        std::pair<int, int> v = q.top();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}

void MazeSolver::solveByBFS() {
    /* In lecture on Tuesday March 22, we had a graph
       with vertices numbered 0 to n-1, inclusive.
       Instead, we have vertices with two numbers,
       row and col, in the range:
       [0, maze->numRows()-1], [0, maze->numCols() -1 ]
       to assign each a unique number [0, maze->numRows() * maze->numCols() -1]
       we will say that maze square (r,c) is really number
       r * maze->numCols() + c
    */
    int r, c;
    int numSquares = maze->numRows() * maze->numCols();
    VisitedTracker vt(maze->numRows(), maze->numCols());

    std::vector<Direction> parent( numSquares ); // what was my immediate prior direction to get here?
    int numExplored = 0;
    vt.setVisited(maze->getStartRow(), maze->getStartCol());
    std::queue<std::pair<int, int>> q;
    q.push(std::pair<int,int>(maze->getStartRow(), maze->getStartCol()));

    while( ! q.empty() )
    {
        std::pair<int, int> v = q.front();
        q.pop();
        numExplored++;

        r = v.first;
        c = v.second;

        /* This one if statement is different from the pseudo-code provided
           in lecture, because we want to stop when we've reached the goal.
           The code provided in lecture was for if you wanted to do a BFS
           that explored the entire graph.
        */
        if( r == maze->getGoalRow() && c == maze->getGoalCol() )
        {
            std::vector<Direction> path;
            std::stack<Direction> st;

            while( r != maze->getStartRow() || c != maze->getStartCol())
            {
                st.push( parent[ squareNumber(r,c) ]);
                switch( st.top() )
                {
                case UP: r++; break; // yes, r++.  I went up to get here...
                case DOWN: r--; break;
                case LEFT: c++; break;
                case RIGHT: c--; break;
                }
            }
            while ( ! st.empty() )
            {
                path.push_back(st.top());
                st.pop();
            }
            display->reportSolution(path, vt, numExplored);
            return;
        }

        /*
         * Now we're back to code that looks like the pseudo-code you've seen.
         * The difference here is that we aren't keeping track of distances;
           that's similar to the difference above.  You could add, and ignore,
           the vector that would result if you wanted to do so.
         */
        if ( maze->canTravel(UP, r, c) && ! vt.isVisited(r-1,c))
        {
            parent[squareNumber(r-1, c)] = UP;
            vt.setVisited(r-1,c);
            q.push(std::pair<int,int>(r-1, c));
        }
        // Note:  this is NOT "else if" ...
        if ( maze->canTravel(DOWN, r, c) && ! vt.isVisited(r+1,c) )
        {
            parent[squareNumber(r+1, c)] = DOWN;
            vt.setVisited(r+1, c);
            q.push(std::pair<int,int>(r+1, c));
        }
        if ( maze->canTravel(LEFT, r, c) && ! vt.isVisited(r,c-1) )
        {
            parent[squareNumber(r, c-1)] = LEFT;
            vt.setVisited(r, c-1);
            q.push(std::pair<int,int>(r, c-1));
        }
        if ( maze->canTravel(RIGHT, r, c) && ! vt.isVisited(r, c+1) )
        {
            parent[squareNumber(r, c+1)] = RIGHT;
            vt.setVisited(r, c+1);
            q.push(std::pair<int,int>(r, c+1));
        }
    }
}


int MazeSolver::squareNumber(int r, int c) const {
  return maze->numCols() * r + c;
}

int MazeSolver::heuristic(std::pair<int, int> u, std::pair<int, int> v, int choice) {
  // u = node 1; v = node 2
  /*choice = heuiristic type
      1: 0. Essentially runs BFS
      2: Manhattan Distance
      3: Euclidean Distance*/
  if (choice == 1)
    return 0;
  else if (choice == 2)
    return std::abs(u.first - v.first) + std::abs(u.second - v.second); // Manhattan distance
  else if (choice == 3)
    return sqrt( pow(u.first - v.first, 2) + pow(u.second - v.second, 2) ); // Euclidian distance
  else
    return 0; // double check if this is cool with staff.
}

void MazeSolver::createPath(int r, int c, std::vector<Direction> &parent, VisitedTracker &vt, std::vector<Direction> &path) {
  if (r == maze->getStartRow() && c == maze->getStartCol())
    return;
  else {
    switch(parent[squareNumber(r, c)]) {
      case UP: createPath(r+1, c, parent, vt, path); break;
      case DOWN: createPath(r-1, c, parent, vt, path); break;
      case LEFT: createPath(r, c+1, parent, vt, path); break;
      case RIGHT: createPath(r, c-1, parent, vt, path); break;
    }
    // create path when returning from the recursive calls
    path.push_back(parent[squareNumber(r,c)]);
  }
}