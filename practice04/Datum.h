// Datum.h
// header file of the Datum class

#ifndef Datum_h
#define Datum_h

class Datum {
  public:
    // constructor
    Datum(double val, double error);

    // getters
    double value();
    double error();

    // setters
    void setValue(double value);
    void setError(double error);

    void print();

  private:
    double value_;
    double error_;
};

#endif
