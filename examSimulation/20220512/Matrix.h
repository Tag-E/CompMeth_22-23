
//Emilio Taggi 1910388
//Matrix.h
#ifndef Matrix_h
#define Matrix_h





//classe che implementa una matrice
class Matrix{
    public:

    //CONSTRUCTORS:
    
    //default constructor
    Matrix(); 
    //copy constructor
    Matrix(const Matrix& sourceMatrix); 
    //random square matrix constructor
    Matrix(int Nrows); 
    //random rectangular matrix constructor
    Matrix(int Nrows, int Ncols); 
    //diagonal matrix from a given vector
    Matrix(int Nrows, double* v);
    //matrix given dimension and entries
    Matrix(int Nrows,int Ncols, double* entries);

    //DESTRUCTOR:
    ~Matrix();


    //SETTERS:

    //set number of rows
    void setNrows(int Nrows);
    //set number of columns
    void setNcols(int Ncols);
    //set entries of matrices
    void setels(double *els);

    //SPECIFIC SETTERS:

    //set i-th row
    void set_ithRow(int i,double *row_entries);
    //set number of columns
    void set_jthCol(int j,double *col_entries);
    //set specific entry of matrices
    void set_ijEle(int i, int j, double entry);



    //GETTERS:

    //return number of rows 
    double Nrows() const {return Nrows_; }
    //return number of columns
    double Ncols() const {return Ncols_; }
    double *els() const {return els_;}


    //SPECIFIC SETTERS:

    //return the i-th row
    double *ithRow(int i);
    //return the j-th col
    double *jthCol(int j);
    //return the i,j element
    double ij_ele(int i,int j) const {return els_[i+Nrows_*j]; }


    //ALGEBRA METHODS:

    //swap rows
    void swapRows(int row1,int row2);
    //swap cols
    void swapCols(int col1,int col2);
    //return the transposed  matrix
    Matrix transposed();


    //OVERLOADS:

    //sum +
    Matrix operator+( const Matrix& mat2 ) const;
    //diff -
    Matrix operator-( const Matrix& mat2 ) const;
    //matrices multiplication *
    Matrix operator*( const Matrix& mat2 ) const;


    //UTILITY METHODS:

    //print to scrren the matrix
    void print(int precision=3) const;

    private:
    int Nrows_,Ncols_; //number of rows and columns
    double *els_; //2d array with matrix elements inside

    void allocMat(); //method to alloc the needed space for the matrix
};

#endif