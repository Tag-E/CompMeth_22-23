//Emilio Taggi 1910388
//app2.cpp

#include <iostream>
#include <cmath>

#include "Capacitor.h"

using namespace std;

using std::cout;
using std::endl;

int main(){

    Capacitor defaultCap = Capacitor();

    cout << "Default initialized Capacitor:" << endl;
    defaultCap.print();

    Capacitor myCap = Capacitor(25*pow(10,-9));

    cout << "Capacitor initialized by argument:" << endl;
    myCap.print();

    Capacitor copyCap = Capacitor(myCap);

    cout << "Capacitor initialized by copy constructor:" << endl;
    copyCap.print();

    cout << "With a capacitor C=" << myCap.C() << " F"
         << "\n- A(eps_r=80,s=1 m) = " << myCap.get_A(80,1) << " m**2"
         << "\n- s(eps_r=80,A=1 m**2) = " << myCap.get_s(80,1) << " m"
         << "\n- eps_r(A=1 m**2,s=1 m) = " << myCap.get_eps_r(1,1) << endl;


    Capacitor cap1 = Capacitor(10*pow(10,-9)), cap2 = Capacitor(20*pow(10,-9));

    cout << "cap1 = " << cap1.C() << endl;
    cout << "cap2 = " << cap2.C() << endl;

    Capacitor C_series = cap1+cap2, C_parallel = cap1||cap2;

    cout << "cap1+cap2 = " << C_series.C() << endl;
    cout << "cap1||cap2 = " << C_parallel.C() << endl;



    return 0;
}