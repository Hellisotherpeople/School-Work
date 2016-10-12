#include "PNMreader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PNMreader::PNMreader(const char *f)
{
	filename = new char[strlen(f)+1];
	strcpy(filename, f);
}

PNMreader::~PNMreader()
{
	delete [] filename;
}

void PNMreader::Update()
{
    Execute();
}

void PNMreader::Execute()
{
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
    
}

