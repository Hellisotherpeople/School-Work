#ifndef IMAGE_H
#define IMAGE_H

class source; 
class Image
{
    private:
        int  iwidth, iheight;                                         /* Initialize width, height, and maxvalue */
        unsigned char *buffer;                                          /* Initialize the 1D array as buffer */
        source *source_; 

    public:
        Image();                                                    //Default constructor
        Image(Image &img);                                          //Copy constructor
        Image(int w, int h);                                         //Parametertized  constructor


        int GetWidth() const;  // Initialize getter methods 
        int GetHeight() const;
        unsigned char *GetBuffer() const;
        void ResetSize(int w, int h);
        void Update() const; 
        void setSource(source *s); 
};

#endif