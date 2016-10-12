#include <stdio.h>
#include "source.h"
#include <iostream>
#include <fstream>
#include <string> 

#ifndef PNMreaderCPP_H
#define PNMreaderCPP_H

class PNMreaderCPP: public Source
{
	    
	public:
            char *filename;
	    virtual void Execute();
	    PNMreaderCPP(const char *filename);
            virtual ~PNMreaderCPP(); // destructor
};

#endif