#ifndef PICTURE_EDIT_H
#define PICTURE_EDIT_H
/*
Name: Milee Owen
Class: CPSC 121, Spring 2019
Date: April 21, 2019
Programming Assignment: PA9
Description: Create a program that edits ppm pictures.
Notes: Referenced http://www.cplusplus.com/forum/beginner/56491/ for "extern" (global variables)
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
// function prototypes
void openInputFile(ifstream&, string);
void readHeader(ifstream&, string&, int&, int&, int&);
void readBody(ifstream&, vector<vector<vector<short>>>&, int, int);
void displaySingleRow(const vector<vector<short>>&);
short computeNegativeValue(short);
short computeHighContrastValue(short);
short computeRandomNoiseValue(short);
short computeGrayScaleValue(vector<short>);
void applyModification(const vector<vector<vector<short>>>&, string, string);
void applyNegative(const vector<vector<vector<short>>>&, ofstream&);
void applyHighContrast(const vector<vector<vector<short>>>&, ofstream&);
void applyRemoveRed(const vector<vector<vector<short>>>&, ofstream&);
void applyRemoveGreen(const vector<vector<vector<short>>>&, ofstream&);
void applyRemoveBlue(const vector<vector<vector<short>>>&, ofstream&);
void applyGrayScale(const vector<vector<vector<short>>>&, ofstream&);
void applyVerticalFlip(const vector<vector<vector<short>>>&, ofstream&);
void applyHorizontalFlip(const vector<vector<vector<short>>>&, ofstream&);
void applyRandomNoise(const vector<vector<vector<short>>>&, ofstream&);
void applyComplexImageMod(const vector<vector<vector<short>>>&, ofstream&);
// global variables
extern int rows, cols, maxRGB;
extern string specification;
#endif
