#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	char *filename=argv[1],*hexstring=argv[2];
	uint32_t rule;
	printf("%s\n",hexstring);
	sscanf(hexstring,"%x",&rule);
	printf("%d\n",rule);
}
