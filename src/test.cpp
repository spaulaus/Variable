/** \file test.cpp
 * \brief A sample program to ensure that the Variable class is performing 
 *    properly.
 * \author S. V. Paulauskas
 * \date 11 November 2013
 */
#include <iostream>

#include "Variable.hpp"

using namespace std;

int main () {
    Variable var  = Variable(123.45, 0.6789, "keV/MeV");
    Variable var1 = Variable(123.45, 0.0987, "keV/MeV");
    Variable var2 = Variable(123.45, 0.6789, "MeV");
    Variable var3 = Variable(123.45, 3465.84, "keV/MeV");

    
    cout << "The Current information for var: " << var.GetValue() 
              << " +- " << var.GetError() 
              <<  " " << var.GetUnits() << endl;

    var.SetValue(987.65);
    var.SetUnits("hbar/c/G");

    cout << "The Updated information for var: " << var.GetValue() 
              << " +- " << var.GetError() 
              <<  " " << var.GetUnits() << endl;

    bool temp =  var1 == var2;
    cout << endl << "We are now going to try to compare things. " << endl
         << "Does var1 = " << var1.Output() << " compare equal to var2 = " 
         << var2.Output() << "?!?!" << endl << "Answer: " << temp << endl; 

    bool temp1 = var1 == var3;
    cout << endl
         << "Does var1 = " << var1.Output() << " compare equal to var3 = " 
         << var3.Output() << "?!?!" << endl << "Answer: " << temp1 << endl; 
}
