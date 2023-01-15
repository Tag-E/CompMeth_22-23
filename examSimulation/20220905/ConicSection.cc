//Emilio Taggi 1910388 2023/01/15
//ConicSection.h
#include "ConicSection.h"

#include <cmath>


//CONSTRUCTORS

//Constructor by 6 double
ConicSection::ConicSection(double a,double b,double c,double d,double e,double f){
    a_ = a;
    b_ = b;
    c_ = c;
    d_ = d;
    e_ = e;
    f_ = f;
    setType_(); //set type of conic
}

//copy constructor
ConicSection::ConicSection(const ConicSection& sourceConicSection){
    a_ = sourceConicSection.a_;
    b_ = sourceConicSection.b_;
    c_ = sourceConicSection.c_;
    d_ = sourceConicSection.d_;
    e_ = sourceConicSection.e_;
    f_ = sourceConicSection.f_;
    setType_(); //set type of conic
}



//SETTERS

//set the value of a
void ConicSection::set_a(double a){
    a_ = a; //change the parameter
    setType_(); //change type
}
//set the value of c
void ConicSection::set_c(double c){
    c_ = c; //change the parameter
    setType_(); //change type
}




//PRIVATE METHODS:


double eps = pow(10,-12);
//set the type of the conic section based on the coefficients
void ConicSection::setType_(){
    if(abs(a_*c_) < eps) {      //if a=0 or c=0 we have a parabola
        conicType_ = PARABOLA;
    }
    else if(a_*c_ > 0.0) {           //if a and c have same sign we have an ellipse
        conicType_ = ELLIPSE;
    }
    else if(a_*c_ < 0.0) {      //if a and c have opposite sign we have an hyperbola
        conicType_ = HYPERBOLA;
    }
}



//OVERLOADS:

//printo to screen info <<
ostream& operator<<(ostream& os, const ConicSection& sourceConicSection){

    os << "\nConic Section Information:"
       << "\n- a = " << sourceConicSection.a()   
       << "\n- b = " << sourceConicSection.b()  
       << "\n- c = " << sourceConicSection.c()  
       << "\n- d = " << sourceConicSection.d()  
       << "\n- e = " << sourceConicSection.e()  
       << "\n- f = " << sourceConicSection.f();  
    
    //change output based on conic type
    int conicType = sourceConicSection.conicType(); 
    if(conicType==ELLIPSE){
        os << "\n- conic type: Ellipse";
    }
    else if(conicType==PARABOLA){
        os << "\n- conic type: Parabola";
    }
    else if(conicType==HYPERBOLA){
        os << "\n- conic type: Hyperbola";
    }

  return os;
}