#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cs1300bmp.h"
#include "cs1300bmp.cc"

using namespace std;
/*
	In this part you'll be implementing 2 filters.
	1. green filter
	2. blue filter

	Before you can do any operation on images, you'll
	have to read the image file into the program.
	You can read and write "bmp" images using the functions
	1. cs1300bmp_readfile()
	and
	2. cs1300bmp_writefile() respectively.

	cs1300bmp_readfile(image_file_name, cs1300bmp_struct):
		1.	The data read from an image on the disk with path
			image_file_name is stored in the cs1300bmp_structure.

		2.	The structure holds 3 things:
				a.	The HEIGHT of the image (int).
				b.	The WIDTH of the image (int).
				c.	A 3D array storing the colors
					of every pixel in the image.

		3.	I suggest you to look at the declaration of the
			structure in file cs1300bmp.h @ line#18.

		4.	Most of the manipulations that you will be doing in
			this project will be on the color field of the
			cs1300bmp structure.

	cs1300bmp_writefile(output_file_name, cs1300bmp_structure):
		1.	Similar to the cs1300bmp_readfile function, except in this
			case, the function will be writing the data from the
			cs1300bmp_structure to the file defined by the
			output_file_name value onto the disk.
*/

/*
	While implementing the below functions based on the
	introduction mentioned in the attached pdf document,
	do not forget to set the width and height values of
	the new cs1300bmp structure.
	HINT: the values will be same as the dimensions of the
	inImage structure.
*/

/*
	We have implemented the red_filter for you. Go through
	it and comment your understanding below.
	HERE:
    
    The red_filter function takes an image using the cs1300bmp structure
    which holds the basic essential data components of an image for manipulation
    (width, height, and color -- char array RGB fields). Looking at cs1300bmp header file,
    we see it takes the image and extracts its actual width and height which we can see below
    in the red_filter coding for outImage->width = inImage->width and setting those values as int 
    rows and cols to be iterated through. The settings for red_filter are adjusted in accordance
    with setting the 'R' field as 0, while maintaining the 'G' and 'B' fields. The same principle
    will be applied when setting up the green_filter and blue_filter, meaning we will set initialize
    the width and height of image then set the corresponding color fields to 0 to create color filters.

*/

void red_filter(cs1300bmp *inImage, cs1300bmp *outImage) {

	outImage->width = inImage->width;
	outImage->height = inImage->height;

	int rows = outImage->height;
	int cols = outImage->width;

	for (int i = 0; i <= rows; ++i) {
		for (int j = 0; j <= cols; ++j) {
			outImage->color[0][i][j] = 0;   //setting 'R' value to 0
			outImage->color[1][i][j] = inImage->color[1][i][j];
			outImage->color[2][i][j] = inImage->color[2][i][j];
		}
	}
}

/*
	*************************************************************
					TODO GREEN_FILTER
	*************************************************************

	Implement the green filter here.
	HINT: Colors in the green channel should be 0.
*/
void green_filter(cs1300bmp *inImage, cs1300bmp *outImage) {
    
    outImage->width = inImage->width;
	outImage->height = inImage->height;

	int rows = outImage->height;
	int cols = outImage->width;

	for (int i = 0; i <= rows; ++i) {
		for (int j = 0; j <= cols; ++j) {
			outImage->color[0][i][j] = inImage->color[0][i][j];
			outImage->color[1][i][j] = 0;     //setting 'G' value to 0
			outImage->color[2][i][j] = inImage->color[2][i][j];
		}
	}
}
/*
	*************************************************************
					TODO GREEN_FILTER ENDS
	*************************************************************
*/

/*
	*************************************************************
					TODO BLUE_FILTER
	*************************************************************


	Implement the blue filter here.
	HINT: Colors in the blue channel should be 0.
*/
void blue_filter(cs1300bmp *inImage, cs1300bmp *outImage) {
    
    outImage->width = inImage->width;
	outImage->height = inImage->height;

	int rows = outImage->height;
	int cols = outImage->width;

	for (int i = 0; i <= rows; ++i) {
		for (int j = 0; j <= cols; ++j) {
			outImage->color[0][i][j] = inImage->color[0][i][j];
			outImage->color[1][i][j] = inImage->color[1][i][j];
			outImage->color[2][i][j] = 0;    //setting 'B' value to 0
		}
	}
}
/*
	*************************************************************
					TODO BLUE_FILTER ENDS
	*************************************************************
*/
int
main(int argc, char *argv[]) {
	//	This is how you mention the file name.
	//	for the images that you need to read and
	//	write as mentioned in the project PART 1.A
	//	description.
	string inputfilename = "images/bmp/1.bmp";
	//	Output file name for the red filter image.
	string outputfilename_red_filter = "images/part_1/1_red_filter.bmp";
	//	Output file name for the red filter image.
	string outputfilename_blue_filter = "images/part_1/1_blue_filter.bmp";
	//	Output file name for the red filter image.
	string outputfilename_green_filter = "images/part_1/1_green_filter.bmp";

	cout << "Read file " << inputfilename << endl;
	//	Below, we have declared
	//	the structure where you will read the
	//	file mentioned.
	cs1300bmp *inImage = new cs1300bmp;

	//	Similarly create a structure which will hold the
	//	modified image data.
	cs1300bmp *outImage = new cs1300bmp;

	// Read the file to be filtered
	int result = cs1300bmp_readfile(inputfilename, inImage);

	if ( result ) {
		cout << "Adding Green Filter" << endl;
		green_filter(inImage, outImage);
		cout << "Writing output image to " << outputfilename_green_filter << endl;
		cs1300bmp_writefile(outputfilename_green_filter, outImage);


		//	The above 4 lines, apply a red_filter onto the inImage and
		//	store the data in the outImage.
		//	Later, the data in the outImage is written onto the disk using the
		//	function cs1300bmp_writefile.

		//	**********************************************************
		//							TODO
		//	**********************************************************
		//	Similarly apply the blue as well as the green filter.
		//	This part will be graded on the output of the images that
		//	has been read and not the statements that are printed on the
		//	console.
        //
        //
        //  I individually modified the scripts/code for red/blue/green filter to produce the images
        //  the parts that need to be modified are blue_filter, outputfilename_blue_filter, "Adding Blue Filter" for 
        //  respective colors R,G,B.
        /*/     
            Examples:
            cout << "Adding Blue Filter" << endl;
            blue_filter(inImage, outImage);
            cout << "Writing output image to " << outputfilename_blue_filter << endl;
            cs1300bmp_writefile(outputfilename_blue_filter, outImage);
    
            cout << "Adding Blue Filter" << endl;
            blue_filter(inImage, outImage);
            cout << "Writing output image to " << outputfilename_blue_filter << endl;
            cs1300bmp_writefile(outputfilename_blue_filter, outImage);
        
        /*/
	}
    else {
        cout << "Unable to read image" << endl;
    }
    return 0;
}
