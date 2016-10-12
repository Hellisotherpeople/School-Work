#include <stdio.h>
#include "image.h"
#include "source.h"

Source::Source()
{

}


Image * Source::GetOutput()
{
	return &img;
}
