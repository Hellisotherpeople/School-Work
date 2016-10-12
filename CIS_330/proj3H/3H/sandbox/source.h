#include "image.h"

#ifndef SOURCE_H
#define SOURCE_H

class source
{
	protected:
	    Image img;
            virtual void Execute()= 0; 
	public:
            virtual const char * SourceName() = 0; 
            virtual void Update() = 0;
	    Image * GetOutput();
	    source();
            /*
            bool isUpdated = false;
            bool const GetUpdated();
            void SetUpdated(bool b);
            */ 

};

#endif