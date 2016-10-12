#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;  
} imagePixel;

typedef struct // hold width and height info  
{
    int iwidth, iheight; 
    imagePixel *imageData; 
} Image; 


Image * 
ReadImage(char *filename)
{
    FILE *infile = fopen(filename, "rb");
    Image *img = NULL; // initialize it to null when it has nothing in it 
    char magicNum[128]; 
    int width, height, maxval; 
    
    if (infile == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
    }
    
    fscanf(infile, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    //printf("I read magic num = %s width = %d, height = %d, maxval = %d\n", magicNum, width, height, maxval);
    
     if (strcmp(magicNum, "P6") != 0) // returns non-zero if they're not the same 
    {
        fprintf(stderr, "Unable to read from file %s, because it is not a PNM file of type P6\n", filename);
    }

    img = (Image *) malloc(sizeof(Image));
    img -> iwidth = width;
    img -> iheight = height;
    img -> imageData = (imagePixel*) malloc(img -> iwidth * img -> iheight * sizeof(imagePixel));

    fread(img -> imageData, sizeof(imagePixel), width*height, infile);

    fclose(infile);
    return img;
    
}

Image *
YellowDiagonal(Image *input)
{
    Image *imgcopy = NULL;
    imgcopy = (Image *) malloc(sizeof(Image));
    imgcopy = input; 
    int i, j;

    for (i = 0; i < imgcopy->iwidth; i++)
    {
        for (j=0; j < imgcopy->iheight; j++)
        {
            if (i==j)
            {
                int index = j * input -> iwidth + i;
                imgcopy->imageData[index].red=255;
                imgcopy->imageData[index].green=255;
                imgcopy->imageData[index].blue=0;
            }
        }
    }

    return imgcopy;   
}


void WriteImage(Image *img, char *filename)
{
    FILE *outfile = fopen(filename, "wb");

    if (outfile == NULL)
    {
        fprintf (stderr, "Unable to open %s\n", filename);
    }

    fprintf (outfile, "P6\n"); // fprintf to write ASCII, 
    fprintf (outfile, "%d %d\n", img->iwidth, img->iheight);
    fprintf (outfile, "%d\n", 255); // hardcoded max value (Should I read this?) 

    fwrite(img->imageData, sizeof(imagePixel), img->iwidth * img->iheight, outfile); // fwrite to write binary data 
    fclose(outfile);
}


int main(int argc, char *argv[])
{
   
   if (argc != 3)
    {
        fprintf(stderr, "Commands should look like this:  ./3A_c.c <input image file> <output image file>\n");
        exit(EXIT_FAILURE);
    }

        Image *img;

        img = ReadImage(argv[1]);
        fprintf(stderr, "Read executed!\n");
        Image *img2 = YellowDiagonal(img); // create another image to be edited. 
        fprintf(stderr, "Drawing Diaganol Line!\n");
        WriteImage(img2, argv[2]);
        fprintf(stderr, "Write executed!\n");
        // Free the previously malloced memory
        //free(imgcopy);  // was getting weird errors when I tried to free this or img2 
        free(img->imageData); 
        free(img); 
        
}
