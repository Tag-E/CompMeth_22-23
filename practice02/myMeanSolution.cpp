#include <iostream>
#include <cmath>

using namespace std;

void computeMean(const double* data, int nData, double& mean, double& stdDev){
  // Two variables passed by reference to void function: not great, but harmles
  double mean2 = 0.;
  double norm = 1.0;
  mean=0.;
  norm = 1.0/nData; //should check if nData != 0
  for(int i=0;i<nData;++i){
    mean += *data;
    mean2 += (*data) * (*data);
    data++;
  }
  mean *= norm; //divide by number of points
  mean2 *= norm;
  stdDev = sqrt( mean2 - mean*mean ); //stdDev formula
}

double meanWithStdDev(const double* data, int nData, double& stdDev){
  // Error passed by reference to mean function! Ugly and anti-intuitive
  double mean = 0.; //mean i'll return
  double mean2 = 0.; //auxiliary variable
  double norm;
  norm = 1.0/nData; //should check if nData != 0
  for(int i=0;i<nData;++i){
    mean += *data;
    mean2 += (*data) * (*data);
    data++;
  }
  mean *= norm; //divide by number of points
  mean2 *= norm;
  stdDev = sqrt( mean2 - mean*mean ); //stdDev formula
  return mean;
}

double mean(const double* data, int nData){
  // One method to compute only average
  double mean=0.;
  double norm;
  norm = 1.0/nData; //should check if nData != 0
  for(int i=0;i<nData;++i){
    mean += *data;
    data++;
  }
  mean *= norm; //divide by number of points
  return mean;
}

double stdDev(const double* data, int nData){
  // One method to compute standard deviation
  // Use mean() to compute average needed by std deviation
  double my_mean = 0.;
  double mean2 = 0.;
  double norm;
  my_mean = mean(data, nData);
  norm = 1.0/nData; //should check if nData != 0
  for(int i=0;i<nData;++i){
    mean2 += (*data) * (*data);   
    data++;
  }
  /*also possible to use
    stdDev += pow(*data-m,2.);
    --> 
  */
  mean2 *= norm; //divide by number of points
  return sqrt( mean2-my_mean*my_mean );
}

int main(){

  double pressure[] = { 1.2, 0.9, 1.34, 1.67, 0.87, 1.04, 0.76 };
  double mn = 0., std = 0.;

  cout << "mean: " << mn << "\tstdDev: " << std << endl;

  computeMean(pressure,7,mn,std);
  cout << "computeMean executed" << endl;
  cout << "mean: " << mn << "\tstdDev: " << std << endl;


  mn = meanWithStdDev(pressure,7,std);
  cout << "using meanWithStdDev" << endl;
  cout << "mean: " << mn << "\tstdDev: " << std << endl;

  mn = mean(pressure,7);
  std = stdDev(pressure,7);
  cout << "using mean and stdDev" << endl;
  cout << "mean: " << mn << "\tstdDev: " << std << endl;
  
  return 0;
}
