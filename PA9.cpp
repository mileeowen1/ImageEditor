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
void listOfModificationChoices ();
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
void applyAPopOfColour(const vector<vector<vector<short>>>&, ofstream&);
// global variables
int rows, cols, maxRGB;
string specification;
// main function
int main() {
	// create variables and initialize them or not
	ifstream inputFile;
	string fileName = "";
	string tempFileName = "";
	string modificationChoice = "";
	int userChoice = 0;
	int i = 0;
	vector<vector<vector<short>>> imageData; // initially empty
	vector<string> modifications{"negative", "high contrast", "remove red", "remove green" , "remove blue", "gray scale", "vertical flip", "horizontal flip", "random 50", "a pop of colour"};
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
	cout << "1. Apply all modifications" << endl << "2. Apply one modification" << endl << "Enter the number of choice: " << endl << endl;
	cin >> userChoice;
	cout << endl;
	// apply the modification to image
	if (userChoice == 1) {
		for (i = 0; i < 10; i++) {
			applyModification(imageData, fileName, modifications.at(i));
		}
	}
	else {
		listOfModificationChoices();
		cin >> modificationChoice;
		// apply the modification to image
		applyModification(imageData, fileName, modificationChoice);
	}
	cout << "\nExiting program..." << endl;
	// close file
	inputFile.close();
	return 0;
}
// function definitions
 /*************************************************************
 * Function: openInputFile()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function opens file inputed by user.
 * Input parameters: The ifstream file must be pass by 
 *				reference and the name of the file.
 * Returns: nothing
 * Pre: The ifstream file must be pass by 
 *				reference and the name of the file had to have 
 *            	been scanned in by the user.
 * Post: The file is opened or not and a message is displayed.
 *************************************************************/
void openInputFile(ifstream& inputFile, string fname) {
	inputFile.open(fname);
	if (inputFile.is_open()) {
		cout << "Successfully opened input file" << endl;
	}
	else {
		cout << "Failed to open input file" << endl;
		exit(-1);
	}
}
 /*************************************************************
 * Function: readHeader()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function reads the header of the file.
 * Input parameters: The ifstream file, specification string,
 *				rows, cols, and maxRGB must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: The ifstream filem specification string, rows, cols,
 *				and maxRGB are pass by reference.
 * Post: The ifstream filem specification string, rows, cols,
 *				and maxRGB are pass by reference.
 *************************************************************/
void readHeader(ifstream& inputFile, string& specification, int& rows, int& cols, int& maxRGB) {
	inputFile >> specification;
	inputFile >> cols >> rows;
	inputFile >> maxRGB;
}
 /*************************************************************
 * Function: readBody()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function reads the body of the file.
 * Input parameters: The ifstream file and a 3-D vector is pass  
 *				by reference, rows, and cols.
 * Returns: nothing
 * Pre: The ifstream file and a 3-D vector is pass  
 *				by reference, rows, and cols had to have 
 *            	been scanned in by the user.
 * Post: The ifstream file and 3-D vector are pass by 
 *				reference.
 *************************************************************/
void readBody(ifstream& inputFile, vector<vector<vector<short>>>& imageData, int rows, int cols) {
	short value;
	vector<short> rgbTriple;
	vector<vector<short>> rowOfTriples;
	
	while (!inputFile.eof()) {
		inputFile >> value;
		if (inputFile.good()) {
			//cout << "Read value: " << value << endl;
			rgbTriple.push_back(value);
			if (rgbTriple.size() == 3) {
				// just processed a pixel
				rowOfTriples.push_back(rgbTriple);
				rgbTriple.clear();
				if (rowOfTriples.size() == cols) {
					// just processed a row
					imageData.push_back(rowOfTriples);
					rowOfTriples.clear();
				}
			}
		}
	}
}

void displaySingleRow(const vector<vector<short>>& row) {
	int i, j;
	for (i = 0; i < row.size(); i++) {
		for (j = 0; j < row.at(i).size(); j++) {
			cout << row.at(i).at(j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

short computeNegativeValue(short value) {
	short negativeValue = 0;
	negativeValue = abs(value - 255);
	return negativeValue;
}

short computeHighContrastValue(short value) {
	short highContrastValue = 0;
	if (value > 127) {
		highContrastValue = 255;
	}
	else {
		highContrastValue = 0;
	}
	return highContrastValue;
}

short computeRandomNoiseValue(short value) {
	
	short randomNoise = 0;
	short randomNoiseValue = 0;
	
	randomNoise = rand() % 100 - 50;
	
	randomNoiseValue = abs(randomNoise + value);
	
	return randomNoiseValue;
	
}

short computeGrayScaleValue(vector<short> value) {

	short sumValue = 0;
	short averageValue = 0;
	int i = 0;
	
	for (i = 0; i < value.size(); i++) {
		sumValue = sumValue + value.at(i);
	}
	
	averageValue = sumValue / value.size();
	
	return averageValue;

}

void listOfModificationChoices() {

	cout << "Image modification Choices:" << endl << "1. Negative" << endl << "2. High Contrast" << endl << "3. Remove Red" << endl << "4. Remove Green" << endl << "5. Remove Blue" << endl << "6. Gray Scale" << endl << "7. Vertical Flip" << endl << "8. Horizonatl Flip" << endl << "9. Random 50" << endl << "10. A Pop of Colour" << endl << endl;
	cout << "Enter the number for the modification you wish to make on the image: ";

}

void applyModification(const vector<vector<vector<short>>>& imageData, string fileName, string imageModification) {
	ofstream outputFile;
	if (imageModification == "negative" || imageModification == "1") {
		outputFile.open(fileName + "_negative.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_negative.ppm" << " for writing...";
		applyNegative(imageData, outputFile);
	}
	else if (imageModification == "high contrast" || imageModification == "2") {
		outputFile.open(fileName + "_high_contrast.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "high_contrast.ppm" << " for writing...";
		applyHighContrast(imageData, outputFile);
	}
	else if (imageModification == "remove red" || imageModification == "3") {
		outputFile.open(fileName + "_remove_red.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_remove_red.ppm" << " for writing...";
		applyRemoveRed(imageData, outputFile);
	}
	else if (imageModification == "remove green" || imageModification == "4") {
		outputFile.open(fileName + "_remove_green.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_remove_green.ppm" << " for writing...";
		applyRemoveGreen(imageData, outputFile);
	}
	else if (imageModification == "remove blue" || imageModification == "5") {
		outputFile.open(fileName + "_remove_blue.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_remove_blue.ppm" << " for writing...";
		applyRemoveBlue(imageData, outputFile);
	}
	else if (imageModification == "gray scale" || imageModification == "6") {
		outputFile.open(fileName + "_gray_scale.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_gray_scale.ppm" << " for writing...";
		applyGrayScale(imageData, outputFile);
	}
	else if (imageModification == "vertical flip" || imageModification == "7") {
		outputFile.open(fileName + "_vertical_flip.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_vertical_flip.ppm" << " for writing...";
		applyVerticalFlip(imageData, outputFile);
	}
	else if (imageModification == "horizontal flip" || imageModification == "8") {
		outputFile.open(fileName + "_horizontal_flip.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_horizontal_flip.ppm" << " for writing...";
		applyHorizontalFlip(imageData, outputFile);
	}
	else if (imageModification == "random 50" || imageModification == "9") {
		outputFile.open(fileName + "_random_50.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_random_50.ppm" << " for writing...";
		applyRandomNoise(imageData, outputFile);
	}
	else {
		outputFile.open(fileName + "_a_pop_of_colour.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_a_pop_of_colour.ppm" << " for writing...";
		applyAPopOfColour(imageData, outputFile);
	}
}


void applyNegative(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			outputFile << computeNegativeValue(imageData[j][i][0]) << " ";
			outputFile << computeNegativeValue(imageData[j][i][1]) << " ";
			outputFile << computeNegativeValue(imageData[j][i][2]) << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"negative\" complete. Closing files..." << endl;
}

void applyHighContrast(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			outputFile << computeHighContrastValue(imageData[j][i][0]) << " ";
			outputFile << computeHighContrastValue(imageData[j][i][1]) << " ";
			outputFile << computeHighContrastValue(imageData[j][i][2]) << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"high contrast\" complete. Closing files..." << endl;
}

void applyRemoveRed(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			outputFile << 0 << " ";
			outputFile << imageData[j][i][1] << " ";
			outputFile << imageData[j][i][2] << " " ;
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"remove red\" complete. Closing files..." << endl;
}

void applyRemoveGreen(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			outputFile << imageData[j][i][0] << " ";
			outputFile << 0 << " ";
			outputFile << imageData[j][i][2] << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"remove green\" complete. Closing files..." << endl;
}

void applyRemoveBlue(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			outputFile << imageData[j][i][0] << " ";
			outputFile << imageData[j][i][1] << " ";
			outputFile << 0 << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"remove blue\" complete. Closing files..." << endl;
}

void applyGrayScale(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0, k = 0;
	vector<short> rgbTriple;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			rgbTriple.push_back(imageData[j][i][0]);
			rgbTriple.push_back(imageData[j][i][1]);
			rgbTriple.push_back(imageData[j][i][2]);
			for (k = 0; k < 3; k++) {
				outputFile << computeGrayScaleValue(rgbTriple) << " ";
			}
			rgbTriple.clear();
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"gray scale\" complete. Closing files..." << endl;
}

void applyVerticalFlip(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = rows - 1; j >= 0; j--) {
		for (i = 0; i < cols; i++) {
			outputFile << imageData[j][i][0] << " ";
			outputFile << imageData[j][i][1] << " ";
			outputFile << imageData[j][i][2] << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"vertical flip\" complete. Closing files..." << endl;
}

void applyHorizontalFlip(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows ; j++) {
		for (i = cols - 1; i >= 0; i--) {
			outputFile << imageData[j][i][0] << " ";
			outputFile << imageData[j][i][1] << " ";
			outputFile << imageData[j][i][2] << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"horizontal flip\" complete. Closing files..." << endl;
}

void applyRandomNoise(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i++) {
			outputFile << computeRandomNoiseValue(imageData[j][i][0]) << " ";
			outputFile << computeRandomNoiseValue(imageData[j][i][1]) << " ";
			outputFile << computeRandomNoiseValue(imageData[j][i][2]) << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"random 50\" complete. Closing files..." << endl;
}

void applyAPopOfColour(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {

	int i = 0, j = 0;
	
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols/3; i++) {
			outputFile << 0 << " ";
			outputFile << imageData[j][i][1] << " ";
			outputFile << imageData[j][i][2] << " " ;
		}
		i = 0;
		outputFile << endl;
	}
	for (j = 0; j < rows; j++) {
		for (i = cols/3; i < 2*cols/3; i++) {
			outputFile << imageData[j][i][0] << " ";
			outputFile << 0 << " ";
			outputFile << imageData[j][i][2] << " ";
		}
		i = 0;
		outputFile << endl;
	}
	for (j = 0; j < rows; j++) {
		for (i = 2*cols/3; i < cols; i++) {
			outputFile << imageData[j][i][0] << " ";
			outputFile << imageData[j][i][1] << " ";
			outputFile << 0 << " ";
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"a pop of colour\" complete. Closing files..." << endl;
}
