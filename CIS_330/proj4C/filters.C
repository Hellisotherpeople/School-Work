#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "filters.h"
#include "sink.h" 
#include "source.h" 
#include "logging.h" 


void filter::Update()
{	
    struct timeval startTime; 
    gettimeofday(&startTime, 0); 
	
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
    
    struct timeval endTime; 
    gettimeofday(&endTime, 0); 
    double seconds = double(endTime.tv_sec - startTime.tv_sec) + double(endTime.tv_usec - startTime.tv_usec) / 1000000.;
    sprintf(msg, "%s: Took : %f seconds to update\n", SourceName(), seconds);
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

void Crop::Execute(void)
{
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image1 passed in!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= image1->GetWidth() || Istop >= image1->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= image1->GetHeight() || Jstop >= image1->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    
    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = image1->GetWidth();
    img.ResetSize(width, height);
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int index_ori = j*inputWidth+i;
            int index = (j-Jstart)*width+(i-Istart);
            img.GetBuffer()[3*index]   = image1->GetBuffer()[3*index_ori];
            img.GetBuffer()[3*index+1] = image1->GetBuffer()[3*index_ori+1];
            img.GetBuffer()[3*index+2] = image1->GetBuffer()[3*index_ori+2];
        }
    }
}

void Invert::Execute(void) // defensive coding 
{
    if(image1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no image1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else
    {
    img.ResetSize(image1->GetWidth(), image1->GetHeight());
    for(int i = 0; i < img.GetHeight(); i++)
    {
        for(int j = 0; j < img.GetWidth(); j++)
        {
            int index_ori = 3*(i*image1->GetWidth()+j);
            int index = 3*(i*img.GetWidth()+j);
            img.GetBuffer()[index] = 255 - image1->GetBuffer()[index_ori];
            img.GetBuffer()[index+1] = 255 - image1->GetBuffer()[index_ori+1];
            img.GetBuffer()[index+2] = 255 - image1->GetBuffer()[index_ori+2];
            }
        }
    }
}
    
void Transpose::Execute(void)
{
    
    if(image1 == NULL) // defensive coding 
    {
        char msg[1024];
        sprintf(msg, "%s: no image1!\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

        int newheight = image1->GetWidth();
        int newwidth = image1->GetHeight();
        int inputWidth = image1->GetWidth();
        img.ResetSize(newwidth, newheight);
        for(int i = 0; i < newheight; i++)
        {
            for(int j = 0; j < newwidth; j++)
            {
                int index_ori = 3*(j*inputWidth+i);
                int index = 3*(i*newwidth+j);
                img.GetBuffer()[index] = image1->GetBuffer()[index_ori];
                img.GetBuffer()[index+1] = image1->GetBuffer()[index_ori+1];
                img.GetBuffer()[index+2] = image1->GetBuffer()[index_ori+2];
            }
        }
    }

void Checkerboard::Execute(void)
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
    
    if (image1->GetWidth() != image2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d\n", SinkName(), image1->GetWidth(),
                image2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    
    img.ResetSize(image1->GetWidth(), image1->GetHeight()); // image1 and image2 should be the same size so it wouldn't matter which I picked
    
    for(int i = 0; i < img.GetHeight(); i++)
    {
        for(int j = 0; j < img.GetWidth(); j++)
        {
            if((i/10 + j/10) % 2 == 0)
            {
                int index = 3*(i*img.GetWidth()+j);
                img.GetBuffer()[index] = image1->GetBuffer()[index];
                img.GetBuffer()[index+1] = image1->GetBuffer()[index+1];
                img.GetBuffer()[index+2] = image1->GetBuffer()[index+2];
            }
            else
            {
                int index = 3*(i*img.GetWidth()+j); 
                img.GetBuffer()[index] = image2->GetBuffer()[index];
                img.GetBuffer()[index+1] = image2->GetBuffer()[index+1];
                img.GetBuffer()[index+2] = image2->GetBuffer()[index+2];
            }
        }
    }
}

    
void Color::Execute(void)
{
    img.ResetSize(width, height);
    
    for(int i = 0; i < img.GetWidth(); i++)
    {
        for(int j = 0; j < img.GetHeight(); j++)
        {
            int index = 3*(j*img.GetWidth()+i);
            img.GetBuffer()[index] = red;
            img.GetBuffer()[index+1] = green;
            img.GetBuffer()[index+2] = blue;
        }
    }
}

void Color::Update()
{
    Execute();
}

void CheckSum::OutputCheckSum(const char *filename)
{
    
    if(image1 == NULL) // some defensive coding 
    {
        char msg[1024];
        sprintf(msg, "%s: no input\n", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    unsigned char redSum = 0; // auto modulos by %256 
    unsigned char greenSum = 0;
    unsigned char blueSum = 0;
    FILE *f = fopen(filename, "w");
    
    for(int j = 0; j < image1->GetWidth(); j++)
    {
        for(int i = 0; i < image1->GetHeight(); i++)
        {
            int index = 3*(i*image1->GetWidth()+j);
            redSum += image1->GetBuffer()[index];
            greenSum += image1->GetBuffer()[index+1];
            blueSum += image1->GetBuffer()[index+2];
        }
    }
    fprintf(f, "CHECKSUM: %d, %d, %d\n", redSum, greenSum, blueSum);
    fclose(f);
}
  
