/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
uint8_t pick(Color c,char color)
{
	switch (color)
	{
		case 'R':
			return c.R;
		case 'G':
			return c.G;
		default:
			return c.B;
	}
}
uint8_t is_live(Image *image,int row,int col,uint32_t rule,int bit,char color)
{
	int dx[]={-1,-1,-1,0,0,1,1,1},dy[]={-1,0,1,-1,1,-1,0,1},cnt=0;
	for (int i=0;i<8;++i)
	{
		int x=(row+dx[i]+image->rows)%image->rows,y=(col+dy[i]+image->cols)%image->cols;
		cnt+=pick(image->image[x][y],color)>>bit&1;
	}
	uint8_t now=pick(image->image[row][col],color)>>bit&1;
	return now?rule>>(8+cnt)&1:rule>>cnt&1;
}

Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color *color=(Color*)malloc(sizeof(Color));
	color->R=color->G=color->B=0;
	for (int i=0;i<8;++i)
	{
		color->R+=is_live(image,row,col,rule,i,'R')<<i;
		color->G+=is_live(image,row,col,rule,i,'G')<<i;
		color->B+=is_live(image,row,col,rule,i,'B')<<i;
	}
	return color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *iteration=(Image*)malloc(sizeof(Image));
	iteration->rows=image->rows;
	iteration->cols=image->cols;
	iteration->image=(Color**)malloc(sizeof(Color*)*iteration->rows);
	for (int i=0;i<image->rows;++i)
	{
		iteration->image[i]=(Color*)malloc(sizeof(Color)*iteration->cols);
		for (int j=0;j<image->cols;++j)
		{
			Color *color=evaluateOneCell(image,i,j,rule);
			iteration->image[i][j]=*color;
			free(color);
		}
	}
	return iteration;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	char *filename=argv[1],*hexstring=argv[2];
	Image *image=readData(filename);
	uint32_t rule;
	// printf("%s\n",hexstring);
	sscanf(hexstring,"%x",&rule);
	// printf("%d\n",rule);
	Image *iteration=life(image,rule);
	writeData(iteration);
	freeImage(image);
	freeImage(iteration);
}
