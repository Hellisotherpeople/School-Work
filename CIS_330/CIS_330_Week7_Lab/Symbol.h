#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol 
{
    virtual void draw() = 0;
    
    private:    
            int repeatNum;
    
    public:
            int getRepeatNum();
            void setRepeatNum(int);
    
};

#endif