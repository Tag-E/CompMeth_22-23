//Emilio Taggi 1910388 2023/01/15
//CanonicalParabola.cc
#include "CanonicalParabola.h"
#include "ConicSection.h"

#include <iostream>
using namespace std;


//CONSTRUCTORS:

//I construct the Parabola accordingly to the relation alpha,beta - a,b
CanonicalParabola::CanonicalParabola(double alpha, double beta, double gamma) : ConicSection(alpha,0.0,0.0,beta,-1.0,gamma){}
