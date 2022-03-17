#include "PictureEdit.h"
// main function
int main() {
	// create variables and initialize them or not
	ifstream inputFile;
	string fileName = "";
	string tempFileName = "";
	string modificationChoice = "";
	int i = 0;
	vector<vector<vector<short>>> imageData; // initially empty
	vector<string> modifications{"negative", "high contrast", "remove red", "remove green" , "remove blue", "gray scale", "vertical flip", "horizontal flip", "random 50", "horizontal blur attempt"};
	// prompt user to input name of image
	cout << "Enter the name of the image for modification: ";
	cin >> fileName;
	tempFileName = fileName;
	cout << "\nProcessing " << fileName << ".ppm..." << endl;
	// open file
	openInputFile(inputFile, tempFileName += ".ppm");
	// read in the header values of the file
	readHeader(inputFile, specification, rows, cols, maxRGB);
	cout << "rows: " << rows << " cols: " << cols << endl;
	// read in the body values of the file
	readBody(inputFile, imageData, rows, cols);
	cout << "rows check: " << imageData.size() << " cols check: " << imageData.at(0).size() << endl;
	// task: define and call a displaySingleRow() function that accepts a row of image data and displays the triples
	displaySingleRow(imageData.at(rows - 1)); // display that last row
	// apply the modification to image
	for (i = 0; i < 10; i++) {
		applyModification(imageData, fileName, modifications.at(i));
	}
	cout << "\nExiting program..." << endl;
	// close file
	inputFile.close();
	return 0;
}
