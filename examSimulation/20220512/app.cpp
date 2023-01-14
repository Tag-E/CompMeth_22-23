//Emilio Taggi 1910388
//app.cpp
//compiling with g++ -o app app.cpp Matrix.cc `$ROOTSYS/bin/root-config --libs --cflags` -Wall
#include <iostream>
#include <iomanip>

#include "Matrix.h"

int main(){

    
    Matrix A = Matrix();
    A.print();

    Matrix B = Matrix(5);
    B.print();

    Matrix C = Matrix(B);
    C.print(5);

    std::cout << "D" << std::endl;
    Matrix D = Matrix(3,7);
    D.print(3);

    double entries[2*3] = {1,2,3,4,5,6};
    //double **e = entries;
    Matrix E = Matrix(2,3,entries);
    std::cout << "E" << std::endl;
    E.print();
    double new_entries[2*3] = {11,21,31,41,51,61};
    E.setels(new_entries);
    E.print();
    double col[2] ={18,54};
    double row[3] = {90,90,90};
    E.set_ithRow(0,row);
    E.print();
    E.set_jthCol(1,col);
    E.print();
    E.set_ijEle(0,0,500);
    E.print();

    E.setNrows(4);
    E.setNcols(7);
    std::cout << "E new" << std::endl;
    E.print();

    double *myCol;
    myCol = E.jthCol(2);
    E.set_jthCol(0,myCol);
    E.print();
    double *myRow;
    myRow = E.ithRow(0);
    E.set_ithRow(3,myRow);
    E.print();
    E.swapRows(0,2);
    E.print();
    E.swapCols(0,3);
    E.print();

    Matrix F = E.transposed();
    F.print();

    (F+F).print();
    (F-F).print();
    (E*F).print();

    

    return 0;
};
