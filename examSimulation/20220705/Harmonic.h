//Emilio Taggi 1910388 2023/01/14
//Harmonic.h
#ifndef Harmonic_h
#define Harmonic_h

#include "Dataset.h"

class Harmonic : public Dataset {

    public:

    //CONSTRUCTORS:
    
    //derived copy constructor
    Harmonic(const Dataset& sourceDataset);
    
    //VIRTUAL METHODS:

    //compute Harmonic mean
    virtual double mean() const;
    //print info to screen
    virtual void print(const string& message = string()) const;


};

#endif