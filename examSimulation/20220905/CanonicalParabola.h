//Emilio Taggi 1910388 2023/01/15
//CanonicalParabola.h
#ifndef CanonicalParabola_h
#define CanonicalParabola_h

#include "ConicSection.h"

class CanonicalParabola : public ConicSection {

    public:

    //CONSTRUCTORS:
    
    //constructor by 3 parameters
    CanonicalParabola(double alpha, double beta, double gamma);


    //OTHER:

    //method that return first derivatives at a given x
    double first_derivative(double x) const {return 2*a()*x+d();} //the conversion from alpha,beta gamma is written here
    //method that return second derivatives at a given x
    double second_derivative(double x) const {return 2*a();}
    


};

#endif