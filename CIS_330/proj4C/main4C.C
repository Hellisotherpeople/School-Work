#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>

int main(int argc, char *argv[])
{
    /*
    PNMreader reader(argv[1]);
    */ 
    
    Color blue(2000, 2000, 0, 0, 255);
    Color red(2000, 2000, 255, 0, 0);
    
    Blender blender; 
    blender.SetFactor(0.5); // didn't tell us what factor to use on prompt so I assumed 0.5  
    blender.SetInput(blue.GetOutput());
    blender.SetInput2(red.GetOutput());
    blender.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(blender.GetOutput());
    writer.Write(argv[1]);
 
}
