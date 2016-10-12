#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filters.h"
#include "sink.h" 
#include "source.h" 
#include "logging.h" 


void filter::Update()
{	
	
	if(image1 != NULL)
	{
        char msg[128];
        sprintf(msg, "%s: about to update image1\n", SourceName());
        Logger::LogEvent(msg);
        
        image1->Update();
        
        sprintf(msg, "%s: done updating image1\n", SourceName());
        Logger::LogEvent(msg);
	}

	if(image2 != NULL)
	{

        char msg[128];
        sprintf(msg, "%s: about to update image2\n", SourceName());
        Logger::LogEvent(msg);
        
        image2->Update();
        
        sprintf(msg, "%s: done updating image2\n", SourceName());
        Logger::LogEvent(msg);
	}
	
    char msg[1024];
    sprintf(msg, "%s: about to execute\n", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing\n", SourceName());
    Logger::LogEvent(msg);
	
}

const char * filter::SourceName()
{ 
    return FilterName(); 
}

const char * filter::SinkName()
{
    return FilterName(); 
    
}

void Shrinker::Execute()
{
    int i, j;                                                       
    img.ResetSize(image1->GetWidth()/2, image1->GetHeight()/2);
    
    for(i = 0; i < img.GetHeight(); i++)
    {
        for(j = 0; j < img.GetWidth(); j++)
        {
            img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+0];
            img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+1];
            img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(2*i*image1->GetWidth()+2*j)+2];
        }
    }
}


void LRConcat::Execute()
{
    
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
             throw e;
    }
    
    if (image1->GetHeight() != image2->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d\n", SinkName(), image1->GetHeight(),
                image2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int i, j, width, height;

    width = image1->GetWidth() + image2->GetWidth();

    if(image1->GetHeight() > image2->GetHeight())                   // Find the max height of the two images 
    {
        height = image1->GetWidth();
    }
    else
    {
        height = image2->GetHeight();
    }

    img.ResetSize(width, height);

    for(i = 0; i < img.GetHeight(); i++)
    {
        for(j = 0; j < img.GetWidth(); j++)
        {           
            if(j < image1->GetWidth())
            {
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2];
           
            }           
            else
            {
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image2->GetBuffer()[3*(i*image2->GetWidth()+j - image1->GetWidth()) + 0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image2->GetBuffer()[3*(i*image2->GetWidth()+j - image1->GetWidth()) + 1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image2->GetBuffer()[3*(i*image2->GetWidth()+j - image1->GetWidth()) + 2];
            }
        }
    }
}


void TBConcat::Execute()
{
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if (image1->GetWidth() != image2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(), image1->GetWidth(),
                    image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int i, j, width, height;

  

        height = image1->GetHeight() + image2->GetHeight();

        if(image1->GetWidth() > image2->GetWidth())            // Find the max width of the two images
        {
            width = image1->GetWidth();
        }
        else
        {
            width = image2->GetWidth();
        }

        img.ResetSize(width, height);

        for(i = 0; i < image1->GetHeight(); i++)
        {
            for(j = 0; j < img.GetWidth(); j++)
            {   
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1];
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2];  
            }
        }

        for(i = 0; i < image2->GetHeight(); i++)
        {
            for(j = 0; j < img.GetWidth(); j++)
            {
                           
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+0] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0];
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+1] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1];
                img.GetBuffer()[3*((i+image1->GetHeight())*img.GetWidth()+j)+2] = image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2];
            }
        }
    }


void Blender::SetFactor(float factor)
{
    this->factor = factor;
}

void Blender::Execute()
{
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(image2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image2!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
    if (factor < 0 || factor > 1)
    {
        char msg[1024];
        sprintf(msg, "%s: factor is invalid: %f\n", SinkName(), factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    
    
    
    
    
    unsigned char *pixel;                                                                           
    int i, j;



        img.ResetSize(image1->GetWidth(), image1->GetHeight());

        memcpy(img.GetBuffer(), image1->GetBuffer(), 3*image1->GetWidth()*image1->GetHeight());         // Copy the image memory and create a new one

        for(i = 0; i < img.GetHeight(); i++)                                                         // For loop to set the pixel color down the diagonal 
        {
            for(j = 0; j < img.GetWidth(); j++)
            {                  
                img.GetBuffer()[3*(i*img.GetWidth()+j)+0] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+0]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+0]*(1-factor));
                img.GetBuffer()[3*(i*img.GetWidth()+j)+1] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+1]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+1]*(1-factor));
                img.GetBuffer()[3*(i*img.GetWidth()+j)+2] = (image1->GetBuffer()[3*(i*image1->GetWidth()+j)+2]*factor) + (image2->GetBuffer()[3*(i*image2->GetWidth()+j)+2]*(1-factor));
            }
        }
    }
}


