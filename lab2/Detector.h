//Detector.h
#ifndef Detector_h
#define Detector_h


#include "TRandom3.h" //for the random generator
#include "TVector3.h" //for 3 Vectors
#include "TLorentzVector.h" //for the particle 4-momentum

class Detector{
    public:
    //COSTRUCTORS

    //constructor by arguments
    Detector(double resolution);

    //GETTERS

    //return the resolution of the detector
    double resolution() const {return resolution_; }

    //SETTERS

    //set the resolution of the detector
    void setRes(double resolution) {resolution_ = resolution;}


    //FUNCTIONS

    //return a smeared 3vector
    TVector3 smearing(const TVector3& sourceVec);

    //return a smeared 4vector
    TLorentzVector smearing(const TLorentzVector& sourceVec);

    private:
    double resolution_; //resolution of the detector
    TRandom3 gen_; //instance of a random generator 
};

#endif