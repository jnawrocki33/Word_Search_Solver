/* 
 * File:   Puzzle.cpp
 * Author: Jason
 * 
 * This file contains the methods for the Puzzle class
 * It includes a way to read the puzzle file, as well as three methods to check
 * for words in the puzzle
 * 
 * Created on February 27, 2015, 12:07 PM
 */

#include "Puzzle.h"
//This function reads a file of characters into a puzzle, a 2D array
Puzzle::Puzzle(int len) {
    string fileName;
    ifstream puzzleStream;
    
    //read in the puzzle file name
    do {
        cout << "Enter the puzzle file name: ";
        cin >> fileName;
        puzzleStream.open(fileName.c_str(), ios::in);
    } while (!puzzleStream.good());     //continue until successful open
    
    string line;
    //Check that the file isn't empty
    if (!getline(puzzleStream, line)) {
        cerr << "Error: puzzle file is empty" << endl;
        numRows = 0;
        numCols = 0;
        return;
    }
    
    // put the first puzzle line in theBoard
    numCols = line.size();
    for (int i = 0; i < numCols; i++) {
        theBoard[0][i] = tolower(line.at(i));
    }
    
    //put the rest of the lines in theBoard
    for (numRows = 1; getline(puzzleStream, line); numRows++) {
        
        //make sure it's rectangular
        if (line.size() != numCols) {
            cerr << "Error: puzzle is not rectangular" << endl;
            numRows = 0;
            numCols = 0;
            return;
        }
        //put this puzzle line in theBoard
        for (int i = 0; i < numCols; i++) {
            theBoard[numRows][i] = tolower(line.at(i));
        }
    }
    minWordLength = len;
        
    }
//This function prints the puzzle board in upper case letters
void Puzzle::printBoard() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            cout << char(toupper(theBoard[r][c]));
        }
        cout << endl;
    }
    cout << endl;
}
//This is the naive approach to finding words
//It looks at every word in the dictionary for each possible position in each
//possible direction
//It is highly inefficient
void Puzzle::simpleSolve() {
    int numWords = 0;
    double start, end, seconds;
    start = clock();
    for (int w = 0; w < dictionary.size(); w++) {
        //check if the word is long enough to bother checking
        if (dictionary.at(w).length() < minWordLength) {
            continue;
        }
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < numCols; c++) {
                //This for loop runs through the 8 possible directions, treated
                //as integers 0-8
                for (int d = 0; d < NUM_DIRECTIONS; d++) {
                    //Down, d = 0
                    if (d == 0) {
                        //start with empty string
                        string newString = "";
                        //build the string up to the length of the word
                        //the direction down is accounted by adding to the row
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString + theBoard[r + count][c];
                        }
                        //check if the string matches the word.
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r + newString.length() - 1
                                    << "," << c << ")" 
                                    << endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Down Right, d = 1. same exact process as Down
                    //only the co-ordinates are treated differently
                    if (d == 1) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString +
                                    theBoard[r + count][c + count];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r + newString.length() - 1 
                                    << "," << c + newString.length() -1 
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Right - same as before with different coordinates
                    if (d == 2) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString + theBoard[r][c + count];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r
                                    << "," << c + newString.length() -1 
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Up Right
                    if (d == 3) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString + 
                                    theBoard[r - count][c + count];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r - newString.length() + 1
                                    << "," << c + newString.length() -1 
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Up
                    if (d == 4) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString + theBoard[r - count][c];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r - newString.length() + 1
                                    << "," << c 
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Up Left
                    if (d == 5) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString +
                                    theBoard[r - count][c - count];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r - newString.length() + 1
                                    << "," << c - newString.length() + 1 
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Left
                    if (d == 6) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString + theBoard[r][c - count];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r
                                    << "," << c - newString.length() + 1
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                    //Down Left
                    if (d == 7) {
                        string newString = "";
                        for (int count = 0; count < dictionary.at(w).length();
                                count++) {
                            newString = newString +
                                    theBoard[r + count][c - count];
                        }
                        if (newString == dictionary.at(w)) {
                            cout << "Found '" << dictionary.at(w) << "' at (" 
                                    << r << "," << c << ") " << " to ("
                                    << r + newString.length() - 1
                                    << "," << c - newString.length() + 1 
                                    << ")"<< endl;
                            numWords = numWords + 1;
                        }   
                    }
                }
            }
        }     
    }
    end = clock();
    seconds = (end - start) / CLOCKS_PER_SEC;
    cout << "Found " << numWords << " matches" << endl;
    cout << "Solution time: " << seconds << " seconds" << endl;
}

//This function is more efficient than the simple solve
//It checks each possible string on the board, and uses binary search
//to determine if it forms a word
//Strings are built up to the end of the board in all 8 directions
void Puzzle::binarySolve() {
    int numWords = 0;
    double start, end, seconds;
    start = clock();
    //find the maximum possible word length. this is how long potential words
    //will be built
    int maxL;
    if (numRows > numCols) {
        maxL = numRows;
    }
    else if (numRows < numCols) {
        maxL = numCols;
    }
    else {
        maxL = numCols;
    }
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            //dx and dy represent the 8 directions in their combinations
            for (int dx = -1; dx < 2; dx++) {
                for (int dy = -1; dy < 2; dy++) {
                    //if dx and dy are both zero, this is not a direction
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    string newString = "";
                    //build strings up to the minimum word length
                    for (int i = 0; i < minWordLength; i++) {
                        newString = newString +
                                theBoard[r + (dx * i)][c + (dy * i)];
                        //if the word goes off the board, break
                        if (r + (dx * i) < 0 || r + (dx * i) > numRows -1
                                || c + (dy * i) < 0 || c + (dy * i) > numCols) {
                            break;
                        }
                    }
                
                    //check if the string is in the dictionary
                    bool check = dictionary.binarySearch(newString, 0, 
                            dictionary.size() - 1);
                        if (check == true) {
                            cout << "Found '" << newString << "' at ("
                                    << r << "," << c << ") to ("
                                    << r + (dx * newString.length()) - dx << ","
                                    << c + (dy * newString.length()) - dy 
                                    << ")" << endl;
                            numWords = numWords + 1;
                        }  
                    //continue building the word up to the maximum word length
                    for (int l = minWordLength; l < maxL-1; l++) {
                        newString = newString +
                                theBoard[r + (dx *l)][c + (dy * l)];
                        //check if the string goes off the board
                        if (r + (dx * l) < 0 || r + (dx * l) > numRows -1
                                || c + (dy * l) < 0 || c + (dy * l) > numCols) {
                            break;
                        }
                        //check if the string is in the dictionary
                        bool check = dictionary.binarySearch(newString, 0,
                                dictionary.size() - 1);
                        if (check == true) {
                            cout << "Found '" << newString << "' at ("
                                    << r << "," << c << ") to ("
                                    << r + (dx * newString.length()) - dx << ","
                                    << c + (dy * newString.length()) - dy 
                                    << ")" << endl;
                            numWords = numWords + 1;
                        }
                    }     
                }
            }
        }
    }
    end = clock();
    seconds = (end - start) / CLOCKS_PER_SEC;
    cout << "Found " << numWords << " matches" << endl;
    cout << "Solution time: " << seconds << " seconds" << endl;
}

//This function words very similarly to binarySolve
//It is more efficient in that it checks the string being build
//to see if it forms a prefix of a word in the dictionary
//if it doesn't, that entire direction can be discarded
void Puzzle::prefixSolve()  {
    int numWords = 0;
    double start, end, seconds;
    start = clock();
    //find the maximum possible word length on the puzzle
    int maxL;
    if (numRows > numCols) {
        maxL = numRows;
    }
    else if (numRows < numCols) {
        maxL = numCols;
    }
    else {
        maxL = numCols;
    }
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            for (int dx = -1; dx < 2; dx++) {
                //again, dy and dx represent the 8 directions in combinations
                for (int dy = -1; dy < 2; dy++) {
                    //make sure it is an actual direction
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    string newString = "";
                    //build the string up to the minimum word length
                    for (int i = 0; i < minWordLength; i++) {
                        newString = newString + 
                                theBoard[r + (dx * i)][c + (dy * i)];
                        //check that the string is on the board
                        if (r + (dx * i) < 0 || r + (dx * i) > numRows -1
                                || c + (dy * i) < 0 || c + (dy * i) > numCols) {
                            break;
                        }
                        //always check if the word is still a prefix
                        bool check1 = dictionary.isPrefix(newString, 0,
                                dictionary.size() - 1);
                        if (check1 == false) {
                            break;
                        }
                    }
                    
                    //check if the string of min length is a word
                    bool check3 = dictionary.binarySearch(newString, 0,
                            dictionary.size() - 1);
                    if (check3 == true) {
                        cout << "Found '" << newString << "' at ("
                            << r << "," << c << ") to ("
                            << r + (dx * newString.length()) - dx << ","
                            << c + (dy * newString.length()) - dy 
                            << ")" << endl;
                        numWords = numWords + 1;
                        }
                    
                    //continue to build the string up to the maximum length
                    for (int l = minWordLength; l < maxL-1; l++) {
                        newString = newString +
                                theBoard[r + (dx *l)][c + (dy * l)];
                        if (r + (dx * l) < 0 || r + (dx * l) > numRows -1
                                || c + (dy * l) < 0 || c + (dy * l) > numCols) {
                            break;
                        }
                        //always check to see if the string is still a prefix
                        bool check4 = dictionary.isPrefix(newString, 0, 
                                dictionary.size() - 1);
                        if (check4 == false) {
                            break;
                        }
                        //check if the string makes a word
                        bool check5 = dictionary.binarySearch(newString, 0, 
                                dictionary.size() - 1);
                        if (check5 == true) {
                            cout << "Found '" << newString << "' at ("
                                    << r << "," << c << ") to ("
                                    << r + (dx * newString.length()) - dx << ","
                                    << c + (dy * newString.length()) - dy 
                                    << ")" << endl;
                            numWords = numWords + 1;
                        }
                    }     
                }
            }
        }
    }
    end = clock();
    seconds = (end - start) / CLOCKS_PER_SEC;
    cout << "Found " << numWords << " matches" << endl;
    cout << "Solution time: " << seconds << " seconds" << endl;
}

