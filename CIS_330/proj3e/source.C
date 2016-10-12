#include <stdio.h>
#include "image.h"
#include "source.h"

source::source()
{
    img.setSource(this); 

}


Image * source::GetOutput()
{
	return &img;
}
