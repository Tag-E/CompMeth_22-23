//Emilio Taggi 1910388 2023/01/16
//Ensemble.h
#ifndef Ensemble_h
#define Ensemble_h

#include <iostream>
using namespace std;

#include <string> //for the message in print
using std::string;

#include "TVector3.h" //for the Ensemble's position and velocity

#include "Particle.h" //for the particles
#include "TRandom3.h" //for the random generator

#include <vector>
using std::vector;

const double K_BOLTZ = 1.38*pow(10,-23); //Boltzmann constant in SI units

//to address the type of distribution
#define UNIFORM 0
#define GAUSSIAN 1


class Ensemble{

    public:

    //CONSTRUCTORS:

    //Default Constructor
    Ensemble();
    //Constructor by number of particle
    Ensemble(int N);
    //copy constructor
    //Ensemble(const Ensemble& sourceEnsemble);
    //Constructor with uniform distribution
    static Ensemble EnsembleUniform(int N, double m_min, double m_max, double x_min, double x_max, double v_min, double v_max);
    //Constructor with uniform distribution
    static Ensemble EnsembleGaussian(int N, double m_mean, double m_sigma, double x_mean, double x_sigma, double v_mean, double v_sigma);


    //GETTERS

    //return the number of particle in the Ensemble
    int N() const {return N_;}
    //return the total mass of the Ensemble
    double M() const {return M_;}
    //return the temperature of the Ensemble
    double T() const {return T_;}
    //return the vector of particles of the ensamble
    vector<Particle> particles() const {return particles_;}
    //return the center of mass
    TVector3 CoM() const {return CoM_;}



    //SETTERS
    
    //set the value of the mass of the Ensemble
    //void set_N(int N) {N_=N;}

    //UTILITY METHODS:

    //print info to screen
    void print(const string& message = string()) const;
    

    private:
    int N_; //number of particles in the Ensemble
    vector<Particle> particles_; //array containing the particle instances of the Ensemble
    TRandom3 gen_; //instance of a random generator used to generate the particles
    double M_;//total mass of the Ensemble
    TVector3 CoM_; //center of mass of the Ensemble 
    double K_; //average kinetic energy
    double T_; //temperature 

    //generate the particles of the Ensemble uniformly
    void fillEnsemble_Uniform_(double m_min, double m_max, double x_min, double x_max, double v_min, double v_max);
    //generate the particles of the Ensemble gaussian
    void fillEnsemble_Gaussian_(double m_mean, double m_sig, double x_mean, double x_sig, double v_mean, double v_sig);

    //compute the total mass of the Ensemble
    double get_totalMass_();
    //compute the center of mass of the Ensemble
    TVector3 get_centerofmass_();
    //compute the average kinetic energy
    double get_averageK_();
    //compute the Temperature
    double get_T_();

    //private constructor (par1 and par2 are max min if uniform=0, mean sigma if gaussian=1)
    Ensemble(int N,int distrType, double m_par1, double m_par2, double x_par1, double x_par2, double v_par1, double v_par2);

};

#endif