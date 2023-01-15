//Emilio Taggi 1910388 2023/01/15
//app.cpp
#include "ConicSection.h"
#include "CanonicalEllipse.h"
#include "CanonicalHyperbola.h"
#include "CanonicalParabola.h"

#include <iostream>
using namespace std;

int main(){

    //ConicSection Demonstration

    //constructor by 6 doubles
    ConicSection con1 = ConicSection(1.0,2.0,3.0,4.0,5.0,6.0);
    //print info
    std::cout << "con1:" << con1 << std::endl;

    //copy constructor
    ConicSection con2 = ConicSection(con1);
    std::cout << "con2:" << con2 << std::endl;


    //setters and getters
    con2.set_a(-con2.a());
    std::cout << "con2 modified:" << con2 << std::endl;

    //discriminant
    std::cout << "con2 modified discriminant = " << con2.discr() << std::endl;

    //CanonicalEllipse
    CanonicalEllipse ell1 = CanonicalEllipse(2.0,3.0);
    std::cout << "ell1:" << ell1 << std::endl;

    //CanonicalHyperbola
    CanonicalHyperbola hyp1 = CanonicalHyperbola(2.0,3.0);
    std::cout << "hyp1:" << hyp1 << std::endl;

    //CanonicalParabola
    CanonicalParabola par1 = CanonicalParabola(2.0,3.0,1.0);
    std::cout << "par1:" << par1 << std::endl;

    //first and second derivatives for canonical parabola
    std::cout << "par1 first derivative at x=10:  " << par1.first_derivative(10.0) << std::endl;
    std::cout << "par1 second derivative at x=10:  " << par1.second_derivative(10.0) << std::endl;


    return 0;
}