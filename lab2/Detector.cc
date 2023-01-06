//Detector.cc
#include "Detector.h"


#include "TRandom3.h" //for the random generator
#include "TVector3.h" //for 3 Vectors

#include <iostream>

using std::cout;
using std::endl;

//Constructor by argument
Detector::Detector(double resolution){
    resolution_ = resolution;
    gen_ = TRandom3(); //instance of a TRandom generator
    gen_.SetSeed(0);//setting the seed for the random generator
}



//smearing of a 3 vector
TVector3  Detector::smearing(const TVector3& sourceVec){
    double smearing_factor = gen_.Gaus(1.0, resolution_); //I get a correction factor around 1.0
    return TVector3(sourceVec*smearing_factor); //I multiply each component of the 3 vector by this factor
}



//smearing of a 4 vector
/*TLorentzVector  Detector::smearing(const TLorentzVector& sourceVec){
    //double mag = sourceVec.Vect().Mag(); //magnitude of the 3 vector
    double smeared_ratio = gen_.Gaus(1.0, resolution_); //Smearing of the magnitude
    //double ratio = smeared_mag/mag; //percentual smearing
    TVector3 smearedP = sourceVec.Vect() * smeared_ratio; //P of the new 4Momentum
    //double newE = sqrt( smeared_mag*smeared_mag + sourceVec.M2() - mag*mag ); //Energy of the smeared 4momentum
    return TLorentzVector(smearedP,sourceVec.E()); //I return the smeared vector
}*/
