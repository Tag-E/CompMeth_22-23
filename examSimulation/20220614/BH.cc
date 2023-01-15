//Emilio Taggi 1910388 2023/01/15
//BH.cc
#include "BH.h"

#include <iostream>
#include <iomanip>
#include <string>
using std::string;

using namespace std;


//CONSTRUCTORS:

//default constructors
BH::BH(){
    m_ = 1.0; //set m to 1
    chi_ = 0.0; //and chi to 0
    mirr_ = mirr_eq_(m_,chi_);
    Epen_= Epen_eq_(m_,chi_);
}

//Private constructor, using all arguments
BH::BH(double m, double chi,double mirr,double Epen){
    m_=m;
    chi_=chi;
    mirr_=mirr; //i just assign them, the control is done in the other constructor
    Epen_=Epen;
}

//Constructor providing just m
BH BH::BH_by_m(double m){
    return BH(m,0.0,mirr_eq_(m,0.0),Epen_eq_(m,0.0));
}

//Constructor providing just chi
BH BH::BH_by_chi(double chi){
    return BH(1.0,chi,mirr_eq_(1.0,chi),Epen_eq_(1.0,chi));
}

//Constructor providing m and chi
BH BH::BH_by_m_chi(double m, double chi){
    return BH(m,chi,mirr_eq_(m,chi),Epen_eq_(m,chi));
}

//Constructor providing m and mirr
BH BH::BH_by_m_mirr(double m, double mirr){
    return BH(m,chi_eq_(m,mirr),mirr,m-mirr);
}

//Constructor providing chi and mirr
BH BH::BH_by_chi_mirr(double chi, double mirr){
    double m = m_eq_(chi,mirr);
    return BH(m,chi,mirr,m-mirr);
}

//copy constructor
BH::BH(const BH& sourceBH){
    m_ = sourceBH.m_;
    chi_ = sourceBH.chi_;
    mirr_ = sourceBH.mirr_;
    Epen_ = sourceBH.Epen_;
}



//SETTERS 


//set m, leave chi fixed, recompute mirr and E
void BH::set_m(double m){
    m_=m;
    mirr_ = mirr_eq_(m,chi_);
    Epen_ = Epen_eq_(m,chi_);
}
//set chi, leave m fixed, recompute mirr and E
void BH::set_chi(double chi){
    chi_ = chi;
    mirr_ = mirr_eq_(m_,chi);
    Epen_ = Epen_eq_(m_,chi);
}

//set m and chi and recompute mirr and E
void BH::set_m_chi(double m, double chi){
    m_ = m;
    chi_ = chi;
    mirr_ = mirr_eq_(m,chi);
    Epen_ = Epen_eq_(m,chi);
}

//set m and mirr and recompute chi and E
void BH::set_m_mirr(double m, double mirr){
    m_ = m;
    chi_ = chi_eq_(m,mirr);
    mirr_ = mirr;
    Epen_ = m-mirr;
}

//set chi and mirr and recompute m and E
void BH::set_chi_mirr(double chi, double mirr){
    m_ = m_eq_(chi,mirr);
    chi_ = chi;
    mirr_ = mirr;
    Epen_ = m_-mirr;
}





//UTILITY FUNCTIONS

//print info to screen:
void BH::print(const string& message, int precision) const{

    std::cout << std::fixed;
    std::cout << std::setprecision(precision); //to see just 3 digits in prints

    std::cout << message << std::endl;
    std::cout << "Black Hole info:" 
              << "\n-m = " << m_
              << "\n-chi = " << chi_
              << "\n-m_irr = " << mirr_
              << "\n-E_pen = " << Epen_ << std::endl;
}