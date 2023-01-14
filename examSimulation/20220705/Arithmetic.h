//Emilio Taggi 1910388 2023/01/14
//Arithmetic.h
#ifndef Arithmetic_h
#define Arithmetic_h

#include "Dataset.h"

class Arithmetic : public Dataset {

    public:

    //CONSTRUCTORS:
    
    //derived copy constructor
    Arithmetic(const Dataset& sourceDataset);
    
    //VIRTUAL METHODS:

    //compute arithmetic mean
    virtual double mean() const;
    //print info to screen
    virtual void print(const string& message = string()) const;


};

#endif