//Emilio Taggi 1910388 2023/01/14
//Geometric.h
#ifndef Geometric_h
#define Geometric_h

#include "Dataset.h"

class Geometric : public Dataset {

    public:

    //CONSTRUCTORS:
    
    //derived copy constructor
    Geometric(const Dataset& sourceDataset);
    
    //VIRTUAL METHODS:

    //compute Geometric mean
    virtual double mean() const;
    //print info to screen
    virtual void print(const string& message = string()) const;


};

#endif