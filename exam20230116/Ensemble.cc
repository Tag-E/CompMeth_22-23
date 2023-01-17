//Emilio Taggi 1910388 2023/01/16
//Ensemble.cc
#include "Ensemble.h"

#include "Particle.h" //for the particles
#include "TRandom3.h" //for the random generator

#include <iostream>
using namespace std;

#include <string>
using std::string;

#include "TVector3.h" //for the Ensemble's position and velocity

#include <vector>
using std::vector;



//CONSTRUCTORS:


//Default Constructor
Ensemble::Ensemble(){
    N_ = 3; //default value for N
    gen_ = TRandom3(); //instance of a TRandom generator
    gen_.SetSeed(0);//setting the seed for the random generator
    fillEnsemble_Uniform_(1,10,-10,10,-10,10); //by default I fill the Ensemble uniformly in this way
    M_ = get_totalMass_();
    CoM_ = get_centerofmass_();
    K_ = get_averageK_();
    T_ = get_T_();
}
//Constructor by number of particle
Ensemble::Ensemble(int N){
    N_ = N; //set N
    gen_ = TRandom3(); //instance of a TRandom generator
    gen_.SetSeed(0);//setting the seed for the random generator
    fillEnsemble_Uniform_(1,10,-10,10,-10,10); //by default I fill the Ensemble uniformly in this way
    M_ = get_totalMass_();
    CoM_ = get_centerofmass_();
    K_ = get_averageK_();
    T_ = get_T_();
}

//copy constructor
//Ensemble(const Ensemble& sourceEnsemble);

//Constructor with uniform distribution
Ensemble Ensemble::EnsembleUniform(int N, double m_min, double m_max, double x_min, double x_max, double v_min, double v_max){
    return Ensemble(N,UNIFORM,m_min,m_max,x_min,x_max,v_min,v_max);
}
//Constructor with uniform distribution
Ensemble Ensemble::EnsembleGaussian(int N, double m_mean, double m_sigma, double x_mean, double x_sigma, double v_mean, double v_sigma){
   return  Ensemble(N,GAUSSIAN,m_mean,m_sigma,x_mean,x_sigma,v_mean,v_sigma);
}

//PRIVATE CONSTUCTOR
Ensemble::Ensemble(int N,int distrType, double m_par1, double m_par2, double x_par1, double x_par2, double v_par1, double v_par2){
    N_ = N; //set N
    gen_ = TRandom3(); //instance of a TRandom generator
    gen_.SetSeed(0);//setting the seed for the random generator

    if(distrType==UNIFORM){ //if the distribution is uniform
        fillEnsemble_Uniform_(m_par1,m_par2,x_par1,x_par2,v_par1,v_par2); 
    }
    else{ //if is gaussian
        fillEnsemble_Gaussian_(m_par1,m_par2,x_par1,x_par2,v_par1,v_par2); 
    }
    //complete construction
    M_ = get_totalMass_();
    CoM_ = get_centerofmass_();
    K_ = get_averageK_();
    T_ = get_T_();
}




//UTILITY METHODS:

//print info to screen
void Ensemble::print(const string& message) const{
    std::cout << message << std::endl;
    std::cout << "Ensemble's info:" 
              << "\n-N = " << N_
              << "\n-T = " << T_
              << std::endl;
    particles_.begin()->print("First particle in the Ensemble");
}



//PRIVATE METHODS:

//fill the Ensemble using uniform distributions
void Ensemble::fillEnsemble_Uniform_(double m_min, double m_max, double x_min, double x_max, double v_min, double v_max){
    
    double m;
    double x1,x2,x3,v1,v2,v3; //m, coordinates of x and v to fill uniformly
    for(int i=0;i<N_;i++){ //loop to fill the array of particle
        m = m_min + gen_.Uniform(m_max-m_min);
        x1 = x_min + gen_.Uniform(x_max-x_min);
        x2 = x_min + gen_.Uniform(x_max-x_min);
        x3 = x_min + gen_.Uniform(x_max-x_min);
        v1 = v_min + gen_.Uniform(v_max-v_min);
        v2 = v_min + gen_.Uniform(v_max-v_min);
        v3 = v_min + gen_.Uniform(v_max-v_min);
        //now I create the particle and store it in the vector of the Ensemble
        particles_.push_back(Particle(m,TVector3(x1,x2,x3),TVector3(v1,v2,v3)));
    }
}

//fill the Ensemble using uniform distributions
void Ensemble::fillEnsemble_Gaussian_(double m_mean, double m_sig, double x_mean, double x_sig, double v_mean, double v_sig){

    double m; //mass
    double x1,x2,x3,v1,v2,v3; //m, coordinates of x and v to fill gaussianly
    for(int i=0;i<N_;i++){ //loop to fill the array of particle

        m = gen_.Gaus(m_mean,m_sig);

        x1 = gen_.Gaus(x_mean,x_sig);
        x2 = gen_.Gaus(x_mean,x_sig);
        x3 = gen_.Gaus(x_mean,x_sig);
        v1 = gen_.Gaus(v_mean,v_sig);
        v2 = gen_.Gaus(v_mean,v_sig);
        v3 = gen_.Gaus(v_mean,v_sig);
        //now I create the particle and store it in the vector of the Ensemble
        particles_.push_back(Particle(m,TVector3(x1,x2,x3),TVector3(v1,v2,v3)));
    }
    
}

//compute the total mass of the Ensemble
double Ensemble::get_totalMass_(){
    double totalMass = 0.0;//total mass of the Ensemble
    //loop over the particles
    for(std::vector<Particle>::iterator p = particles_.begin(); p != particles_.end(); p++) {
        totalMass += p->m(); //add particle's mass
    } 
    return totalMass; //total mass
}

//compute the center of mass of the Ensemble
TVector3 Ensemble::get_centerofmass_(){
    double x1_com = 0.0, x2_com = 0.0, x3_com = 0.0;//coordinates of center of mass
    double totalMass = 0.0;

    double temp_mass = 0.0; //temporary variable used to make the loop faster
    TVector3 temp_position;
    //loop over the particles
    for(std::vector<Particle>::iterator p = particles_.begin(); p != particles_.end(); p++) {
        temp_position = p->x(); //get info abou the i-th particle
        temp_mass = p->m();

        totalMass += temp_mass; //compute total mass

        x1_com += temp_position.x() *  temp_mass; //compute center of mass
        x2_com += temp_position.y() *  temp_mass;
        x3_com += temp_position.z() *  temp_mass;
    } 
    x1_com /= totalMass;
    x2_com /= totalMass;
    x3_com /= totalMass;
    return TVector3(x1_com,x2_com,x3_com); //center of mass
}


//compute the average kinetic energy
double Ensemble::get_averageK_(){
    double averageK=0.0; //initilize K
    for(std::vector<Particle>::iterator p = particles_.begin(); p != particles_.end(); p++) {
        averageK += p->m() * p->v().Mag2(); //compute 2*K
    }
    return averageK*0.5;
}

//compute the Temperature
double Ensemble::get_T_(){
    return 2.0/3.0 * K_ / K_BOLTZ; //return T
}