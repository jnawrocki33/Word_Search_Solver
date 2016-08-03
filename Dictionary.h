/* 
 * File:   Dictionary.h
 * Author: Jason
 *
 * This is the dictionary class
 * It contains the dictionary object which is a vector
 *  and methods used to search inside the dictionary
 * Created on February 27, 2015, 11:59 AM
 */

#ifndef DICTIONARY_H
#define	DICTIONARY_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Dictionary {
public:
    Dictionary();
    bool binarySearch(string word, int iMin, int iMax);
    bool isPrefix(string word, int iMin, int iMax);
    int size() { return (int)dictionary.size();}
    string at(int i) { return dictionary.at(i);}
private:
    vector <string> dictionary;
};

#endif	/* DICTIONARY_H */

