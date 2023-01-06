//Particle.h
#ifndef Particle_h
#define Particle_h

#include <string.h> //for the name of the particle
#include "TLorentzVector.h" //for the particle 4-momentum
#include "TVector3.h" //for the particle 3-momentum

using std::string;

//classe che implementa un particella
class Particle{
    public:

    //CONSTRUCTORS

    //default constructor
    Particle(); 
    //constructor of the particle
    Particle(const string& name, double m, double px, double py, double pz); 
    //constructor of the particle with 3-momentum
    Particle(const string& name, double m, const TVector3& p); 
    //constructor of the particle with momentum 0.0
    Particle(const string& name, double m); 
    //copy constructor
    Particle(const Particle& sourcePart); 


    //GETTERS

    //return name of the particle
    std::string name() const {return name_; }
    //return mass of the particle 
    double m() const {return m_; }
    //return 4-momentum of the particle            
    TLorentzVector p4() const {return p4_; }   

    //SETTERS

    //set name of the particle
    void setname(const string& name) {name_ = name;} 
    //set value of m
    void setm(double m);
    //set 3-momentum of the particle
    void setp3(double px, double py, double pz);

    /*m and p3 setters correctly recompute the energy of the particle
      after setting the variable to the given value
      A p4 setter is not implemented since the component of the 
      4-momentum cannot be arbitrary once the mass of the 
      particle is fixed*/       


    //OVERLOADS

    //assignation of Particle
    const Particle& operator=(const Particle& sourcePart); 


    //UTILITY FUNCTIONS

    //print info about the particle
    void print() const; 

    private:
    string name_; //name of the particle
    double m_; //mass of the particle
    TLorentzVector p4_; //4-momentum of the particle
};

#endif