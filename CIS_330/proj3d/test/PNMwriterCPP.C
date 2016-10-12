#include "PNMwriterCPP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std; 


void PNMwriterCPP::Write(char *filename)
{
    int width = image1->GetWidth();
    int height = image1->GetHeight();
    
    ofstream myfile (filename, ios::binary);
    myfile << "P6" << endl; // write P6 and go to next line
    myfile << width << " " << height << endl;
    myfile << 255 << endl; 
    
    myfile.write((char *) image1->GetBuffer(), width * height * 3);
    myfile.close();
    
    
}
