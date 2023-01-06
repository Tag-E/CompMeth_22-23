//Vector3D.h
#ifndef Vector3D_h
#define Vector3D_h


//classe che implementa un vettore nello spazio tridimensionale
class Vector3D {
    public:
    Vector3D(); //default constructor
    static Vector3D cartesianVec3D(double x, double y, double z); //construct by cartesian coordinate
    static Vector3D sphericalVec3D(double r, double theta, double phi); //construct by spherical coordinate
    Vector3D(const Vector3D& sourceVec); //copy constructor

    //getters:
    double x() const {return x_; }
    double y() const {return y_; }
    double z() const {return z_; }

    //setters
    void setx(double x) { x_ = x;} //set value of x
    void sety(double y) { y_ = y;} //set value of y
    void setz(double z) { z_ = z;} //set value of z

    //functions
    double scalarProduct(const Vector3D& vector2) const; //scalar product between two vectors
    Vector3D vectorProduct(const Vector3D& vec2) const; //vector product between two vectors

    double magnitude() const; //magnitude of a vector
    double theta() const; //theta of the vector
    double phi() const; //phi of the vector

    //overloads
    Vector3D operator+( const Vector3D& vec2 ) const;  //sum of Vector3D
    Vector3D operator-( const Vector3D& vec2 ) const;  //difference of Vector3D
    Vector3D operator*( const double& scalar ) const;  //multiplication by scalar
    Vector3D operator/( const double& scalar ) const;  //division by scalar
    const Vector3D& operator+=(const Vector3D& sourceVec); //increment of Vector3D
    const Vector3D& operator-=(const Vector3D& sourceVec); //decrement of Vector3D
    const Vector3D& operator=(const Vector3D& sourceVec); //assignation of Vector3D

    //utility functions
    void print() const; //flash info to screen

    //friend methods
    friend Vector3D operator*(const double& scalar, const Vector3D& vec);//multiplication scalar times a Vector3D

    private:
    double x_; //coordinates of a point in space
    double y_;
    double z_;

    //constructor by cartesian coordinate
    Vector3D(double x, double y, double z);// construct the Vector3D given x,y,z
};

//extra functions

double angle(const Vector3D& vec1, const Vector3D& vec2);//function to compute angle between two vectors

double toDeg(double rad); //radians to degrees conversion

//global Overloads

Vector3D operator*(const double& scalar, const Vector3D& vec);//multiplication scalar times a Vector3D

#endif