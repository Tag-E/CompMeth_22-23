//Emilio Taggi 1910388 2023/01/16
//Particle.h
#ifndef Particle_h
#define Particle_h

#include <iostream>
using namespace std;

#include <string> //for the message in print
using std::string;

#include "TVector3.h" //for the particle's position and velocity


class Particle{

    public:

    //CONSTRUCTORS:

    //Default Constructor
    Particle();
    //Constructor by argument
    Particle(double m,const TVector3& x,const TVector3& v);
    //copy constructor
    Particle(const Particle& sourceParticle);


    //GETTERS

    //return the mass of the particle
    double m() const {return m_;}
    //return the position of the particle
    TVector3 x() const {return x_;};
    //return the velocity of the particle
    TVector3 v() const {return v_;};


    //SETTERS
    
    //set the value of the mass of the particle
    void set_m(double m) {m_=m;}
    //set the position of the particle
    void set_x(const TVector3& x) {x_=x;}
    //set the value of the particle
    void set_v(const TVector3& v) {v_=v;}

    //UTILITY METHODS:

    //print info to screen
    void print(const string& message = string()) const;
    

    private:
    double m_; //mass of the particle
    TVector3 x_,v_; //position and velocity of the particle

};

#endif