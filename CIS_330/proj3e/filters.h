#include "sink.h"
#include "source.h" 
#include <stdio.h>

#ifndef FILTERS_H
#define FILTERS_H

class filter: public source, public Sink
{
    virtual void Update(); 

};

class Shrinker: public filter
{
	public:
	    void Execute();
};

class LRConcat: public filter
{
	public:
	    void Execute();
};

class TBConcat: public filter
{
	public:
		void Execute();
};

class Blender: public filter
{
	protected:
	    float factor;
	    
	public:
	    void SetFactor(float factor);
	    void Execute();
};


#endif