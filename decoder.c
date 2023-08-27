#include<stdio.h>
#include<stdlib.h>
#include"bmp.h"
#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>
void main(int argc, char *argv[]){
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_EVERYTHING);
	__bmp_file bmp_file;
	                             /*The file is opened in read mode*/
	
        //bmp_file.path="new.bmp";
	/*to open any bmp file throughg this code uncommand the below line*/
	bmp_file.path=argv[1];
	
	read_bmp_header(&bmp_file);
	printf("Type of file: %c%c\n",bmp_file.bmp_header.signature,bmp_file.bmp_header.signature>>8 );
	printf("size of the file: %d\n",bmp_file.bmp_header.file_size);
	printf("reserved1: %d\n",bmp_file.bmp_header.reserved1);
	printf("reserved2: %d\n",bmp_file.bmp_header.reserved2);
	printf("offset to pixel_array: %d\n",bmp_file.bmp_header.offset_pixel_array);
	
	read_dib_header(&bmp_file);
	printf("\ndib info:\n");
	printf("size of dib_header %d\n",bmp_file.dib_header.header_size);
	printf("image width %d\n",bmp_file.dib_header.img_width);
	printf("image height %d\n",bmp_file.dib_header.img_height);
	printf("color plane %d\n",bmp_file.dib_header.color_plane);
	printf("bits per pixel %d\n",bmp_file.dib_header.bits_per_pixel);
	printf("compression %d\n",bmp_file.dib_header.compression);
	printf("image raw size %d\n",bmp_file.dib_header.img_raw_size);
	printf("v pixels/mtr %f\n",bmp_file.dib_header.v_pixel_per_mtr);
	printf("h pixels/mtr %f\n",bmp_file.dib_header.h_pixel_per_mtr);
	printf("colors %d\n",bmp_file.dib_header.colors);

	int img_width=bmp_file.dib_header.img_width;
	
	if(img_width%4)
	{
	img_width=(8*img_width+31)/8;
    }
	int img_height=bmp_file.dib_header.img_height;
	bmp_file.stream=fopen(bmp_file.path,"r");
	fseek(bmp_file.stream,bmp_file.bmp_header.offset_pixel_array,SEEK_SET);
	
	unsigned char img_data[img_width*img_height],img_data_cp[img_width*img_height];

	fread(img_data,img_width*img_height,1,bmp_file.stream);
	
	fclose(bmp_file.stream);
	// #if
         int index=0, x=img_height, y=0;
         while(index<img_width*img_height)
    {
	if(y==img_width)
	{
			 y=0;
			 x--;
	}
	img_data_cp[x*img_width+(y++)]=img_data[index++];
}
// #endif

	SDL_Window *window=SDL_CreateWindow("DARKview",
										SDL_WINDOWPOS_UNDEFINED, 
										SDL_WINDOWPOS_UNDEFINED,
										img_width,img_height,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
									
	SDL_Surface *screen=SDL_GetWindowSurface(window);
	SDL_Surface *image=SDL_CreateRGBSurfaceFrom(img_data_cp,img_width,img_height,8,1*img_width,0,0,0,0);
	// for(int i=0;i<img_width*img_height;i++){
	// 	//printf("%d %d\n",img_data[i],((unsigned char*)image->pixels)[i]);
	// 	if(img_data[i]!=((unsigned char*)image->pixels)[i])
	// 		printf("\ndata corruption");
	// }



	bmp_file.stream=fopen(bmp_file.path,"r");
	fseek(bmp_file.stream,14+40,SEEK_SET);
	SDL_Color *colors=image->format->palette->colors;

	for(int i=0;i<256;i++)
	{
		fread(&(colors[i].b),1,1,bmp_file.stream);
		fread(&(colors[i].g),1,1,bmp_file.stream);
		fread(&(colors[i].r),1,1,bmp_file.stream);
		fread(&(colors[i].a),1,1,bmp_file.stream);


	}
	SDL_BlitSurface(image,NULL,screen,NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(5000);

	/*to open any bmp file throughg this code uncommand the below line*/
	while(getchar()!='x');
/*to open any bmp file throughg this code command the below line*/
	SDL_Quit();

}
