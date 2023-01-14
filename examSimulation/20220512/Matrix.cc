//Emilio Taggi 1910388
//Matric.cc

#include <iostream>
#include <iomanip>
#include <cmath>

#include "TRandom3.h" //for the random generator


using std::cout;
using std::endl;



#include "Matrix.h"

//CONSTRUCTORS:

//default constructor(creates a 3x3 matrices with 1s inside)
Matrix::Matrix(){

    Nrows_ = 3; //to default I set the dimension to be 3x3
    Ncols_ = 3;

    allocMat(); //I take the needed memory


    for (int i = 0; i < Nrows_; ++i) {
        for (int j = 0; j < Ncols_; ++j) {
            els_[i+Nrows_*j] = 1.0; 
        }
    }


}

//Copy constructor that copies entries from another matrix
Matrix::Matrix(const Matrix& sourceMatrix){
    
    Nrows_ = sourceMatrix.Nrows_;
    Ncols_ = sourceMatrix.Ncols_;

    allocMat(); //I take the needed memory

    for (int i = 0; i < Nrows_; ++i) {
        for (int j = 0; j < Ncols_; ++j) {
            els_[i+Nrows_*j] = sourceMatrix.els_[i+Nrows_*j];
        }
    }
} 

//constructor for random square matrix
Matrix::Matrix(int Nrows){

    Nrows_ = Nrows;
    Ncols_ = Nrows;

    allocMat(); //I take the needed memory

    //I set up a random generator
    TRandom3*  gen = new TRandom3();
    gen->SetSeed(0);

    for (int i = 0; i < Nrows_; ++i) {
        for (int j = 0; j < Ncols_; ++j) {
            els_[i+Nrows_*j] = gen->Uniform(1.0); //I fill the matrix with random double between 0 and 1
        }
    }

    //remove memory allocated for the generator
    delete gen;

}

//constructor for random rectangular matrix
Matrix::Matrix(int Nrows,int Ncols){

    Nrows_ = Nrows;
    Ncols_ = Ncols;

    allocMat(); //I take the needed memory

    //I set up a random generator
    TRandom3*  gen = new TRandom3();
    gen->SetSeed(0);

    for (int i = 0; i < Nrows_; ++i) {
        for (int j = 0; j < Ncols_; ++j) {
            els_[i+Nrows_*j] = gen->Uniform(1.0); //I fill the matrix with random double between 0 and 1
        }
    }

    //remove memory allocated for the generator
    delete gen;

}

//constructor from dimension and vector to put on diagonal
Matrix::Matrix(int Nrows, double* v){
    Nrows_=Nrows;
    Ncols_=Nrows;

    allocMat(); //I take the needed memory

    for (int i = 0; i < Nrows_; ++i) {
        els_[i+Nrows_*i] = v[i]; //i put the input vector on the diagonal
    }    
}

//constructor from dimensions and entries
Matrix::Matrix(int Nrows, int Ncols, double* entries){

    Nrows_=Nrows;
    Ncols_=Ncols;

    allocMat(); //I take the needed memory

    for (int i = 0; i < Nrows_; ++i) {
        for (int j = 0; j < Ncols_; ++j) {
            els_[i+Nrows_*j] = entries[i + Nrows*j]; //I fill the matrix with the given entries
        }
    }   
}


//DESTRUCTOR
Matrix::~Matrix()
{
    delete[] els_; //i delete the array i allocated in allocMat
}


//SETTERS:

//set number of rows
void Matrix::setNrows(int Nrows){

    

    double *new_els = new double[Nrows*Ncols_]; //create a new matrix with the new number of rows

    for (int i = 0; i < Nrows_; ++i) {                //..up to the old number of rows
        for (int j = 0; j < Ncols_; ++j) {
            new_els[i+Nrows*j] = els_[i + Nrows_*j]; //..I fill it with old entrieds
        }
    }

    for (int i = Nrows_; i < Nrows; ++i) {                //and add a padding
        for (int j = 0; j < Ncols_; ++j) {
            new_els[i+Nrows*j] = 0.0; //..with zeros
        }
    }

    Nrows_=Nrows; //then I change the number of rows

    delete els_; // delete the old entries
    els_ = new_els; //and take the new ones

}

//set number of columns
void Matrix::setNcols(int Ncols){

    

    double *new_els = new double[Nrows_*Ncols]; //create a new matrix with the new number of rows

    for (int i = 0; i < Nrows_; ++i) {                
        for (int j = 0; j < Ncols_; ++j) {           //..up to the old number of rows
            new_els[i+Nrows_*j] = els_[i + Nrows_*j]; //..I fill it with old entrieds
        }
        for (int j = Ncols_; j < Ncols; ++j) {        //and add apadding
            new_els[i+Nrows_*j] = 0.0;                //..with zeros
        }
    }

    Ncols_=Ncols; //then I change the number of cols

    delete els_; // delete the old entries
    els_ = new_els; //and take the new ones

}

//set entries of the matrix
void Matrix::setels(double *els){

    for (int i = 0; i < Nrows_; ++i) {     //loop over the entries 
        for (int j = 0; j < Ncols_; ++j) {
            els_[i+Nrows_*j] = els[i + Nrows_*j]; //change the old with the new
        }
    }

}


//SPECIFIC SETTERS:

//set i-th row
void Matrix::set_ithRow(int i,double *row_entries){
    for (int j = 0; j < Ncols_; ++j) {
        els_[i+Nrows_*j] = row_entries[j]; //change the old with the new
    }
}

//set j-th row
void Matrix::set_jthCol(int j,double *col_entries){
    for (int i = 0; i < Nrows_; ++i) {
        els_[i+Nrows_*j] = col_entries[i]; //change the old with the new
    }
}

//set entry i,j
void Matrix::set_ijEle(int i, int j, double entry){
    els_[i+Nrows_*j] = entry;
}


//SPECIFIC GETTERS

//get ith row
double *Matrix::ithRow(int i){
    double *i_row = new double[Ncols_]; //allocate memory for new array
    for (int j = 0; j < Ncols_; ++j) {
        i_row[j] = els_[i+Nrows_*j]; //fill it with the row
    }
    return i_row; //send it back
}
//get jth col
double *Matrix::jthCol(int j){
    double *j_col = new double[Nrows_]; //allocate memory for new array
    for (int i = 0; i < Nrows_; ++i) {
        j_col[i] = els_[i+Nrows_*j]; //fill it
    }
    return j_col;
}



//ALGEBRA METHODS:

//swap two rows
void Matrix::swapRows(int row1,int row2){
    double temp; //temporary double to store row1 elements before changing them

    //loop over the entries of the row
    for (int j = 0; j < Ncols_; ++j) {
        temp = els_[row1+Nrows_*j]; //store row1 element
        els_[row1+Nrows_*j] = els_[row2+Nrows_*j]; //change it with a row 2 element
        els_[row2+Nrows_*j] = temp; //change row 2 element
    }
}

//swap two cols
void Matrix::swapCols(int col1,int col2){
    double temp; //temporary double to store col1 elements before changing them

    //loop over the entries of the col
    for (int i = 0; i < Nrows_; ++i) {
        temp = els_[i+Nrows_*col1]; //store col1 element
        els_[i+Nrows_*col1] = els_[i+Nrows_*col2]; //change it with a col2 element
        els_[i+Nrows_*col2] = temp; //change col2 element
    }
}

//return the transposed  matrix
Matrix Matrix::transposed(){
    Matrix tran = Matrix(Ncols_,Nrows_);
    for (int i = 0; i < Nrows_; ++i) {     //loop over the entries 
        for (int j = 0; j < Ncols_; ++j) {
            tran.els_[j+Ncols_*i] = els_[i + Nrows_*j]; //transposition
        }
    }
    return tran;
}




//UTILITY METHODS:

//print the matrix to screen
void Matrix::print(int precision) const{

    std::cout << std::fixed;
    std::cout << std::setprecision(precision); //to see just 3 digits in prints
    std::cout << "\n" << std::endl;

    for (int i = 0; i < Nrows_; ++i) { //rows loop

        cout << "|" << " ";

        for (int j = 0; j < Ncols_; ++j) { //column loop
            cout << els_[i+Nrows_*j] << " ";
        }

        cout << "|" << endl;
    }
}



//OVERLOADS:

//sum +
Matrix Matrix::operator+( const Matrix& mat2 ) const {
    Matrix sum = Matrix(Nrows_,Ncols_);
    for (int i = 0; i < Nrows_; ++i) {     //loop over the entries 
        for (int j = 0; j < Ncols_; ++j) {
            sum.els_[i+Nrows_*j] = els_[i + Nrows_*j] + mat2.els_[i + Nrows_*j]; //sum
        }
    }
    return sum;
}

//difference -
Matrix Matrix::operator-( const Matrix& mat2 ) const {
    Matrix diff = Matrix(Nrows_,Ncols_);
    for (int i = 0; i < Nrows_; ++i) {     //loop over the entries 
        for (int j = 0; j < Ncols_; ++j) {
            diff.els_[i+Nrows_*j] = els_[i + Nrows_*j] - mat2.els_[i + Nrows_*j]; //sum
        }
    }
    return diff;
}

//matrices multiplication *
Matrix Matrix::operator*( const Matrix& mat2 ) const{

    Matrix mult = Matrix(Nrows_,mat2.Ncols_); //dimension for new matrix

    double row_col_sum;

    for (int i = 0; i < Nrows_; ++i) {     //loop over the entries of new matrices
        for (int j = 0; j < mat2.Ncols_; ++j) {

            row_col_sum=0.0; //put to 0 the new entry

            for(int k=0; k<Ncols_; ++k){
                row_col_sum += els_[i+Nrows_*k] * mat2.els_[k+mat2.Nrows_*j]; //row column product
            }

            mult.els_[i+Nrows_*j] = row_col_sum; //set new entry
        }
    }
    return mult;
}




//private method to allocate the needed space for the matrix
void Matrix::allocMat(){
    els_ = new double[Nrows_*Ncols_]; //allocate the space needed for the matrix
}