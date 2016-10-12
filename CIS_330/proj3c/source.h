#include "image.h"

#ifndef SOURCE_H
#define SOURCE_H

class Source
{
	protected:
	    Image img;

	public:
	    Image * GetOutput();
	    Source();
            virtual void Execute() = 0;

};

#endif