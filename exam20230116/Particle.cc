//Emilio Taggi 1910388 2023/01/16
//Particle.cc
#include "Particle.h"

#include <iostream>
using namespace std;

#include <string>
using std::string;

#include "TVector3.h" //for the particle's position and velocity



//CONSTRUCTORS:


//default constructor
Particle::Particle(){
    m_ = 1.0;
    x_ = TVector3(0.0,0.0,0.0);
    v_ = TVector3(1.0,0.0,0.0);
}
//Constructor by argument
Particle::Particle(double m,const TVector3& x,const TVector3& v){
    m_=m;
    x_=x;
    v_=v;
}
//copy constructor
Particle::Particle(const Particle& sourceParticle){
    m_ = sourceParticle.m_;
    x_ = sourceParticle.x_;
    v_ = sourceParticle.v_;
}



//UTILITY METHODS:

//print info to screen
void Particle::print(const string& message) const{
    std::cout << message << std::endl;
    std::cout << "Particle's info:" 
              << "\n-m = " << m_ 
              << "\n-x:\nx1 = "<< x_.x() << ", x2 = " << x_.y() << ", x3 = " << x_.z()
              << "\n-v:\nv1 = "<< v_.x() << ", v2 = " << v_.y() << ", v3 = " << v_.z() << std::endl;
}
