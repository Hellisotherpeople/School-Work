#include "sink.h"
#include "source.h" 
#include <stdio.h>

#ifndef FILTERS_H
#define FILTERS_H

class filter: public source, public Sink
{
public: 
    virtual void Update(); 
    virtual const char * FilterName() = 0; 
    virtual const char * SourceName();
    virtual const char * SinkName(); 

};

class Shrinker: public filter
{
	public:
	    void Execute();
            const char * FilterName()
            { 
                return "Shrinker"; 
            };
};

class LRConcat: public filter
{
	public:
	    void Execute();
            const char * FilterName()
            { 
                return "LRConcat"; 
            };
};

class TBConcat: public filter
{
	public:
            void Execute();
            const char * FilterName()
            { 
                return "TBConcat"; 
            };
};

class Blender: public filter
{
	protected:
	    float factor;
	    
	public:
	    void SetFactor(float factor);
	    void Execute();
            const char * FilterName()
            { 
                return "Blender"; 
            };
};


#endif