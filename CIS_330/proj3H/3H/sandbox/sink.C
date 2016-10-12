#include "sink.h"
#include <stdio.h>
#include "logging.h" 

Sink::Sink()
{
	image1 = NULL; // should be initialied to null
	image2 = NULL;
};

void Sink::SetInput(const Image *image1)
{
    this->image1 = image1;
}

void Sink::SetInput2(const Image *image2)
{
    this->image2 = image2;
}