#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

typedef int* IntPtrArray; //pointer type created to make an array which stores coordinates of key

using namespace std;

string P2;
string pgm;
string editedpgm;
string text;
ifstream fin;
ofstream fout;

int edited[2000][2000];
int temp[2000][2000];
int flip[2000][2000];

//function declarations
void OScheck();
void coordinatetobinary(int val[], int size, int binaryofval[]);
void concatenatebinary(int binaryofval[], int size);
void binaryToDecimal(int bits[], int decbits[], int loop);

void contraststretching(int **a, int width, int height);
void negative(int **a, int height, int width);
void flipimage(int **a, int height, int width);
void histE(int **a, int height, int width);

//function definitions
void OScheck()
{
	// apple Xcode vs anything else
#ifdef __APPLE__
	cout << "Running on:\tMacOS" << endl;
#else
	cout << "Running on:\tWindows" << endl;
#endif
	// MS Visual Studio vs anything else
#ifdef _MSC_VER
	cout << "IDE:\t\tVS" << endl;
#elif __APPLE__
	cout << "IDE:\t\tXCODE" << endl;
#else
	cout << "IDE:\t\tOther" << endl;
#endif
#ifdef _WIN32
	cout << "Console:\tWIN32" << endl;
#else
	cout << "Console:\tnotWIN32" << endl;
#endif
	// Visual Studio, Xcode or anything else
}
void coordinatetobinary(int val[], int size, int binaryofval[])
{
	int x = 0;
	for (int i = 0; i < size; i++) //checks if the val is even or odd and stores 1 or 0 respectively as LSB
	{
		if (val[i] % 2 == 0)
		{
			binaryofval[x] = 0;
		}
		else if (val[i] % 2 == 1)
		{
			binaryofval[x] = 1;
		}
		x++;
	}
}
void concatenatebinary(int binaryofval[], int size)
{
	int sevenbits[7];				//takes binary bits in groups of 7 as integers
	string stringbits[7];			//takes binary bits in groups of 7 as strings
	string concatenatedbits[500];	//stores the concatenated groups of binary bits
	int bits[500]; 
	int decbits[500];

	int loop = size / 7;
	cout << "\nNumber of hidden characters: " << loop << endl;
	
	for (int j = 0; j < loop; j++)
	{
		sevenbits[0] = binaryofval[(7 * j) + 0];
		sevenbits[1] = binaryofval[(7 * j) + 1];
		sevenbits[2] = binaryofval[(7 * j) + 2];
		sevenbits[3] = binaryofval[(7 * j) + 3];
		sevenbits[4] = binaryofval[(7 * j) + 4];
		sevenbits[5] = binaryofval[(7 * j) + 5];
		sevenbits[6] = binaryofval[(7 * j) + 6];

		for (int i = 0; i < 7; i++)
		{
			stringbits[i]=to_string(sevenbits[i]); //converts the binary bits to string for concatenations 
		}

		//concatenated from back to front. Reversed because originally the converted char didn't give sensible hidden message
		concatenatedbits[j] = stringbits[6] + stringbits[5] + stringbits[4] + stringbits[3] + stringbits[2] + stringbits[1] + stringbits[0];
	}

	for (int i = 0; i < loop; i++)
	{
		bits[i] = stoi(concatenatedbits[i]); //converts concatenated bits of string into int
	}

	binaryToDecimal(bits, decbits, loop); //calls function to convert the binary into decimal 
}
void binaryToDecimal(int bits[], int decbits[], int loop)
{
	for (int j = 0; j < loop; j++)
	{
		int output = 0;
		int num = bits[j];
		for (int i = 0; num > 0; i++)
		{
			if (num % 10 == 1) {
				output += pow(2, i);
			}
			num /= 10;
		}

		decbits[j] = output;
	}

	cout << "The hidden message is: ";
	for (int k = 0; k < loop; k++) //converts the decimal value to equivalent character.
	{
		char message = static_cast <char> (decbits[k]);
		cout << message;
	}
	cout << endl;
}

void histE(int **a, int height, int width)
{
	double histogram[256];
	double histFactors[256], cumulativeProb[256], lastSum(0);
	int p(0);

	for (int i = 0; i < 256; i++)
		histogram[i] = 0;
	for (int m = 0; m < height; m++)
	{
		for (int n = 0; n < width; n++)
		{
			p = temp[m][n];
			histogram[p] += 1;
		}
	}
	for (int i = 0; i < 256; i++)
	{

		histFactors[i] = ((histogram[i]) / (height*width));
	}

	for (int i = 0; i < 256; i++)
	{
		lastSum += histFactors[i];
		cumulativeProb[i] = lastSum;
	}
	for (int m = 0; m < height; m++)
	{
		for (int n = 0; n < width; n++)
		{
			p = a[m][n];
			temp[m][n] = round(cumulativeProb[p] * 255);
		}
	}
}
void contraststretching(int **a, int height, int width)
{
	int lower = 0;
	int upper = 255;
	int lowest = 255;
	int highest = 0;
	int	currentVal;

	for (int i = 0; i < height; i++) //finds the lowest and highest pixel value from the pgm
	{
		for (int j = 0; j < width; j++)
		{
			if (temp[i][j] < lowest)
			{
				lowest = temp[i][j];
			}
			if (temp[i][j] > highest)
			{
				highest = temp[i][j];
			}
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			currentVal = temp[i][j];
			temp[i][j] = round((currentVal - lowest)*((upper - lower) / (highest - lowest))) + (lower); //does contrast stretching based on the code in the project pdf 
		}
	}
}
void negative(int **a, int height, int width)
{
	for (int i = 0; i < height; i++) //inverts the pgm image by subracting the pixel value from the maximum possible pixel value
	{
		for (int j = 0; j < width; j++)
		{
			temp[i][j] = 255 - temp[i][j];
		}
	}
}
void flipimage(int **a, int height, int width) //flips the image by performing a matrix inverse
{
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++)
		{
			flip[i][j] = temp[height - 1 - i][width - 1 - j];
		}
	}
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++)
		{
			temp[i][j] = flip[i][j];	
		}
	}
}

int main()
{
	//OS validation
	OScheck(); 
	bool program = 0;
	while (program == 0)
	{
		bool check = 0;
		while (check == 0) //loop to validate user input
		{
			for (int i = 0; i < 2000; i++) //resets the arrays to make new changes
			{
				for (int j = 0; j < 2000; j++)
				{
					edited[i][j] = 0;
					temp[i][j] = 0;
					flip[i][j] = 0;
				}
			}

			cout << "\nWhich image would you like to process? Please select the file!\n" << endl;
			cout << "1S.pgm" << "\n2S.pgm" << "\n3S.pgm" << "\n4S.pgm" << "\n5S.pgm" << endl;
			cout << "\nPlease type the full name of the file exactly as shown on the list: ";
			cin >> pgm;
			if (pgm == "1S.pgm")
			{
				text = "key1.txt";
				check = 1;
			}
			else if (pgm == "2S.pgm")
			{
				text = "key2.txt";
				check = 1;
			}
			else if (pgm == "3S.pgm")
			{
				text = "key3.txt";
				check = 1;
			}
			else if (pgm == "4S.pgm")
			{
				text = "key4.txt";
				check = 1;
			}
			else if (pgm == "5S.pgm")
			{
				text = "key5.txt";
				check = 1;
			}
			else if (pgm == "1demo.pgm")
			{
				text = "key1demo.txt";
				check = 1;
			}
			else
			{
				cout << "Invalid Selection! Try Again!" << endl;
				check = 0;
			}
		}
		cout << "\nYou selected the file " << pgm << " for processing.\n" << endl;

		//code to read the pgm file

		int width, height, maxval; // Sizes needed for the array
		fin.open(pgm);
		if (!fin)
			cout << "The file does not exist" << endl; //if there is no file
		fin >> P2 >> width >> height >> maxval;
		cout << "Width: " << width << " Height: " << height << " Max Val: " << maxval << endl;

		int **a = new int *[height]; // pointer variable to dynamically create the 1st dimension of the array
		for (int i = 0; i < height; i++)
			a[i] = new int[width]; // The elements of the 2nd dimension are created here

		for (int i = 0; i < height; i++) // this fills in the 2D image array
		{
			for (int j = 0; j < width; j++)
			{
				fin >> a[i][j]; 
			}
		}

		for (int i = 0; i < height; i++) //copies pixel values from pgm to temp array for editing
		{
			for (int j = 0; j < width; j++)
			{
				temp[i][j]= a[i][j];
			}
		}

		//code to read key txt file
		ifstream ifs(text);
		if (!ifs)
		{
			//Checks if file reading fails
			cerr << "Error: could not find the specified file. Terminating Program..." << endl << endl;
		}

		int size;
		ifs >> size; //size is the number of coordinates for hidden message which is the first number in the txt file

		IntPtrArray *coordinate = new IntPtrArray[size];
		for (int x = 0; x < size; x++)
			coordinate[x] = new int[2]; //coordinate is now a size by 2 array which stores the coordinates of the pgm file for the hidden message

		//this loop retrieves rest of the number from the txt in the form of [size][2] array
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < 2; j++)
				ifs >> coordinate[i][j];
		}

		int val[500]; //val array stores the value of pgm which is pointed at by the corresponding coordinate
		int m, n;

		for (int i = 0; i < size; i++) //iterates through the total number of coordinates
		{
			m = coordinate[i][0];
			n = coordinate[i][1];
			val[i] = a[m][n];
		}

		int binaryofval[500];							//binaryofval stores the LSB of pgm value
		coordinatetobinary(val, size, binaryofval);		//function call to store the LSB of the pgm in binaryofval
		concatenatebinary(binaryofval, size);			//function call to concatenate all the LSB 


		//this if-else performs all the necessary editing to the selected image
		if (pgm == "1S.pgm")
		{
			cout << "\nThe image " << pgm << " needs histogram equalization.\n..." << endl;
			histE(a, height, width);
		}
		else if (pgm == "2S.pgm")
		{
			cout << "\nThe image " << pgm << " needs contrast stretching.\n..." << endl;
			contraststretching(a, height, width);
		}
		else if (pgm == "3S.pgm")
		{
			cout << "\nThe image " << pgm << " needs histogram equalization, should be negative and flipped.\n..." << endl;
			histE(a, height, width);
			negative(a, height, width);
			flipimage(a, height, width);
		}
		else if (pgm == "4S.pgm")
		{
			cout << "\nThe image " << pgm << " needs histogram equalization and should be negative.\n..." << endl;
			histE(a, height, width);
			negative(a, height, width);		
		}
			else if (pgm == "5S.pgm")
		{
			cout << "\nThe image " << pgm << " needs contrast stretching, should be negative and flipped.\n..." << endl;
			flipimage(a, height, width);
			contraststretching(a, height, width);
			negative(a, height, width);
		}

		for (int i = 0; i < height; i++) //copies pixel values from temp to edited array for outputing
		{
			for (int j = 0; j < width; j++)
			{
				edited[i][j] = temp[i][j];
			}
		}

		for (int i = 0; i < size; i++)
			delete[] coordinate[i];
		delete[] coordinate;

		for (int i = 0; i < height; i++)
			delete[] a[i];
		delete[] a;

		string pgmHeader = "P2"; //header created to output the edited file
		editedpgm = "edited_" + pgm;
		fout.open(editedpgm); // outputs a file
		fout << pgmHeader << " " << width << " " << height << " " << maxval << "\n";

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				fout << edited[i][j] << " ";
			}
		}

		bool checkagain=0;
		int again;
		while (checkagain == 0)
		{
			cout << "Do you want to continue with a new file or exit? \nType 1 to continue or 2 to exit! ";
				cin >> again;
			if (again == 1)
			{
				cout << "Continue!\n" << endl;
				checkagain = 1;
				program = 0;
			}
			else if (again == 2)
			{
				cout << "Exiting Program!" << endl;
				checkagain = 1;
				program = 1;
			}
			else
			{
				cout << "Invalid Option! Try again!\n" << endl;
				checkagain = 0;
			}
		}
	}
	system("pause");
	return 0;
}


