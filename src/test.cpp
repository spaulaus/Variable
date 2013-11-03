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
    Variable var;
    var=Variable(123.45, 0.6789, "keV/MeV");

    
    std::cout << "The Current information for var: " << var.GetValue() 
              << " +- " << var.GetError() 
              <<  " " << var.GetUnits() << endl;

    var.SetValue(987.65);
    var.SetUnits("hbar/c/G");

    std::cout << "The Updated information for var: " << var.GetValue() 
              << " +- " << var.GetError() 
              <<  " " << var.GetUnits() << endl;
}
