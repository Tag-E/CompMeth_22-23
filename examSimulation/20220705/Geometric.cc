//Emilio Taggi 1910388 2023/01/14
//Geometric.cc
#include "Geometric.h"
#include "Dataset.h"

#include <iostream>
using namespace std;

#include <cmath>


//CONSTRUCTORS:

Geometric::Geometric(const Dataset& sourceDataset) : Dataset(sourceDataset){}


//VIRTUAL METHODS:

//compute Geometric mean
double Geometric::mean() const{

    double sum=1.0; // I initialize the mean to 0
    vector<double> entries = x();

    for(std::vector<double>::iterator d = entries.begin(); d != entries.end(); d++) {
        sum *= *d;
    }

    return pow(sum,1.0/N()) ;

}

//print dataset to screen:
void Geometric::print(const string& message) const{
    std::cout << message << std::endl;
    std::cout << "Dataset info:\n" 
              << "-N = " << N()
              << "\n-variable stored in dataset:" << std::endl;
    for(int i=0;i<N();i++){
        std::cout << x()[i] << " ";
    }
    std::cout << "\n-Mean = " << mean() << "\n" << std::endl;

}