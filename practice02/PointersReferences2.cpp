#include <iostream>
using namespace std;

void print_info(int var, string var_name){
   cout << "value of " << var_name << ": " << var
        << ", address of " << var_name << ", " 
        << "&" << var_name << ": " << &var << endl;
}
   
int main() {

   int a = 1;
   print_info(a, "a");

   int* b = &a;
   *b = 3;
   print_info(a, "a");

   int& x = a;
   x = 45;
   print_info(a, "a");

   return 0;
}
