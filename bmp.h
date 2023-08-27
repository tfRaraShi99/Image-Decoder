#include <stdio.h>
#include<stdlib.h>
typedef struct
{
	unsigned short signature;
	unsigned int file_size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int offset_pixel_array;

}__bmp_header;


typedef struct{
	unsigned int header_size;
	unsigned int img_width;
	unsigned int img_height;
	unsigned short color_plane;
	unsigned short bits_per_pixel;
	unsigned int compression;
	unsigned int img_raw_size;
	float v_pixel_per_mtr;
	float h_pixel_per_mtr;
	unsigned int colors;

}__dib_header;


typedef struct{
	char *path;
	FILE *stream;
	__bmp_header bmp_header;
	__dib_header dib_header;

}__bmp_file;


void read_bmp_header(__bmp_file *file);
void read_dib_header(__bmp_file *file);