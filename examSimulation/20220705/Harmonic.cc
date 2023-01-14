//Emilio Taggi 1910388 2023/01/14
//Harmonic.cc
#include "Harmonic.h"
#include "Dataset.h"

#include <iostream>
using namespace std;

#include <cmath>


//CONSTRUCTORS:

Harmonic::Harmonic(const Dataset& sourceDataset) : Dataset(sourceDataset){}


//VIRTUAL METHODS:

//compute Harmonic mean
double Harmonic::mean() const{

    double sum=0.0; // I initialize the mean to 0
    vector<double> entries = x();

    for(std::vector<double>::iterator d = entries.begin(); d != entries.end(); d++) {
        sum += 1.0 / *d;
    }

    return N()/sum ;

}

//print dataset to screen:
void Harmonic::print(const string& message) const{
    std::cout << message << std::endl;
    std::cout << "Dataset info:\n" 
              << "-N = " << N()
              << "\n-variable stored in dataset:" << std::endl;
    for(int i=0;i<N();i++){
        std::cout << x()[i] << " ";
    }
    std::cout << "\n-Mean = " << mean() << "\n" << std::endl;

}