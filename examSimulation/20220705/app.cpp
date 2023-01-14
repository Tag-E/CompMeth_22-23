//Emilio Taggi 1910388 2023/01/14
#include "Dataset.h"
#include "Arithmetic.h"
#include "Geometric.h"
#include "Harmonic.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

    
    const char filepath[30] = "data1.dat"; //input file for data1

    std::cout << filepath << endl;


    //constructor by reference to file
    Dataset d1 = Dataset(7,filepath);
    d1.print("d1:");

    //copy constructor
    Dataset d2 = Dataset(d1);
    d2.print("d2:");

    //method to add a point
    d2.addData(15);
    d2.addData(8.45126);
    d2.print("d2+newdata:");

    //method to remove a point
    d2.removeLastData();
    d2.print("d2,dataremoved:");

    //overload of +
    Dataset d3 = d2+10;
    d3.print("d3 = d2+10:");

    //class arithmetic
    Arithmetic a = Arithmetic(d3);
    a.print("a:");

    //class geometric
    Geometric g = Geometric(d2);
    g.print("g:");

    //class Harmonic
    Harmonic h = Harmonic(d2);
    h.print("h:");


    return 0;
}
