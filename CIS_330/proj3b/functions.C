#include <image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ReadImage(char *filename, Image &output){
    
    FILE *infile = fopen(filename, "rb");
    char magicNum[128];
    int  width, height, maxval;
    
    if (infile == NULL)
    {
        fprintf(stderr, "Unable to open filename %s\n", filename);
    }
    
    fscanf(infile, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    //printf("I read magic num = %s width = %d, height = %d, maxval = %d\n", magicNum, width, height, maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from filename %s, because it is not a PNM filename of type P6\n", filename);
    }
    
    output.ResetSize(width, height);
    fread(output.GetBuffer(), sizeof(unsigned char), 3 * output.GetWidth() * output.GetHeight(), infile);
        
    fclose(infile);
    
}


void WriteImage(char *filename, Image &img){
    FILE *outfile = fopen(filename, "wb");
    
    if (outfile == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", filename);
    }
    
    //fprintf(outfile, "P6\n%d %d\n%d\n", img.GetWidth(), img.GetHeight(), 255);
    fprintf (outfile, "P6\n"); // fprintf to write ASCII, 
    fprintf (outfile, "%d %d\n", img.GetWidth(), img.GetHeight());
    fprintf (outfile, "%d\n", 255);

    fwrite(img.GetBuffer(), sizeof(unsigned char), 3 * img.GetWidth() * img.GetHeight(), outfile);

    fclose(outfile);   
}


void HalveInSize(Image &input, Image &output){
    
      int i, j;    
    
    output.ResetSize(input.GetWidth()/2, input.GetHeight()/2);
    
    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {
            output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = input.GetBuffer()[3*(2*i*input.GetWidth()+2*j)+0];
            output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = input.GetBuffer()[3*(2*i*input.GetWidth()+2*j)+1];
            output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = input.GetBuffer()[3*(2*i*input.GetWidth()+2*j)+2];
        }
    }
}
    

void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output) // leftInput camel case but rightinput isn't... :( 
{
    
    int i, j, width, height;


    width = leftInput.GetWidth() + rightinput.GetWidth();

    if(leftInput.GetHeight() > rightinput.GetHeight())  // Find the max height of the two images
    {
        height = leftInput.GetWidth();
    }
    else
    {
        height = rightinput.GetHeight();
    }

    output.ResetSize(width, height);

    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {           
            if(j < leftInput.GetWidth())
            {
                output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = leftInput.GetBuffer()[3*(i*leftInput.GetWidth()+j)+0];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = leftInput.GetBuffer()[3*(i*leftInput.GetWidth()+j)+1];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = leftInput.GetBuffer()[3*(i*leftInput.GetWidth()+j)+2];
           
            }           
            else
            {
                output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = rightinput.GetBuffer()[3*(i*rightinput.GetWidth()+j - leftInput.GetWidth()) + 0];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = rightinput.GetBuffer()[3*(i*rightinput.GetWidth()+j - leftInput.GetWidth()) + 1];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = rightinput.GetBuffer()[3*(i*rightinput.GetWidth()+j - leftInput.GetWidth()) + 2];
            }
        }
    }
}
    
    


void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output)

{
    int i, j, width, height;
    
        height = topInput.GetHeight() + bottomInput.GetHeight();

        if(topInput.GetWidth() > bottomInput.GetWidth())            // Find the max width of the two images
        {
            width = topInput.GetWidth();
        }
        else
        {
            width = bottomInput.GetWidth();
        }

        output.ResetSize(width, height);

        for(i = 0; i < topInput.GetHeight(); i++)
        {
            for(j = 0; j < output.GetWidth(); j++)
            {   
                output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = topInput.GetBuffer()[3*(i*topInput.GetWidth()+j)+0];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = topInput.GetBuffer()[3*(i*topInput.GetWidth()+j)+1];
                output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = topInput.GetBuffer()[3*(i*topInput.GetWidth()+j)+2];  
            }
        }

        for(i = 0; i < bottomInput.GetHeight(); i++)
        {
            for(j = 0; j < output.GetWidth(); j++)
            {
                           
                output.GetBuffer()[3*((i+topInput.GetHeight())*output.GetWidth()+j)+0] = bottomInput.GetBuffer()[3*(i*bottomInput.GetWidth()+j)+0];
                output.GetBuffer()[3*((i+topInput.GetHeight())*output.GetWidth()+j)+1] = bottomInput.GetBuffer()[3*(i*bottomInput.GetWidth()+j)+1];
                output.GetBuffer()[3*((i+topInput.GetHeight())*output.GetWidth()+j)+2] = bottomInput.GetBuffer()[3*(i*bottomInput.GetWidth()+j)+2];
            }
        }
    }


void Blend(Image &input1, Image &input2, float factor, Image &output)

{                                                                        
    int i, j;

    if(factor < 0 || factor > 1)
    {
       fprintf(stderr, "User didn't enter a legal factor value %f\n", factor);
    }
    else
    {
        output.ResetSize(input1.GetWidth(), input1.GetHeight());

        memcpy(output.GetBuffer(), input1.GetBuffer(), 3*input1.GetWidth()*input1.GetHeight());         // Copy the image memory and create a new one

        for(i = 0; i < output.GetHeight(); i++)                                                         // For loop to set the pixel color down the diagonal 
        {
            for(j = 0; j < output.GetWidth(); j++)
            {                  
                output.GetBuffer()[3*(i*output.GetWidth()+j)+0] = (input1.GetBuffer()[3*(i*input1.GetWidth()+j)+0]*factor) + (input2.GetBuffer()[3*(i*input2.GetWidth()+j)+0]*(1-factor));
                output.GetBuffer()[3*(i*output.GetWidth()+j)+1] = (input1.GetBuffer()[3*(i*input1.GetWidth()+j)+1]*factor) + (input2.GetBuffer()[3*(i*input2.GetWidth()+j)+1]*(1-factor));
                output.GetBuffer()[3*(i*output.GetWidth()+j)+2] = (input1.GetBuffer()[3*(i*input1.GetWidth()+j)+2]*factor) + (input2.GetBuffer()[3*(i*input2.GetWidth()+j)+2]*(1-factor));
            }
        }
    }
}
