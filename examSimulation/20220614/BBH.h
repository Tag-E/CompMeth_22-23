//Emilio Taggi 1910388 2023/01/15
//BBH.h
#ifndef BBH_h
#define BBH_h

#include "BH.h"

#include <string> //for the message in print
using std::string;

#include <cmath>


class BBH{

    public:

    //CONSTRUCTORS:

    //copy constructor
    BBH(const BBH& sourceBHH);
    //constructor data of two black holes and angles
    BBH(double m1, double m2, double chi1, double chi2, double theta1, double theta2);

    //UTILITY METHODS:
    
    //print info screen
    void print(const string& message = string(), int precision=4) const;


    private:

    BH bh1_, bh2_; //two black holes in the system
    double theta1_, theta2_; //angles relative to the black hole
    double chi_eff_; //effective dimensionless angular momentum of the system

    //equation used to compute chi_eff_ given the other parameters
    static double chi_eff_eq_(double m1, double m2, double chi1, double chi2, double theta1, double theta2);

};

#endif