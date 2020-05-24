#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string.h>
#include "cs1300bmp.h"
#include "cs1300bmp.cc"
#include "csvdata.h"
#define ROWS 128
#define COLUMNS 128
#define CHANNELS 3

using namespace std;

/*
	TODO
	Now we will put everything that we have learned together.
	Implement this script to do the following functions:
	1.	Read A CSV file from the image_csv folder.
	2.	Convert the read data to a bmp image by copying the
		data from the csv_data structure to the cs1300bmp
		structure.
	3.	Write the bmp to the disk.
	4.	Apply transformations such as:
		1. Invert
		2. Hflip
		3. VFlip
	5.	Save each of the above transformed images to the disk.


	You can reuse the functions from the parts 1, 2, 3.

	Grading will be based on the comments and your understanding of the functions.
*/



/*/
	The readData function will read a .csv file (from the image_csv folder) and store the data
    as a csvdata structure, in order to be converted to the cs1300bmp structure. Here we are extrapolating 
    the necessary data from the .csv file (as not all files are in .bmp, .jpeg, etc formats) such as color array 
    information and placing them into a structure, here the csv_data structure. This is done by 
    initializing variables to pull information (getline function) from the .csv files and relay them using rows/columns in an array. 
    
*/
int readData(csvdata* _csv_data, string&  _file_name) {
	ifstream input_file_stream;
	input_file_stream.open(_file_name);

	int result = 0;
	int row_idx = 0, col_idx = 0;
	int value = 0;
	stringstream sstream;
	string line;
	char c;
	string color_value;
	while (!input_file_stream.eof()) {
		sstream.clear();
		getline(input_file_stream, line);
		sstream.str(line);
		col_idx = 0;
		
		while (sstream) {
			getline(sstream, color_value, ',');
			value = stoi(color_value);
			_csv_data->data[row_idx][col_idx] = value;
			col_idx += 1;
		}
		row_idx += 1;
	}
	return result;
}

/*
    The copy function was our TODO for part_2 which takes the .csv information we just pulled
    from our readData function and copies the data to a cs1300bmp structure using the same format.
    This is done by initializing height/width of cs1300bmp structure converted and accessing those
    elements from the csvdata structure. We then iterate through the rows of the 2d array and separating 
    them into 3d array of bitmap strucutre, one for each of the RGB color fields. 
*/
int
copy(csvdata *_csv_data, cs1300bmp *_image) {
    _image->height = ROWS;
    _image->width = COLUMNS;

    for (int i = 0; i < _image->height; ++i) {
        for (int j = 0; j < _image->width; ++j) {
        _image->color[0][ROWS - i][j] = _csv_data->data[i*3][j];
        _image->color[1][ROWS - i][j] = _csv_data->data[i*3+1][j];
        _image->color[2][ROWS - i][j] = _csv_data->data[i*3+2][j];
     }
}
}

/*
    Now, introducing functions from part_3 to manipulate the bmp images: 
    The swap function is going to be declared for "swapping" the pixel arrays,
    in order to vertically (v_flip) and horizontally (h_flip) flip the images 
    (functions called and explained below). The swap function takes two integers
    and exchanges the values with one another so that flipping images can be achieved.
*/
void
swap(int &a, int &b) {
    
 int temp ;
 temp = a ;
 a = b ;
 b = temp ;
}


/*
    The invert function will invert and manipulate the colors within the image to 
    create the 90s popculture feel. THe function iterates through the cs1300bmp structure
    and manipulates the color arrays by subtracting the image intensity from the max intensity 
    values of 255 from each of the RGB color fields. The function was similar to part_1 when
    using color filters as it assigns and manipulates the various arrays (except in this case, all three
    color fields are altered simultaneously).
*/
void
invert(cs1300bmp *_image) {
    for (int i = 0; i < _image->height; ++i) {
        for (int j = 0; j < _image->width; ++j) {
        _image->color[0][i][j] = 255 - _image->color[0][i][j];
        _image->color[1][i][j] = 255 - _image->color[1][i][j];
        _image->color[2][i][j] = 255 - _image->color[2][i][j];
         }
    }
}

/*
	The h_flip function flips the image along the horizonal plane (or y-axis). So, in the case of the two parrots,
    they will now be looking and facing in the opposite direction. Again, the cs1300bmp structure is manipulated through
    the iteration of rows/columns. The swap function introduced earlier is used to exchange values of "opposite" cells to flip
    the image horizontally. 
*/
void
h_flip(cs1300bmp *_inImage) {
	for (int row = 0; row < _inImage->height; ++row) {
		for (int col = 0; col < _inImage->width/2; ++col) {
			for (int channel = 0; channel < CHANNELS; ++channel) {
				swap(_inImage->color[channel][row][col], _inImage->color[channel][row][_inImage->width - col]);
			}
		}
	}
}

/*
	The v_flip function flips the image along the vertical plane (or x-axis) in a very similar manner to the h_flip function. 
    Again, with the case of the two parrots, the resulting image will have the parrots upside-down after the resulting v_flip. 
    The cs1300bmp structure is manipulated through the iteration of rows/columns and again, the swap function is used to exchange 
    values of "opposite" corresponding cells to flip the image vertically. 
*/
void
v_flip(cs1300bmp *_inImage) {
    for (int col = 0; col < _inImage->width; ++col) {
        for (int row = 0; row < _inImage->height/2; ++row) {
            for (int channel = 0; channel < CHANNELS; ++channel) {
				swap(_inImage->color[channel][row][col], _inImage->color[channel][_inImage->height - row ][col]);
			}
		}
	}
}





int
main(int argc, char *argv[]) {
	/*
    From the part_2 main code, the readData function uses the string file_name to retrieve
    the particular .csv data and also sets the string image_file_name when file is written to 
    the part_4 directory after conversion into cs1300bmp structure format and images. I combined and 
    initialized the other string file_name for use with part_3 code for inverting and flipping functions. 
	*/
	string file_name = "image_csv/2.csv";
	string image_file_name = "images/part_4/2.bmp";
    string invert_file_name = "images/part_4/2_inverted.bmp";
	string h_flip_file_name = "images/part_4/2_h_flipped.bmp";
	string v_flip_file_name = "images/part_4/2_v_flipped.bmp";
	
    /*
	The readData function is called to extract the necessary .csv data to be stored in the csvdata 
    structure with the file_name csv mentioned above. The result is a cs1300bmp structure to be used for
    image manipulation.
	*/
	csvdata *csv_data = new csvdata;
	int result = readData(csv_data, file_name);


    cs1300bmp *inImage = new cs1300bmp;

	/*
    These next couple lines of code call the copy function in order to copy the elements pulled 
    from the csvdata structure and implemented into the cs1300 bmp structure (2D to 3D array). In the cases 
    of structures, the "new" operator initializes the memory and returns the address of the newly allocated 
    and initialized memory to the pointer variable (https://www.geeksforgeeks.org/new-vs-operator-new-in-cpp/).
    The cs1300bmp_writefile function takes information collected into the cs1300 bmp structure (pulled from .csv file) 
    and writes the data to the output image_file_name mentioned above onto the disk.
	*/
	copy(csv_data, inImage);

	cs1300bmp_writefile(image_file_name, inImage);
    
    /*
    Now that the data from csvdata structure has been pulled and stored into the cs1300 bmp structure and the resulting bmp
    has been written to the disk, we can introduce functions for manipulating the bmp image (invert/h_flip/v_flip).The bmp file 
    is read and the invert function is called for creating the 90s look, along with h_flip and v_flip
    functions following to flip the images horizontally and vertically. From the part_3 main code, the bmp image created from the 
    csvdata structure is referred to for image manipulation and addresses string file_name. The manipulation effects are accumulated 
    in the order of the function listing (invert->h_flip->v_flip). After image is manipulated, the cs1300bmp_writefile function
    writes the altered images to disk as the specified directory locations.
	*/ 

	cs1300bmp_readfile(image_file_name, inImage);
	invert(inImage);
	cs1300bmp_writefile(invert_file_name, inImage);

	h_flip(inImage);
	cs1300bmp_writefile(h_flip_file_name, inImage);

	v_flip(inImage);
	cs1300bmp_writefile(v_flip_file_name, inImage);
    
	return 0;

}
