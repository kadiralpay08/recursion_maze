#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

using namespace std;

//#include "stack.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include "queue.h"

class Maze{
 public:
    Maze();                    //default constructor
    Maze(int start_row, int start_col);     //constructor with set start
    bool read();               //reads a maze from text file
    Coords findStart();        //find start of maze
    bool findPathDepth(int r, int c);  //recursive solver, that starts at position (c,r) and tries to find 'G' in maze
    bool findPathBreadth(int r, int c); //breath first search
    void replaceStart(Coords start);    //puts start S back in its place
    void print(int &pos, int Xpos, bool affectPos);       	   //prints the maze
    void resetMaze();   //resets maze

 private:
    int maze_rows, maze_cols;  //maze size read in from the file
    int row, col;
    int start_row, start_col;
    vector<vector<char>> maze;
    vector<vector<char>> mazeSolution;
};

#endif // MAZE_H_INCLUDED
