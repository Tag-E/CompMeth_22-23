//Emilio Taggi 1910388 2023/01/15
//app.cpp
#include "BH.h"
#include "BBH.h"

#include <iostream>
using namespace std;

int main(){

    //Demonstration of class BH

    //constructors:
    BH bh1 = BH::BH_by_m(2.0);
    //print
    bh1.print("bh1");

    BH bh2 = BH::BH_by_chi_mirr(0.5,2.0);
    bh2.print("bh2");

    //copy constructor
    BH bh3 = bh2;
    bh3.print("bh3");

    //setter
    bh3.set_m(9.0);
    bh3.print("bh3 modified",5);

    //getter
    std::cout << "bh3 Epen = " << bh3.Epen() << std::endl;

    //BBH

    //constructor
    BBH bbh1 = BBH(1.0,1.0,0.1,0.2,0.3,0.4);
    bbh1.print("BBH System 1");

    BBH bbh2 = bbh1;
    bbh2.print("BBH System 2");





    return 0;
}