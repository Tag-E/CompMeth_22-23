//Emilio Taggi 1910388 2023/01/14
//Arithmetic.cc
#include "Arithmetic.h"
#include "Dataset.h"

#include <iostream>
using namespace std;


//CONSTRUCTORS:

Arithmetic::Arithmetic(const Dataset& sourceDataset) : Dataset(sourceDataset){}


//VIRTUAL METHODS:

//compute arithmetic mean
double Arithmetic::mean() const{

    double sum=0.0; // I initialize the mean to 0
    vector<double> entries = x();

    for(std::vector<double>::iterator d = entries.begin(); d != entries.end(); d++) {
        sum += *d;
    }

    return sum/N() ;

}

//print dataset to screen:
void Arithmetic::print(const string& message) const{
    std::cout << message << std::endl;
    std::cout << "Dataset info:\n" 
              << "-N = " << N()
              << "\n-variable stored in dataset:" << std::endl;
    for(int i=0;i<N();i++){
        std::cout << x()[i] << " ";
    }
    std::cout << "\n-Mean = " << mean() << "\n" << std::endl;

}