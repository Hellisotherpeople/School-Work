
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "source.h"

Image::Image() // standerd constructor 
{
    int iwidth = 0;
    int iheight = 0;
    unsigned char *buffer = NULL;
}

Image::Image(Image &img) //copy constructor 
{
    iwidth = img.iwidth;
    iheight = img.iheight;
    buffer = new unsigned char[3 * iwidth * iheight]; // changing ImagePixel to a buffer 
    memcpy(buffer, img.buffer, 3 * iwidth * iheight * sizeof(unsigned char)); // easy way to make deep copy 
}

Image::Image(int w, int h) // parametrized constuctor 
{
    iwidth = w;
    iheight = h;
    buffer = new unsigned char[3 * iwidth * iheight];
}


void Image::ResetSize(int w, int h) // allows me to change width and height values on the fly 
{
    iwidth = w;
    iheight = h;
    buffer = new unsigned char[3 * iwidth * iheight];
}

int Image::GetWidth()const // constant at end to prevent these methods from changing class members 
{
    return iwidth;
}

int Image::GetHeight()const
{
    return iheight;
}

unsigned char * Image::GetBuffer()const
{
    return buffer;
}

void Image::setSource(source *s)
{
    source_ = s;
}

void Image::Update() const
{ 
    if(source_ != NULL)
    {
        source_->Update();
    }
}