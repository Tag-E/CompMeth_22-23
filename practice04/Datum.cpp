// Datum.cpp
// example of an application of the Datum class

#include "Datum.h" 
#include "Datum.h" /*do not complain about this since i have
		     added the #ifndef - #define - #endif
		     syntax in the header file
		    */

int main() {

  Datum d1(23.4,7.5);
  d1.print();

  d1.setValue( 8.563 );
  d1.setError( 0.45 );
  d1.print();

  return 0;
}
