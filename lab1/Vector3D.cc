#include "Vector3D.h"
#include <iostream>
#include <cmath>

#define PI atan(1)*4 //py
double pi = PI;
double invPi = 1.0/pi ;

using namespace std;

//constructor definition

Vector3D::Vector3D(){ //constructor for default inizialization (all 0s) 
    x_ = 0.0;
    y_ = 0.0;
    z_ = 0.0;
}

Vector3D::Vector3D(double x, double y, double z){ //private constructor
    x_ = x;
    y_ = y;
    z_ = z;
}

Vector3D::Vector3D(const Vector3D& sourceVec){ //copy constructor
    x_ = sourceVec.x_;
    y_ = sourceVec.y_;
    z_ = sourceVec.z_;
} 

Vector3D Vector3D::cartesianVec3D(double x, double y, double z){ //construct by cartesian coordinate
    return Vector3D(x,y,z);
}

Vector3D Vector3D::sphericalVec3D(double r, double theta, double phi){ //construct by cartesian coordinate
    return Vector3D(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
}



//member functions

//scalar product between two vectors
double Vector3D::scalarProduct(const Vector3D& vector2) const{
    return x_ * vector2.x() + y_ * vector2.y() + z_ * vector2.z();
}

//magnitude of a vector
double Vector3D::magnitude() const{
    return sqrt( x_*x_ + y_*y_ + z_*z_);
} 


//Overloads

//sum +
Vector3D Vector3D::operator+( const Vector3D& vec2 ) const {
    double x = x_+vec2.x();
    double y = y_+vec2.y();
    double z = z_+vec2.z();
    return Vector3D::cartesianVec3D(x, y, z);
}

//difference -
Vector3D Vector3D::operator-( const Vector3D& vec2 ) const {
    double x = x_-vec2.x();
    double y = y_-vec2.y();
    double z = z_-vec2.z();
    return Vector3D::cartesianVec3D(x, y, z);
}

//
Vector3D Vector3D::operator*( const double& scalar ) const{
    return Vector3D::cartesianVec3D(x_*scalar, y_*scalar, z_*scalar);
}



//utility func
void Vector3D::print() const {
  cout << "x: " << x_
       << " y: " << y_
       << " z: " << z_ << endl;
}



//extra functions

double angle(const Vector3D& vec1, const Vector3D& vec2){
    double scalarProd = vec1.scalarProduct(vec2); //scalar product between vec1 and vec2
    double r1 = vec1.magnitude(); //r of vec1 and vec2
    double r2 = vec2.magnitude();
    return acos(scalarProd / (r1*r2) ); //invert expression of scalar product for angle
}

double toDeg(double rad){
    return rad*180.0*invPi;
}


//global overloads

Vector3D operator*(const double& scalar, const Vector3D& vec){
    
    return Vector3D::cartesianVec3D(vec.x()*scalar, vec.y()*scalar, vec.z()*scalar);
}