#include <stdio.h>
#include "image.h"
#include "source.h"
#include "logging.h"

source::source()
{
    img.setSource(this); 

}
/*
const bool source::GetUpdated()
{
    return isUpdated;
}

void source::SetUpdated(bool b){
    b = true; 
}
*/ 

Image * source::GetOutput()
{
	return &img;
}
