//Particle.cc
#include "Particle.h"
#include <iostream>
#include <cmath>
#include <string.h> //for the name of the particle
#include "TLorentzVector.h" //for the particle 4-momentum

using std::cout;
using std::endl;
using std::string;

//CONSTRUCTORS

//defaut constructor(sets all to 0)
Particle::Particle(){
    name_ = "uninitialized_particle";
    m_ = 0.0;
    p4_.SetPxPyPzE(0.0,0.0,0.0,0.0);
}

//constructor with arguments
Particle::Particle(const string& name, double m, double px, double py, double pz){
    name_ = name;
    m_ = m;
    p4_.SetPxPyPzE(px,py,pz,sqrt(px*px+py*py+pz*pz+m*m));
}

//constructor with 3-momentum
Particle::Particle(const string& name, double m, const TVector3& p3){
    name_ = name;
    m_ = m;
    p4_.SetVect(p3); //set the 3 momentum
    p4_.SetE(sqrt(pow(p3.Mag(),2) + m*m)); //calculate the 4th component
}

//constructor with just momentum 0
Particle::Particle(const string& name, double m){
    name_ = name;
    m_ = m;
    p4_.SetPxPyPzE(0.0,0.0,0.0,m);
}

//copy constructor
Particle::Particle(const Particle& sourcePart){
    name_ = sourcePart.name_;
    m_ = sourcePart.m_;
    p4_ = sourcePart.p4_;
}


//SETTERS

//set 3-momentum of the particle
void Particle::setp3(double px, double py, double pz){
    p4_.SetPxPyPzE(px,py,pz,sqrt(px*px+py*py+pz*pz+m_*m_));
}


//OVERLOADS

// = operator
const Particle& Particle::operator=(const Particle& sourcePart){
    name_ = sourcePart.name_;
    m_ = sourcePart.m_;
    p4_ = sourcePart.p4_;
    return *this;
}


//UTILITY FUNCTIONS

//print to screen particle's information
 void Particle::print() const {
    cout << "Particle: " << name_
         << "\nMass = " << m_
         << "\nPx = " << p4_.Px()
         << "\nPy = " << p4_.Py()
         << "\nPz = " << p4_.Pz() << endl;
 }