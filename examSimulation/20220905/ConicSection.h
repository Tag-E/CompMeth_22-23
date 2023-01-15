//Emilio Taggi 1910388 2023/01/15
//ConicSection.h
#ifndef ConicSection_h
#define ConicSection_h

#include <iostream>
using namespace std;

//to address the type of conic
#define ELLIPSE 0
#define PARABOLA 1
#define HYPERBOLA 2

class ConicSection{

    public:

    //CONSTRUCTORS:

    //Constructor by 6 double
    ConicSection(double a,double b,double c,double d,double e,double f);
    //copy constructor
    ConicSection(const ConicSection& sourceConicSection);


    //GETTERS

    //return the coefficient a
    double a() const {return a_;}
    //return the coefficient b
    double b() const {return b_;}
    //return the coefficient c
    double c() const {return c_;}
    //return the coefficient d
    double d() const {return d_;}
    //return the coefficient e
    double e() const {return e_;}
    //return the coefficient f
    double f() const {return f_;}
    //return the ConicType
    int conicType() const {return conicType_;}


    //SETTERS

    //set the value of a
    void set_a(double a);
    //set the value of b
    void set_b(double b) {b_=b;}
    //set the value of c
    void set_c(double c);
    //set the value of d
    void set_d(double d) {d_=d;}
    //set the value of e
    void set_e(double e) {e_=e;}
    //set the value of f
    void set_f(double f) {f_=f;}


    //OTHER:

    //Compute the discriminant = b**2 - 4ac
    double discr() const {return b_*b_ -4*a_*c_;}
    

    private:
    double a_,b_,c_,d_,e_,f_; //coefficients of the quadratic equation
    int conicType_; //0 if ellipse, 1 if parabola, 2 if hyperbola

    void setType_(); //set the type of conic section based on the coefficients 

};

//OVERLOADS:

//printo to screen info <<
ostream& operator<<(ostream& os, const ConicSection& sourceConicSection);

#endif