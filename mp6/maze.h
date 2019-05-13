/* Your code here! */
#pragma once
#include "./cs225/PNG.h"
#include "./cs225/HSLAPixel.h"
#include <vector>
#include <map>
#include <queue>
#include <stack>
using namespace cs225;

class SquareMaze {
    public:
        	SquareMaze ();
        /**
         * If this object already represents a maze it will clear all the existing data before doing so.
         * You will select random walls to delete without creating a cycle,
         * until there are no more walls that could be deleted without creating a cycle.
         * Do not delete walls on the perimeter of the grid.
         **/
            void makeMaze(int width, int height);
        /**
         * This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y).
         * For example, after makeMaze(2,2), the possible input coordinates will be (0,0), (0,1), (1,0), and (1,1).
         * dir = 0 represents a rightward step (+1 to the x coordinate)
         * dir = 1 represents a downward step (+1 to the y coordinate)
         * dir = 2 represents a leftward step (-1 to the x coordinate)
         * dir = 3 represents an upward step (-1 to the y coordinate)
         **/
            bool canTravel(int x, int y, int dir) const;
        /**
         * Sets whether or not the specified wall exists.
         * This function should be fast (constant time).
         * SetWall should not prevent cycles from occurring
         * but should simply set a wall to be present or not present
         **/
            void setWall(int x, int y, int dir, bool exists);
        /**
          * For each square on the bottom row (maximum y coordinate), there is a distance from the origin (i.e. the top-left cell),
          * which is defined as the length (measured as a number of steps) of the only path through the maze from the origin to that square.
          * Select the square in the bottom row with the largest distance from the origin as the destination of the maze
        **/
            std::vector< int > solveMaze();
        /**
         *  Create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
         *  Blacken the entire topmost row and leftmost column of pixels,
         *  except the entrance (1,0) through (9,0).
         *  If the right wall exists, blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
         *  If the bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
         **/
            PNG* drawMaze() const;
        /**
         * This function calls drawMaze, then solveMaze;
         * it modifies the PNG from drawMaze to show the solution vector and the exit.
         **/
            PNG* drawMazeWithSolution();


            std::vector<int>solveMaze_creative();
            PNG* drawMazeWithSolution_creative();
            

    private:
            /* private helper*/
            std::stack<int> backTraverse(std::vector<int> lastRow,  std::map<int, int> steps);
            std::vector< bool > Vertical;
            std::vector< bool > Hori;
            int height_;
            int width_;
};
