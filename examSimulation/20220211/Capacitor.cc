//Emilio Taggi 1910388
//Capacitor.cc

#include "Capacitor.h"
#include <iostream>
#include <cmath>

using namespace std;


//Constructors:

//constructor with default initialization
Capacitor::Capacitor(){
    C_ = 1.0 * pow(10,-12); 
}

//constructor by arguments
Capacitor::Capacitor(double C){
    C_=C;
}

//copy constructor
Capacitor::Capacitor(const Capacitor& sourceCapacitor){
    C_=sourceCapacitor.C_;
}



//Utility functions:

//printo to flash info to screen
void Capacitor::print() const{
    std::cout << "Capacitor's info:"
              << "\n - Capacitance [F/m]: " << C_ << std::endl;

}


//Overload

//overload of + --> capacitor series
Capacitor Capacitor::operator+( const Capacitor& capacitor2 ) const{
    return C_ + capacitor2.C();
}

//overload of || --> capacitor parallel
Capacitor Capacitor::operator||( const Capacitor& capacitor2 ) const{
    return 1.0 / ( 1.0/C_ + 1.0/capacitor2.C() );
}
