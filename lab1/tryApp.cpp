#include "Vector3D.h"
#include <iostream>
#include <cmath>

#define PI atan(1)*4  //py

using namespace std;

int main(){

    double pi = PI;

    Vector3D myVec;
    Vector3D myVec2 = Vector3D::cartesianVec3D(0.0,4.0,3.0);
    Vector3D myVec3 = Vector3D::sphericalVec3D(1.0,0.0,0.0);


    myVec.print();
    myVec2.print();
    myVec3.print();

    myVec3.setz(19.0);

    cout << "ultima z: " << myVec3.z() << endl;

    double prodotto;
    prodotto = myVec2.scalarProduct(myVec3);
    
    cout << "prod2-3: " << prodotto << endl;

    double r = myVec2.magnitude();

    cout << "magnitude2: " << r << endl;

    Vector3D myVec4 = Vector3D::cartesianVec3D(1.0,0.0,0.0);
    Vector3D myVec5 = Vector3D::cartesianVec3D(0.0,1.0,0.0);
    Vector3D myVec6 = Vector3D::cartesianVec3D(0.0,0.0,3.0);

    cout << "angle4-5: " << toDeg(angle(myVec4,myVec5)) << endl;
    cout << "angle4-6: " << angle(myVec4,myVec6) << endl;
    cout << "angle5-6: " << angle(myVec5,myVec6) << endl;

    Vector3D vecSum = myVec4+myVec5;
    Vector3D vecDif = myVec4-myVec5;

    vecSum.print();
    vecDif.print();

    Vector3D vecProd = myVec4 * 7;
    vecProd.print();
    Vector3D vecProd2 = 7 * myVec4 ;
    vecProd2.print();

    return 0;
}