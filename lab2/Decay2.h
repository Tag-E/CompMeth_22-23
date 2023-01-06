//Decay2.h 
/*Class used to simulate a 2 particle decay
  Given a mother particle and the mass of the
  2 decay product the class is able to 
  compute all the interesting quantities
  relative to the decay*/
#ifndef Decay2_h
#define Decay2_h

#include "Particle.h"
#include "TVector3.h" //for 3 Vectors
#include "TRandom.h" //for the random generator
#include "TLorentzVector.h" //for the particle 4-momentum
#include <vector> 

using std::vector;

class Decay2{
    public:

    //CONSTRUCTORS

    //Constructor by argument
    Decay2(const Particle& mother,double m1, double m2);


    //GETTERS

    //return the mass of the first decay product
    double m1() const {return m1_; }
    //return the mass of the second decay product
    double m2() const {return m2_; }


    //SETTERS

    //set the mass of the first decay product
    void setm1(double m1) {m1_ = m1; }
    //set the mass of the second decay product
    void setm2(double m2) {m2_ = m2; }


    //FUNCTIONS:

    //value of momentum of the particle in the decay (COM)
    double p_star();
    //momentum for one of the decay product 
    TVector3 random_p3Son();
    //pair of 4-momenta for the 2 son particles in the COM frame
    vector<TLorentzVector> random_p4_pair();
    //pair of 4-momenta for the 2 son particles in the LAB frame
    vector<TLorentzVector> random_p4_pairBOOSTED();


    //UTILITY FUNCTION

    //printout of decay information
    void info() const;



    private:
    Particle mother_; //mother Particle
    double m1_; //masses of the 2 produced particle
    double m2_;
    TRandom gen_; //instance of a random generator 
};

#endif