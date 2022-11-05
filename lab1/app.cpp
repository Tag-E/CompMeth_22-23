#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <vector>


using namespace std;

int main(){

    int n; //numero di vettori scelto dall'utente

    cout << "Please decide how many vector to input: " ;
    cin >> n;
    cout << "Excellent choice!" << endl;

    /*
     ...
     missing input control
     ...
    */

    cout << "Now prepare to input them one by one by cartesian coordinates" << endl;

    vector< Vector3D > vecList; //vector of Vector3D

    double x,y,z; //value given in input by the user

    //loop on the vector to add
    for(int i=0;i<n;i++){
        cout << "Vettore " << i+1 << endl;

        cout << "x_" << i+1 << " : ";
        cin >> x;
        cout << "y_" << i+1 << " : ";
        cin >> y;
        cout << "z_" << i+1 << " : ";
        cin >> z;

        /*
         ...
         missing input control
         ...
        */

        vecList.push_back( Vector3D::cartesianVec3D(x,y,z) );

    }

    cout << "Now follows the list of magnitudes of the given vectors:" << endl;

    int i=0;
    //loop to print the magnitudes
    for(vector<Vector3D>::iterator v_it = vecList.begin();v_it != vecList.end(); v_it++){
        i++;
        cout << "r_" << i << " = " << v_it->magnitude()<< endl;
    }    

    return 0;
}