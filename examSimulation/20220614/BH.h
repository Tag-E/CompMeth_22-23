//Emilio Taggi 1910388 2023/01/15
//BH.h
#ifndef BH_h
#define BH_h

#include <string> //for the message in print
using std::string;

#include <cmath>


class BH{

    public:

    //CONSTRUCTORS:

    //default constructor
    BH();
    //Constructor providing just m
    static BH BH_by_m(double m);
    //Constructor providing just chi
    static BH BH_by_chi(double chi);
    //Constructor providing m and chi
    static BH BH_by_m_chi(double m, double chi);
    //Constructor providing m and mirr
    static BH BH_by_m_mirr(double m, double mirr);
    //Constructor providing chi and mirr
    static BH BH_by_chi_mirr(double chi, double mirr);
    //copy constructor
    BH(const BH& sourceBH);



    //GETTERS

    //return  gravitational mass of the black hole
    double m() const {return m_;}
    //return  adimensional rotational angular momentum of the black hole
    double chi() const {return chi_;}
    //return  irreducible mass of the black hole
    double mirr() const {return mirr_;}
    //return  energy of the black hole
    double Epen() const {return Epen_;}



    //SETTERS 

    //set m, leave chi fixed, recompute mirr and E
    void set_m(double m);
    //set chi, leave m fixed, recompute mirr and E
    void set_chi(double chi);
    //set m and chi and recompute mirr and E
    void set_m_chi(double m, double chi);
    //set m and mirr and recompute chi and E
    void set_m_mirr(double m, double mirr);
    //set chi and mirr and recompute m and E
    void set_chi_mirr(double chi, double mirr);





    //UTILITY METHODS:
    
    //print info to screen
    void print(const string& message = string(), int precision=4) const;




    private:

    double m_; //gravitational mass(in units of solar mass) 
    double chi_; //rotational angular momentum (adimensional)
    double mirr_; //irreducible mass of the black hole
    double Epen_; //energy

    //Private constructor
    BH(double m, double chi,double mirr,double Epen); //I use all arguments

    //equation used to compute one parameter given the others
    static double mirr_eq_(double m, double chi) {return m*sqrt( 0.5*( 1+sqrt( 1-chi*chi ) ) ) ;}
    static double Epen_eq_(double m, double chi) {return m*(1 - sqrt( 0.5*( 1+sqrt( 1-chi*chi ) ) ) ) ;}
    static double m_eq_(double chi, double mirr) {return mirr*sqrt( 2/( 1+sqrt( 1-chi*chi ) ) ) ;}
    static double chi_eq_(double m, double mirr) {return sqrt( 1- pow( 2*mirr*mirr/(m*m)-1  ,2) ) ;}
    

    
};

#endif