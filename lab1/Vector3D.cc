#include "Vector3D.h"
#include <iostream>
#include <cmath>

double pi = M_PI;       //I rename pi of cmath library
double invPi = 1.0/pi ; //useful to avoid division

using namespace std;

//constructor definition

//constructor for default inizialization (all 0s) 
Vector3D::Vector3D(){ 
    x_ = 0.0;
    y_ = 0.0;
    z_ = 0.0;
}

//private constructor
Vector3D::Vector3D(double x, double y, double z){ 
    x_ = x;
    y_ = y;
    z_ = z;
}

//copy constructor
Vector3D::Vector3D(const Vector3D& sourceVec){ 
    x_ = sourceVec.x_;
    y_ = sourceVec.y_;
    z_ = sourceVec.z_;
} 

//construct by cartesian coordinate
Vector3D Vector3D::cartesianVec3D(double x, double y, double z){ 
    return Vector3D(x,y,z);
}

//construct by cartesian coordinate
Vector3D Vector3D::sphericalVec3D(double r, double theta, double phi){ 
    return Vector3D(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
}



//member functions

//scalar product between two vectors
double Vector3D::scalarProduct(const Vector3D& vector2) const{
    return x_ * vector2.x() + y_ * vector2.y() + z_ * vector2.z();
}

//vector product between two vectors
Vector3D Vector3D::vectorProduct(const Vector3D& vec2) const{
    double x = y_ * vec2.z() - z_ * vec2.y();
    double y = z_ * vec2.x() - x_ * vec2.z();
    double z = x_ * vec2.y() - y_ * vec2.x();
    return Vector3D::cartesianVec3D(x, y, z);
}

//magnitude of a vector
double Vector3D::magnitude() const{
    return sqrt( x_*x_ + y_*y_ + z_*z_);
} 

//theta of a vector
double Vector3D::theta() const{
    return acos( z_ / sqrt( x_*x_ + y_*y_ + z_*z_) );
} 

//phi of a vector
double Vector3D::phi() const{
    double phi = 0.0; //default variable of return
    
    //expression of phy depends on which quadrant the vector is:
    if(x_>0.){
        phi = atan(y_/x_);
    }
    else if(x_<0.){
        if(y_<0.){
            phi = atan(y_/x_) - pi;
        }
        else phi = atan(y_/x_) + pi;
    }
    else{ //x=0.0 case
        if(y_>0.0){
            phi = 0.5*pi;
        }
        else if(y_<0.0){
            phi = -0.5*pi;
        }
    }

    /*for x=0,y=0 phi is undefined
      here we set it to be 0 by default*/

    return phi;
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

//multiplication by a scalar (vector times scalar)
Vector3D Vector3D::operator*( const double& scalar ) const{
    return Vector3D::cartesianVec3D(x_*scalar, y_*scalar, z_*scalar);
}

//division by a scalar
Vector3D Vector3D::operator/( const double& scalar ) const{
    /*
     ...
     missing a division by 0 handler
     ...
    */
    return Vector3D::cartesianVec3D(x_/scalar, y_/scalar, z_/scalar);
}

//plus equal += (increment of a Vector3D by another Vector3D)
const Vector3D& Vector3D::operator+=(const Vector3D& sourceVec) {
  x_ += sourceVec.x_;
  y_ += sourceVec.y_;
  z_ += sourceVec.z_;
  return *this;
}

//minus equal -= (decrement of a Vector3D by another Vector3D)
const Vector3D& Vector3D::operator-=(const Vector3D& sourceVec) {
  x_ -= sourceVec.x_;
  y_ -= sourceVec.y_;
  z_ -= sourceVec.z_;
  return *this;
}

//equal sign =
const Vector3D& Vector3D::operator=(const Vector3D& sourceVec) {
  x_ = sourceVec.x_;
  y_ = sourceVec.y_;
  z_ = sourceVec.z_;
  return *this;
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

//multiplication by a scalar (scalar times vector)
Vector3D operator*(const double& scalar, const Vector3D& vec){ //(friend method)  
    return Vector3D::cartesianVec3D(vec.x_*scalar, vec.y_*scalar, vec.z_*scalar);
}