//Emilio Taggi 1910388 2023/01/14
//Dataset.cc
#include "Dataset.h"

#include <iostream>
#include <fstream>
#include <string>
using std::string;

using namespace std;


//CONSTRUCTORS:

//Constructor by reference to file
Dataset::Dataset(int N,const char *filename){

    N_ = N; //I set the numbers of data in dataset

    
    ifstream infile(filename); //I create the input file object

    
    string line; // string to hold each line

    // control over file opening
    if(!infile.is_open()) {
        cerr << "cannot open input file" << endl;
        std::cout << "instance of classe Dataset not created" << std::endl;
    }

    
    
    double data;

    // loop over file until end-of-file
    while(!infile.eof()) {
        // get current line
        getline(infile,line);
        if( line == "\n" || line == "" ) continue;

     //parsing
     sscanf(line.c_str(),"%lf", &data);

    x_.push_back(data); //data storing
     

  } // !eof

  infile.close(); // close input file before exiting

}


//copy constructor
Dataset::Dataset(const Dataset& sourceDataset){
    N_ = sourceDataset.N_;
    x_ = sourceDataset.x_;
}

//Constructor by vector
Dataset::Dataset(const vector<double>& sourceVec){
    N_ = sourceVec.size();
    x_ = sourceVec;
}



//DATA MANAGING METHODS:

//add a new data point to the Dataset
void Dataset::addData(double newData){
    x_.push_back(newData); //add data
    N_ += 1;               //update N
}
//remove the last data point from the dataset
void Dataset::removeLastData(){
    x_.pop_back();     //remove data
    N_ -= 1;           //update N
}



//OVERLOADS

//shift by a number  +
Dataset Dataset::operator+(const double shift ) const{

    vector<double> newVec = x_;

    for(std::vector<double>::iterator d = newVec.begin(); d != newVec.end(); d++) {
        *d +=shift;
    } 

    return Dataset(newVec);


}





//UTILITY FUNCTIONS

//print dataset to screen:
void Dataset::print(const string& message) const{
    std::cout << message << std::endl;
    std::cout << "Dataset info:\n" 
              << "-N = " << N_
              << "\n-variable stored in dataset:" << std::endl;
    for(int i=0;i<N_;i++){
        std::cout << x_[i] << " ";
    }
    std::cout << "\n" << std::endl;

}