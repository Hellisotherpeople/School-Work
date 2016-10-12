#include <image.h>

void ReadImage(char *filename, Image &output){
    
    FILE *infile = fopen(this->filename, "rb");
    char magicNum[128];
    int  width, height, maxval;
    
    if (f == NULL)
    {
        fprintf(stderr, "Unable to open filename %s\n", this->filename);
    }
    
    fscanf(infile, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from filename %s, because it is not a PNM filename of type P6\n", this->filename);
    }
    
    output.ResetSize(width, height);
    fread(output.GetBuffer(), sizeof(unsigned char), 3 * output.GetWidth() * output.GetHeight(), infile);
        
    fclose(infile);
    
}

void WriteImage(char *filename, Image &img);

void HalveInSize(Image &input, Image &output);
void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output);
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output);
void Blend(Image &input1, Image &input2, float factor, Image &output);
