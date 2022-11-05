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

    //Setters

    //set name of the particle
    void setname(const string& name) {name_ = name;} 
    //set value of m
    void setm(double m) {m_ = m;}
    //set value of p4                        
    //void setp4(TLorentzVector p4) {p4_ = p4;}            
    /*Setter for 4-momentum no implemented, it cannot be arbitrary
      since the mass is a class member*/
    //set 3-momentum of the particle
    void setp3(double px, double py, double pz);          


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