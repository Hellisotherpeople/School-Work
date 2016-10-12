#include <stdio.h>
#include "sink.h"

#ifndef PNMwriterCPP_H
#define PNMwriterCPP_H

class PNMwriterCPP: public Sink
{
	public:
	    void Write(char *filename);
};

#endif