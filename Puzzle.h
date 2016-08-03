/* 
 * File:   Puzzle.h
 * Author: Jason
 *
 * This is the Puzzle class. it contains the methods for reading and solving
 * It also holds the board, the number of rows and columns, the minimum word len
 * And it also has a dictionary as an instance variable
 * Created on February 27, 2015, 12:07 PM
 */

#ifndef PUZZLE_H
#define	PUZZLE_H

#define MAX_ROWS 100
#define MAX_COLUMNS 100
#define NUM_DIRECTIONS 8

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"

using namespace std;

class Puzzle {
public:
    Puzzle(int len);
    void simpleSolve();
    void binarySolve();
    void prefixSolve();
    void printBoard();
    int getRows() {return numRows;}
    int getCols() {return numCols;}
    
private:
    char theBoard[MAX_ROWS][MAX_COLUMNS];
    int numRows;
    int numCols;
    int minWordLength;
    Dictionary dictionary;
};

#endif	/* PUZZLE_H */

