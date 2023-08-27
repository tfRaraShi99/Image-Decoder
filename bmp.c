#include"bmp.h"
#include<stdio.h>

void read_bmp_header(__bmp_file *file){
	file->stream=fopen(file->path,"r");
	fread(&file->bmp_header.signature,2,1,file->stream);
	fread(&file->bmp_header.file_size,4,1,file->stream);
	fread(&file->bmp_header.reserved1,2,1,file->stream);
	fread(&file->bmp_header.reserved2,2,1,file->stream);
	fread(&file->bmp_header.offset_pixel_array,4,1,file->stream);
	fclose(file->stream);	
}
void read_dib_header(__bmp_file *file){
	file->stream=fopen(file->path,"r");
	fseek(file->stream,14,SEEK_SET);
	fread(&file->dib_header.header_size,4,1,file->stream);
	fread(&file->dib_header.img_width,4,1,file->stream);
	fread(&file->dib_header.img_height,4,1,file->stream);
	fread(&file->dib_header.color_plane,2,1,file->stream);
	fread(&file->dib_header.bits_per_pixel,2,1,file->stream);
	fread(&file->dib_header.compression,4,1,file->stream);
	fread(&file->dib_header.img_raw_size,4,1,file->stream);
	fread(&file->dib_header.v_pixel_per_mtr,4,1,file->stream);
	fread(&file->dib_header.h_pixel_per_mtr,4,1,file->stream);
	fread(&file->dib_header.colors,4,1,file->stream);
	fclose(file->stream);
}