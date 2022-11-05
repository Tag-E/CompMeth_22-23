//decay2.h 
/*utility class for Particle class,
  simulates a 2 particle decay
  */
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

    //Constructor
    Decay2(const Particle& mother,double m1, double m2);

    //FUNCTIONS:

    //value of momentum of the particle in the decay
    double p_star();
    //momentum for one of the decay product 
    TVector3 random_p3Son();
    //pair of 4-momenta for the 2 son particles in the COM frame
    vector<TLorentzVector> random_p4_pair();
    //pair of 4-momenta for the 2 son particles in the LAB frame
    vector<TLorentzVector> random_p4_pairBOOSTED();

    private:
    Particle mother_; //mother Particle
    double m1_; //masses of the 2 produced particle
    double m2_;
    TRandom gen_; //instance of a random generator 
};

#endif