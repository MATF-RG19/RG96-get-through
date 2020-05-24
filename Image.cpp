#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"

//Inicijalizacija i alokacija objekta koji sadrzi sliku i piksela koji ce da se sadrze u njoj
Image *image_init(int width, int height) {
  	Image *image;
  	assert(width >= 0 && height >= 0);

	image = (Image *) malloc(sizeof(Image));
	assert(image != NULL);
	image->width = width;
    image->height = height;

  	if (width == 0 || height == 0)
    	image->pixels = NULL;
  	else {
    	image->pixels = (char *)malloc(3 * width * height * sizeof(char));
    	assert(image->pixels != NULL);
  	}

  	return image;
}

//Ako smo zavrsili sa slikom oslobadjamo memoriju
void image_done(Image *image) {

  	free(image->pixels);
  	free(image);
}

/*
	Ucitavamo sliku sa prosledjene putanje, inicijalizujemo objekat dalje ali sada sa podacima iz slike.
	Slika mora imati 32 ili 24 bita po pikselu. Zatvaramo fajl odaklse smo ucitavali sliku.
*/
void image_read(Image *image, char *filename) {

  	FILE *file;
  	BITMAPFILEHEADER bfh;
  	BITMAPINFOHEADER bih;
  	unsigned int i;
  	unsigned char r, g, b, a;

  	free(image->pixels);
  	image->pixels = NULL;

  	assert((file = fopen(filename, "rb")) != NULL);

  	fread(&bfh.type, 2, 1, file);
  	fread(&bfh.size, 4, 1, file);
  	fread(&bfh.reserved1, 2, 1, file);
  	fread(&bfh.reserved2, 2, 1, file);
  	fread(&bfh.offsetbits, 4, 1, file);

  	fread(&bih.size, 4, 1, file);
  	fread(&bih.width, 4, 1, file);
  	fread(&bih.height, 4, 1, file);
  	fread(&bih.planes, 2, 1, file);
  	fread(&bih.bitcount, 2, 1, file);
  	fread(&bih.compression, 4, 1, file);
  	fread(&bih.sizeimage, 4, 1, file);
  	fread(&bih.xpelspermeter, 4, 1, file);
  	fread(&bih.ypelspermeter, 4, 1, file);
  	fread(&bih.colorsused, 4, 1, file);
	fread(&bih.colorsimportant, 4, 1, file);

  
  	image->width = bih.width;
  	image->height = bih.height;

  	if (bih.bitcount == 24)
    	image->pixels = (char *)malloc(3 * bih.width * bih.height * sizeof(char));
  	else if (bih.bitcount == 32)
    	image->pixels = (char *)malloc(4 * bih.width * bih.height * sizeof(char));
  	else {
	    fprintf(stderr, "image_read(): Nepodrzana slika\n");
	    exit(1);
  }
  assert(image->pixels != NULL);

  
  if (bih.bitcount == 24)
 
    for (i = 0; i < bih.width * bih.height; i++) {
	      
	    fread(&b, sizeof(char), 1, file);
	    fread(&g, sizeof(char), 1, file);
	    fread(&r, sizeof(char), 1, file);

	    image->pixels[3 * i] = r;
	    image->pixels[3 * i + 1] = g;
	    image->pixels[3 * i + 2] = b;
    }
  else if (bih.bitcount == 32)
   
	    for (i = 0; i < bih.width * bih.height; i++) {
		    fread(&b, sizeof(char), 1, file);
		    fread(&g, sizeof(char), 1, file);
		    fread(&r, sizeof(char), 1, file);
		    fread(&a, sizeof(char), 1, file);

		    image->pixels[4 * i] = r;
		    image->pixels[4 * i + 1] = g;
		    image->pixels[4 * i + 2] = b;
		    image->pixels[4 * i + 3] = a;
	    }

 
  fclose(file);
}