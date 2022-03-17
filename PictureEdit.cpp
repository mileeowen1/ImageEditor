#include "PictureEdit.h"
int rows, cols, maxRGB;
string specification;
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
 * Pre: The ifstream file, specification string, rows, cols,
 *				and maxRGB are pass by reference.
 * Post: The ifstream file, specification string, rows, cols,
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
 /*************************************************************
 * Function: displaySingleRow()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function displays a single row from the file.
 * Input parameters: The vector of rows must be pass by reference.
 * Returns: nothing
 * Pre: The vector of rows must be pass by reference.
 * Post: The vector of rows is pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: computeNegativeValue()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function computes a value by subtracting 
 *				255 and taking the absolute value of the result.
 * Input parameters: A single short RGB value.
 * Returns: A new value.
 * Pre: A single short RGB value had to have been scanned in by
 *            	the user.
 * Post: A new value is retuned.
 *************************************************************/
short computeNegativeValue(short value) {
	short negativeValue = 0;
	negativeValue = abs(value - 255);
	return negativeValue;
}
 /*************************************************************
 * Function: computeHighContrastValue()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function computes a value by checking the 
 *				value and if the value is greater than 127, sets 
 *				it to 255, otherwise sets it to 0.
 * Input parameters: A single short RGB value.
 * Returns: A new value.
 * Pre: A single short RGB value had to have been scanned in by
 *            	the user.
 * Post: A new value is retuned.
 *************************************************************/
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
 /*************************************************************
 * Function: computeRandomNoiseValue()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function computes a value by generating a 
 *				random number in the range [-50, 50] and adds 
 *				it to the value.
 * Input parameters: A single short RGB value.
 * Returns: A new value.
 * Pre: A single short RGB value had to have been scanned in by
 *            	the user.
 * Post: A new value is retuned.
 *************************************************************/
short computeRandomNoiseValue(short value) {
	short randomNoise = 0;
	short randomNoiseValue = 0;
	randomNoise = rand() % 100 - 50;
	randomNoiseValue = abs(randomNoise + value);
	return randomNoiseValue;
}
 /*************************************************************
 * Function: computeGrayScaleValue()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function computes a value by computing the 
 *				average of the RGB values in the triple.
 * Input parameters: A RGB triple (1D vector of shorts).
 * Returns: A new value.
 * Pre: A RGB triple (1D vector of shorts) had to have been 
 *            	scanned in by the user.
 * Post: A new value is retuned.
 *************************************************************/
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
 /*************************************************************
 * Function: applyModification()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function applies the different image 
 *				modifications.
 * Input parameters: A 3-D vector must be pass by reference, 
 *				the name of the file, and name of image 
 *				modification.
 * Returns: nothing
 * Pre: A 3-D vector must be pass by reference, 
 *				the name of the file, and name of image 
 *				modification had to have been scanned in by the user.
 * Post: A 3-D vector is pass by reference.
 *************************************************************/
void applyModification(const vector<vector<vector<short>>>& imageData, string fileName, string imageModification) {
	ofstream outputFile;
	if (imageModification == "negative") {
		outputFile.open(fileName + "_negative.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_negative.ppm" << " for writing...";
		applyNegative(imageData, outputFile);
	}
	else if (imageModification == "high contrast") {
		outputFile.open(fileName + "_high_contrast.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "high_contrast.ppm" << " for writing...";
		applyHighContrast(imageData, outputFile);
	}
	else if (imageModification == "remove red") {
		outputFile.open(fileName + "_remove_red.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_remove_red.ppm" << " for writing...";
		applyRemoveRed(imageData, outputFile);
	}
	else if (imageModification == "remove green") {
		outputFile.open(fileName + "_remove_green.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_remove_green.ppm" << " for writing...";
		applyRemoveGreen(imageData, outputFile);
	}
	else if (imageModification == "remove blue") {
		outputFile.open(fileName + "_remove_blue.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_remove_blue.ppm" << " for writing...";
		applyRemoveBlue(imageData, outputFile);
	}
	else if (imageModification == "gray scale") {
		outputFile.open(fileName + "_gray_scale.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_gray_scale.ppm" << " for writing...";
		applyGrayScale(imageData, outputFile);
	}
	else if (imageModification == "vertical flip") {
		outputFile.open(fileName + "_vertical_flip.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_vertical_flip.ppm" << " for writing...";
		applyVerticalFlip(imageData, outputFile);
	}
	else if (imageModification == "horizontal flip") {
		outputFile.open(fileName + "_horizontal_flip.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_horizontal_flip.ppm" << " for writing...";
		applyHorizontalFlip(imageData, outputFile);
	}
	else if (imageModification == "random 50") {
		outputFile.open(fileName + "_random_50.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_random_50.ppm" << " for writing...";
		applyRandomNoise(imageData, outputFile);
	}
	else {
		outputFile.open(fileName + "_complex_image_mod.ppm");
		cout << "Opening " << fileName + ".ppm" << " for reading and " << fileName + "_complex_image_mod.ppm" << " for writing...";
		applyComplexImageMod(imageData, outputFile);
	}
}
 /*************************************************************
 * Function: applyNegative()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function calls upon the computeNegativeValue 
 *				function and the new values are written to the 
 *				output file and applies a negative filter.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyHighContrast()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function calls upon the computeHighContrastValue 
 *				function and the new values are written to the 
 *				output file and applies a high contrast filter.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyRemoveRed()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function writes the first value in the rgb 
 *				triple as 0 and the other two values remain the  
 *				same to the output file and the image is removed 
 *				of red.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyRemoveGreen()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function writes the middle value in the rgb 
 *				triple as 0 and the other two values remain the  
 *				same to the output file and the image is removed 
 *				of green.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyRemoveBlue()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function writes the last value in the rgb 
 *				triple as 0 and the other two values remain the  
 *				same to the output file and the image is removed 
 *				of blue.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyGrayScale()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function calls upon the computeGrayScaleValue 
 *				function and the new values are written to the 
 *				output file and applies a gray scale filter.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
			rgbTriple
			.clear();
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"gray scale\" complete. Closing files..." << endl;
}
 /*************************************************************
 * Function: applyVerticalFlip()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function iterates the values of the rows in 
 *				reverse and the new values are written to the 
 *				output file and the image is vertically flipped.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyHorizontalFlip()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function iterates the values of the cols in 
 *				reverse and the new values are written to the 
 *				output file and the image is horizontally flipped.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyRandomNoise()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function calls upon the computeRandomNoiseValue 
 *				function and the new values are written to the 
 *				output file and applies a random 50 filter.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
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
 /*************************************************************
 * Function: applyComplexImageMod()
 * Date Created: 04/28/19
 * Date Last Modified: 04/28/19          
 * Description: This function attempts to apply a horizontal blur 
 *				filter but ends up looking more like a vertical 
 *				scanline filter and the new values are written to 
 *				the output file.
 * Input parameters: A 3-D vector and output file must be pass by 
 *				reference.
 * Returns: nothing
 * Pre: A 3-D vector and output file must be pass by reference.
 * Post: A 3-D vector and output file are pass by reference.
 *************************************************************/
void applyComplexImageMod(const vector<vector<vector<short>>>& imageData, ofstream& outputFile) {
	int i = 0, j = 0, k = 0, sum1 = 0, sum2 = 0, sum3 = 0, average1 = 0, average2 = 0, average3 = 0;
	outputFile << specification << endl;
	outputFile << cols << " " << rows << endl;
	outputFile << maxRGB << endl;
	for (j = 0; j < rows; j++) {
		for (i = 0; i < cols; i+=5) {
			for (k = 0; k < 5; k++) {
				sum1 = sum1 + imageData[j][i+k][0];
				average1 = sum1 / 5;
				outputFile << average1 << " ";
				sum2 = sum2 + imageData[j][i+k][1];
				average2 = sum2 / 5;
				outputFile << average2 << " ";
				sum3 = sum3 + imageData[j][i+k][2];
				average3 = sum3 / 5;
				outputFile << average3 << " ";
			}
			sum1 = 0, sum2 = 0, sum3 = 0, average1 = 0, average2 = 0, average3 = 0;
		}
		i = 0;
		outputFile << endl;
	}
	outputFile.close();
	cout << "\nImage modification \"complex image mod\" complete. Closing files..." << endl;
}
