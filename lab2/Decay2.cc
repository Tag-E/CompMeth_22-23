//Decay2.cc
#include "Decay2.h"
#include <iostream>
#include <cmath>
#include "TRandom.h"
#include <vector> 
#include "TLorentzVector.h" //for the particle 4-momentum

using std::vector;
using std::cout;
using std::endl;


//CONSTRUCTORS

//Constructor of the decay
Decay2::Decay2(const Particle& mother,double m1, double m2){
    mother_ = mother;
    m1_ = m1;
    m2_ = m2;
    gen_ = TRandom(); //instance of a TRandom generator
    gen_.SetSeed(0);//setting the seed for the random generator
}


//FUNCTIONS

//compute magnitude of p* of the decay product
double Decay2::p_star(){
    double M = mother_.m(); //mass of the particle that decays
    return sqrt(pow(M,4)+pow(m1_,4)+pow(m2_,4)-2*pow(M,2)*pow(m1_,2)-2*pow(M,2)*pow(m2_,2)-2*pow(m1_,2)*pow(m2_,2)) * 0.5 / M;
}

//compute a random oriented momentum with the right magnitude for a decay product
TVector3 Decay2::random_p3Son(){
    double p = Decay2::p_star(); //radius of the sphere given by p*
    double x,y,z; //coordinates of the momentum to be generated
    gen_.Sphere(x,y,z,p); //I generate a theta* and a phy* such that x,y,z are on a sphere of radius p*
    return TVector3(x,y,z);
}

//return the pair of 4-momenta of the 2 decay product in the COM frame
vector<TLorentzVector> Decay2::random_p4_pair(){
    TVector3 p3_1 = Decay2::random_p3Son(); //random generate a 3momentun
    TVector3 p3_2 = -p3_1; //being in the com frame the second one is the opposite

    TLorentzVector p4_1,p4_2; //pair of 4-momenta to be returned
    p4_1.SetVect(p3_1);
    p4_1.SetE(sqrt(p3_1.Mag2() + m1_*m1_)); //4 momenta of the first particle
    p4_2.SetVect(p3_2);
    p4_2.SetE(sqrt(p3_2.Mag2() + m2_*m2_)); //4 momenta of the second particle

    vector<TLorentzVector> p4_pair; //I put the two 4-momenta in a vector
    p4_pair.push_back(p4_1);
    p4_pair.push_back(p4_2);

    return p4_pair;

}

//return the pair of 4-momenta of the 2 decay product in the LAB frame
vector<TLorentzVector> Decay2::random_p4_pairBOOSTED(){
    vector<TLorentzVector> p4_pair = Decay2::random_p4_pair(); //pair of non boosted 4 momenta

    TVector3 BoostVec = mother_.p4().BoostVector(); // I boost according to the decay particle
    p4_pair.at(0).Boost(BoostVec);
    p4_pair.at(1).Boost(BoostVec);

    return p4_pair; //I return the two 4momenta boosted
}

//UTILITY FUNCTIONS

//printout of decay information
void Decay2::info() const{
    cout<< "\nInformation about the decay\n"
        << "\n-Masses of the two decay product:"
        << "\n  -m1 = " << m1_ << " MeV"
        << "\n  -m2 = " << m2_ << " MeV"
        << "\n-Info about the mother particle:" << endl;
    mother_.print();
}