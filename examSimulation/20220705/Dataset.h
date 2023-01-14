//Emilio Taggi 1910388 2023/01/14
//Dataset.h
#ifndef Dataset_h
#define Dataset_h

#include <string> //for the message in print
using std::string;

#include <vector>
using std::vector;

class Dataset{

    public:

    //CONSTRUCTORS:

    //Constructor by reference to file
    Dataset(int N,const char *filename);
    //copy constructor
    Dataset(const Dataset& sourceDataset);
    //Constructor by vector
    Dataset(const vector<double>& sourceVec);


    //GETTERS

    //return N size of the dataset
    int N() const {return N_;}
    //return vector with data points
    vector<double> x() const {return x_;}


    //DATA MANAGING METHODS:

    //add a new data point to the Dataset
    void addData(double newData);
    //remove the last data point from the dataset
    void removeLastData();

    //class to be implemented in derived class
    virtual double mean() const {return 0;}



    //OVERLOADS:

    //shift by a number  +
    Dataset operator+(const double shift ) const;




    //UTILITY METHODS:
    virtual void print(const string& message = string()) const;

    private:
    int N_; //number of elements in dataset
    vector<double> x_; //array containing the data point

};

#endif
