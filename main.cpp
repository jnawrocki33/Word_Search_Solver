/* 
 * File:   main.cpp
 * Author: Jason
 *
 * Created on February 27, 2015, 11:58 AM
 *  This program uses a puzzle class and dictionary class
 *  It finds and prints all words in a given puzzle (word search)
 */

#include <cstdlib>
#include "Puzzle.h"
#include "Dictionary.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int x;
    cout << "Enter minimum word length: " << endl;
    cin >> x;
    Puzzle puzzleObj = Puzzle(x);
    cout << "Read puzzle with " << puzzleObj.getRows() << " rows and "
            << puzzleObj.getCols() << " columns" << endl << endl;
    puzzleObj.printBoard();
    cout << "Using naive approach:" << endl;
    //puzzleObj.simpleSolve();
    cout << endl << "Using direction approach:" << endl;
    puzzleObj.binarySolve();
    cout << endl << "Using direction approach with prefixes:" << endl;
    puzzleObj.prefixSolve();
    
    return 0;
}

