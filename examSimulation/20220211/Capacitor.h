//Emilio Taggi 1910388
//Capacitor.h

/*The class allow to have capacitor of capacitance C
  The only parameter fixed is the capacitance, a given
  parameter can be obtained once you specify all the others */

#ifndef Capacitor_h
#define Capacitor_h

#include <cmath>


const double EPS0 = 8.854*pow(10,-12); //void permittivity in F/m

//classe che implementa un pianeta con le sue caratteristiche
class Capacitor {
    public:


    //Constructors:

    //default constructor with default initialization
    Capacitor(); 
    //Constructor by arguments
    Capacitor(double C);
    //copy constructor
    Capacitor(const Capacitor& sourceCapacitor); 


    //Getters:

    //return the capacitance of the Capacitor
    double C() const {return C_; }
    

    //Setters:

    //set value of C
    void set_C(double C) {C_ = C;} 


    //Physics functions

    //get value of relative permittivity given area of plates (m**2) and separation (m)
    double get_A(double eps_r,double s) const {return C_ * s / (EPS0*eps_r);}
    //get value of separation (m) given relative permittivity and area of plates (m**2) 
    double get_s(double eps_r,double A) const {return EPS0*eps_r*A / C_;}
    //get value of separation (m) given relative permittivity and area of plates (m**2) 
    double get_eps_r(double A,double s) const {return C_ * s / (EPS0 * A);}


    //utility functions:

    //flash info to screen
    void print() const; 


    //overloads

    //overload of sum -> series of capacitor
    Capacitor operator+( const Capacitor& capacitor2 ) const;  
    //overload of or -> parallel of capacitor
    Capacitor operator||( const Capacitor& capacitor2 ) const;  


    private:
    double C_; //Capacitance of the capacitor 

};

#endif