/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	Image *image=(Image*)malloc(sizeof(Image));
	fscanf(fp,"%*s%d%d%*d",&image->cols,&image->rows);
	image->image=(Color**)malloc(sizeof(Color*)*image->rows);
	for (int i=0;i<image->rows;++i)
	{
		image->image[i]=(Color*)malloc(sizeof(Color)*image->cols);
		for (int j=0;j<image->cols;++j)
			fscanf(fp,"%hhu%hhu%hhu",&image->image[i][j].R,&image->image[i][j].G,&image->image[i][j].B);
	}
	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n%d %d\n255\n",image->cols,image->rows);
	for (int i=0;i<image->rows;++i)
	{
		for (int j=0;j<image->cols;++j)
			printf("%s%3d %3d %3d",j?"   ":"",image->image[i][j].R,image->image[i][j].G,image->image[i][j].B);
		printf("\n");
	}
		
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	for (int i=0;i<image->rows;++i)
		free(image->image[i]);
	free(image->image);
	free(image);
}