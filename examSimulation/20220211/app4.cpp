//Emilio Taggi 1910388
//app4.cpp

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#include "TRandom3.h" //for the random generation

#include "Capacitor.h"

using namespace std;

using std::cout;
using std::endl;
using std::vector;

int main(){

    Capacitor C2 = Capacitor(10*pow(10,-12)), C3 = Capacitor(5*pow(10,-12)), C4 = Capacitor(15*pow(10,-12));

    int Ncap = 1000; //number or random C1 we want
    double C1_min = 1*pow(10,-12), C1_max = 100*pow(10,-12);

    //I set up a random generator
    TRandom3*  gen = new TRandom3();
    gen->SetSeed(0);

    vector <double> Ceq_list, C1_list;

    // I open an output file
    ofstream outfile;
    outfile.open ("true.dat");
    outfile << "# C1[F/m] Ceq[F/m]" << endl;

    //generation loop
    for(int i=0;i<Ncap;i++){

        Capacitor C1(C1_min+gen->Uniform(C1_max));

        Capacitor Ceq = (C1||C2) + (C3||C4) ;

        Ceq_list.push_back(Ceq.C());
        C1_list.push_back(C1.C());

        outfile << C1.C() << " " << Ceq.C() << endl;

    }

    //remove allocated memory
    delete gen;

    //closed open file
    outfile.close();


    return 0;
}