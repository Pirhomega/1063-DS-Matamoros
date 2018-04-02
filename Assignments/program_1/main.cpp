```cpp

/*
@ProgramName: Program-1
@Author: Corbin Matamoros
@Description:	
		This program reads in an image in RGB number format and outputs
		a manipulated version of it.
@Course: 1063 Data Structures
@Semester: Spring 2018
@Date: 03 02 2018
*/

#include<iostream>
#include<fstream>

using namespace std;

//creating a struct to hold the three rgb values
struct rgb 
{
	int r;
	int g;
	int b;
	rgb()	//constructor that initializes struct values whenever 
	{		//function's called
		r = 0;
		g = 0;
		b = 0;
	}
};

/*
@FunctionName: grayScale
@Description:	
			Loops through a 2D array, calculates the average of the rgb
			values, then assigns each position in the 2D array to the 
			average
@Params:	
			rgb** dummy - 2D array holding rgb values
			int width - width of the 2D array
			int height - height of the 2D array
@Returns: void
*/
void grayScale(rgb** dummy, int width, int height) 
{
	int r, g, b, gray;
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j<width; j++) 
		{
			r = dummy[i][j].r;
			g = dummy[i][j].g;
			b = dummy[i][j].b;

			gray = (r + g + b) / 3;

			dummy[i][j].r = gray;
			dummy[i][j].g = gray;
			dummy[i][j].b = gray;
		}
	}
}

/*
@FunctionName: flipVert
@Description:
	Loops through a 2D array and assigns to another equally-sized 2D array the
	values of the first 2D array to effectly flip the values vertically
@Params:
	rgb** image - 2D array to hold manipulated image
	rgb** dummy - 2D array holding rgb values of original image
	int width - width of the 2D arrays
	int height - height of the 2D arrays
@Returns: void
*/
void flipVert(rgb** image, rgb** dummy, int width, int height) 
{
	int i, j, row;

	ifstream ifile;
	ifile.open("Image.txt");

	row = height - 1;

	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j++) 
		{
			image[i][j].r = dummy[row][j].r;
			image[i][j].g = dummy[row][j].g;
			image[i][j].b = dummy[row][j].b;
		}
		row--;
	}
}

/*
@FunctionName: flipHoriz
@Description:
	Loops through a 2D array and assigns to another equally-sized 2D array the
	values of the first 2D array to effectly flip the values horizontally
@Params:
	rgb** image - 2D array to hold manipulated image
	rgb** dummy - 2D array holding rgb values of original image
	int width - width of the 2D arrays
	int height - height of the 2D arrays
@Returns: void
*/
void flipHoriz(rgb** image, rgb** dummy, int width, int height)
{
	int i, j, col;

	col = width - 1;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{	
			image[j][i].r = dummy[j][col].r;
			image[j][i].g = dummy[j][col].g;
			image[j][i].b = dummy[j][col].b;
		}
		col--;
	}
}

//main code
int main() 
{
	ifstream ifile;					//Input & output files
	ofstream ofile;
	ifile.open("Image.txt");
	ofile.open("imageManip.txt");

	int width, height, i, j, row;   //width and height of image

	rgb **imgArray;		//Pointer var for our 2D array because we         
	rgb **dummyArray;	//don't know how big the image will be!

	ifile >> width >> height; //Read in width and height from top of input file
							  //We need this so we can make the array the right 
							  //size. After we get these two values, we can
							  //now allocate memory for our 2D array.
	
	//These arrays point to every row
	imgArray = new rgb*[height]; 
	dummyArray = new rgb*[height];

	//Now allocate each row of rgb's for each array
	for (int i = 0; i<height; i++) 
	{
		imgArray[i] = new rgb[width];
		dummyArray[i] = new rgb[width];
	}

	//read in the rgb values into the dummy array
	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j++) 
		{
			ifile >> dummyArray[i][j].r >> dummyArray[i][j].g 
				>> dummyArray[i][j].b;
		}
	}

	//calls the first function to flip the rgb values vertically
	flipVert(imgArray, dummyArray, width, height);

	ofile << width << " " << height << '\n';
	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j++) 
		{
			ofile << imgArray[i][j].r << " " << imgArray[i][j].g << " "
				<< imgArray[i][j].b << " ";
		}
		ofile << '\n';
	}
	
	//calls the second function to flip the rgb values horizontally
	flipHoriz(imgArray, dummyArray, width, height);

	ofile << width << " " << height << '\n';
	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j++) 
		{
			ofile << imgArray[i][j].r << " " << imgArray[i][j].g << " "
				<< imgArray[i][j].b << " ";
		}
		ofile << '\n';
	}

	//calls last function to gray scale the image
	grayScale(dummyArray, width, height);

	ofile << width << " " << height << '\n';
	for (i = 0; i < height; i++) 
	{
		for (j = 0; j < width; j++) 
		{
			ofile << dummyArray[i][j].r << " " << dummyArray[i][j].g << " "
				<< dummyArray[i][j].b << " ";
		}
		ofile << '\n';
	}
	ofile.close();
	return 0;
}
```
