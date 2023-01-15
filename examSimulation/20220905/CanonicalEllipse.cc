//Emilio Taggi 1910388 2023/01/15
//CanonicalEllipse.cc
#include "CanonicalEllipse.h"
#include "ConicSection.h"

#include <iostream>
using namespace std;


//CONSTRUCTORS:

//I construct the ellipse accordingly to the relation alpha,beta - a,b
CanonicalEllipse::CanonicalEllipse(double alpha, double beta) : ConicSection(1.0/(alpha*alpha),0.0,1.0/(beta*beta),0.0,0.0,-1.0){}
