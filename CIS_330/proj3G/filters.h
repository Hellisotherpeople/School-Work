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

class Crop : public filter
{
public:
    Crop()  { Istart = Istop = Jstart = Jstop = -1; };
    virtual const char *FilterName()
    {
        return "Crop";
    };
    virtual void Execute();
    void SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
    {
        Istart = Istart_;
        Istop  = Istop_;
        Jstart = Jstart_;
        Jstop  = Jstop_;
    }
    
private:
    int Istart, Istop, Jstart, Jstop;
};


class Invert : public filter
{
    public:
        const char *FilterName()
        { 
            return "Invert";
        };
        void Execute();
    
};

class Transpose : public filter
{
    public:
        const char *FilterName()
        {
            return "Transpose";
        };
        void Execute();
};

class Checkerboard : public filter
{
public:
    const char *FilterName(){
        return "Checkerboard";
    };
    void Execute();
};

class Color : public source
{
    public:
        const char *SourceName() { return "Color"; };
        void Execute();
        virtual void Update();
        Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
        {
        width = w;
        height = h;
        red = r;
        green = g;
        blue = b;
        }
protected:
    int width, height;
    unsigned char red, green, blue;
};

class CheckSum : public Sink
{
public:
    const char *SinkName()
    {
        return "CheckSum";
    };
    void OutputCheckSum(const char *filename);
};


#endif