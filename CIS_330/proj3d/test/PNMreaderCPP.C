#include "PNMreaderCPP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std; //lets me omit std before everything 

PNMreaderCPP::PNMreaderCPP(const char *f)
{
	filename = new char[strlen(f)+1];
	strcpy(filename, f);
}

PNMreaderCPP::~PNMreaderCPP()
{
	delete [] filename;
}

void PNMreaderCPP::Execute()
{
    ifstream myfile (this->filename, ios::in);
    if (!myfile.is_open())
    {
        fprintf(stderr, "File didn't open!"); 
    }
    char magicNum[128];
    int  width, height, maxval;
    
    myfile >> magicNum >> width >> height >> maxval; // read the values from the file  
    img.ResetSize(width, height); // set the images width and height to be what was read 

        if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from filename %s, because it is not a PNM filename of type P6\n", this->filename);
    }
    
/*
    printf("I read magic num = %s width = %d, height = %d, maxval = %d\n", magicNum, width, height, maxval);
  */  
    
    unsigned char* copy = new unsigned char[3 * width * height+1]; 
    
    myfile.read((char *) copy, width*height*3); 
    img.setData((unsigned char *) copy +1); 
    myfile.close();
    delete(copy);
    

    
    myfile.close(); 
    
    
    /*
    FILE *f = fopen(this->filename, "rb");
    char magicNum[128];
    int  width, height, maxval;
    
    if (f == NULL)
    {
        fprintf(stderr, "Unable to open filename %s\n", this->filename);
    }
    
    fscanf(f, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr, "Unable to read from filename %s, because it is not a PNM filename of type P6\n", this->filename);
    }
    
    img.ResetSize(width, height);
    fread(img.GetBuffer(), sizeof(unsigned char), 3 * img.GetWidth() * img.GetHeight(), f);
        
    fclose(f);
    */ 
}

