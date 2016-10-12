#include "sink.h"
#include "source.h" 
#include <stdio.h>

#ifndef FILTERS_H
#define FILTERS_H

class Filters: public Source, public Sink
{
public:
    virtual void Execute(){};

};

class Shrinker: public Filters
{
	public:
	    void Execute();
};

class LRConcat: public Filters
{
	public:
	    void Execute();
};

class TBConcat: public Filters
{
	public:
		void Execute();
};

class Blender: public Filters
{
	protected:
	    float factor;
	    
	public:
	    void SetFactor(float factor);
	    void Execute();
};


#endif