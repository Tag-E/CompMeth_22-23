//Emilio Taggi 1910388 2023/01/15
//BBH.cc
#include "BBH.h"

#include <cmath>

#include <iostream>
#include <iomanip>
#include <string>
using std::string;

using namespace std;


//CONSTRUCTORS


//copy constructor
BBH::BBH(const BBH& sourceBBH){
    bh1_ = sourceBBH.bh1_;
    bh2_ = sourceBBH.bh2_;
    theta1_ = sourceBBH.theta1_;
    theta2_ = sourceBBH.theta2_;
    chi_eff_ = sourceBBH.chi_eff_;
}


//constructor data of two black holes and angles
BBH::BBH(double m1, double m2, double chi1, double chi2, double theta1, double theta2){
    bh1_ = BH::BH_by_m_chi(m1,chi1); //I construct the 2 black holes
    bh2_ = BH::BH_by_m_chi(m2,chi2);
    theta1_ = theta1;
    theta2 = theta2_;
    chi_eff_ = chi_eff_eq_(m1,m2,chi2,chi2,theta2,theta2);
}

//UTILITY METHODS:

//print info screen
void BBH::print(const string& message, int precision) const{

    std::cout << std::fixed;
    std::cout << std::setprecision(precision); //to see just 3 digits in prints

    std::cout << message << std::endl;
    std::cout << "Binary Black Hole System info:" 
              << "\n-theta1 = " << theta1_
              << "\n-theta2 = " << theta2_
              << "\n-chi_eff = " << chi_eff_ << std::endl;
    bh1_.print("Black Hole 1:",precision);
    bh2_.print("Black Hole 2:",precision);
}



//OTHER:

//equation used to compute chi_eff_ given the other parameters
double BBH::chi_eff_eq_(double m1, double m2, double chi1, double chi2, double theta1, double theta2){
    return  (chi1*m1*cos(theta1) + chi2*m2*cos(theta2) ) / (m1+m2);
}


