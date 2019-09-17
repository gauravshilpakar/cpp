#include <iostream>
#include <string>
#include <fstream> //used for opening the txt file
#include <cctype> //used for changing input to uppercase

using namespace std;

//function declaration and definition for the new arrays after the selection of the color

//The new_colors address 'q' starts at 0 but the original's starts at the position of the selected color itself such that the selected color occupies the the first place of the new array.
//Then it continues till the original array reaches the final position [11]. 
//After that the original position resets to [0] and the first members of the original array get placed in the next continued positions of the new array.
void change_colors(string colors[], string new_colors[], int position,int size);
void change_colors(string colors[], string new_colors[], int position,int size)
{
	const int P = position; //
	int q = 0;
	while (position < 12) 
	{
		new_colors[q] = colors[position];
		position++;
		q++;
	}
position = 0;

	while (position < P)
	{
		new_colors[q] = colors[position];
		position++;
		q++;
	}
}

void change_hex(string hex[], string new_hex[], int position, int size);
void change_hex(string hex[], string new_hex[], int position, int size)
{
	const int P = position;
	int q = 0;
	while (position < 12)
	{
		new_hex[q] = hex[position];
		position++;
		q++;
	}
	position = 0;

	while (position < P)
	{
		new_hex[q] = hex[position];
		position++;
		q++;
	}
}

void change_RGB(string RGB[], string new_RGB[], int position, int size);
void change_RGB(string RGB[], string new_RGB[], int position, int size)
{
	const int P = position;
	int q = 0;
	while (position < 12)
	{
		new_RGB[q] = RGB[position];
		position++;
		q++;
	}
	position = 0;

	while (position < P)
	{
		new_RGB[q] = RGB[position];
		position++;
		q++;
	}
}

//function declaration and definition for complementary, triadic and tetradic colors!

void complementary(string new_colors[], string new_hex[], string new_RGB[], int position);
void complementary(string new_colors[], string new_hex[], string new_RGB[], int position)
{
	cout << "\n*****COMPLEMENTARY COLORS*****" << endl;
	cout << "\nThe selected color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;
	position=position + 6;

	cout << "\nIts Complementary Color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;
}

void triadic(string new_colors[], string new_hex[], string new_RGB[], int position);
void triadic(string new_colors[], string new_hex[], string new_RGB[], int position)
{
	cout << "\n*****TRIADIC COLORS*****" << endl;
	cout << "\nThe first triadic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_colors[position] << endl;

	position += 4;
	cout << "\nThe second triadic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;

	position += 4;
	cout << "\nThe third triadic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;
}

void tetradic(string new_colors[], string new_hex[], string new_RGB[], int position);
void tetradic(string new_colors[], string new_hex[], string new_RGB[], int position)
{
	cout << "\n*****TETRADIC COLORS*****" << endl;
	cout << "\nThe first tetradic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;

	position += 2;
	cout << "\nThe second tetradic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;

	position += 4;
	cout << "\nThe third tetradic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;

	position += 2;
	cout << "\nThe fourth tetradic color is " << new_colors[position] << endl;
	cout << "Its hexadecimal code is " << new_hex[position] << endl;
	cout << "Its RGB combination is " << new_RGB[position] << endl;
}

int main()
{
	string colors[12];	//--1
	string hex[12];		//--2
	string RGB[12];		//--3

//-----Reading the file-----
//for file color.txt-----------------1
	ifstream ifc("colors.txt");
	int i(0);
		while (colors[i].empty())
		{
			getline(ifc, colors[i]);
			i++;
		}
		ifc.close();
//for file hex.txt-------------------2
	ifstream ifh("hex.txt");
	int j(0);
		while (hex[j].empty())
		{
			getline(ifh, hex[j]);
			j++;
		}
		ifh.close();
//for file color.txt-----------------3
	ifstream ifR("RGB.txt");
	int k(0);
		while (RGB[k].empty())
		{
			getline(ifR, RGB[k]);
			k++;
		}
		ifR.close();

//-----Asking for input-----
	cout << "Type the name of the color whose color harmonies you would like to study: " << endl;
	for (int i = 0; i < 12; i++)
	{
		cout << i + 1 << ". " << colors[i] << endl;
	}
	cout << "\nEnter your input here (for example: For 1, type 'RED') ";

	char input[20] = {'\0'}; //declaring the input given by the user
	char temp_input[20]= {'\0'}; //temp_input for changing all the characters entered to uppercase

//-----Input Validation-----
	bool x = 0;
	string A; //new string to check the validity
	while(x==0)
	{
		cin.getline(input, 20);

		for (int i = 0; i < 20;i++) //loop to change all characters in the input to uppercase
		{
			char a = input[i];
			a = toupper(a);		//the conversion is being done one character at a time and stored in a new cstring "temp_input"
			temp_input[i] = a;
		}
		cout << "Your input is: " << temp_input << endl;

		A=temp_input; //A takes the input given by the user converted into uppercase
		if ((A == colors[0] || A == "ORANGE" || A == "YELLOW" || A == "CHARTREUSE GREEN" || A == "GREEN" || A == "SPRING GREEN" || A == "CYAN" || A == "AZURE" || A == "BLUE" || A == "VIOLET" || A == "MAGENTA" || A == "ROSE"))
			x++; 
		else
		{
			cout << "Invalid selection. Try again!" << endl;
			cout << "\nEnter your input here (for example: For 1, type 'RED') ";
		}
	}
//*****Finding the position of the input in the original colors string*****
	int position;
	for (int i = 0; i < 12; i++)
	{
		if (A == colors[i])
		{
			position = i;
			break;
		}
	}	

//*****Declaring new strings*****
	string new_colors[12];
	string new_hex[12];
	string new_RGB[12];

//*****Function call for changing strings*****
	change_colors(colors,new_colors, position, 12);
	change_hex(hex, new_hex,  position, 12);
	change_RGB(RGB, new_RGB, position, 12);

	position = 0; //since the selected color now has the first position in the new string

	//*****Function call for the color harmonies*****
	complementary(new_colors,  new_hex,  new_RGB, position);
	triadic(new_colors, new_hex, new_RGB, position);
	tetradic(new_colors, new_hex, new_RGB, position);

	system("pause");
	return 0;
}

