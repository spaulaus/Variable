///@file test.cpp
///@brief A sample program to ensure that the Variable class is performing properly.
///@author S. V. Paulauskas
///@date November 11, 2013
/// @copyright Copyright (c) 2017 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#include <iostream>

#include "Variable.hpp"

using namespace std;

int main () {
    Variable var(123.45, 0.6789, "keV/MeV");
    Variable var1(123.45, 0.0987, "keV/MeV");
    Variable var2(123.45, 0.6789, "MeV");
    Variable var3(123.45, 3465.84, "keV/MeV");
    
    cout << "The Current information for var: " << var << endl;

    var.SetValue(987.65);
    var.SetUnits("hbar/c/G");

    cout << "The Updated information for var: " << var << endl;

    cout << endl << "We are now going to try to compare things. " << endl;
    bool temp =  var1 == var2;
    cout << "Does var1 = " << var1 << " compare equal to var2 = " 
         << var2 << "?!?!" << endl << "Answer: " << temp << endl; 

    bool temp1 = var1 == var3;
    cout << endl
         << "Does var1 = " << var1 << " compare equal to var3 = " 
         << var3 << "?!?!" << endl << "Answer: " << temp1 << endl;

    cout << "We are going to do some maths now." << endl;
    Variable add = var1 + var2;
    cout << add << endl;
    
    Variable add1 = var1 + var3;
    cout << add1 << endl;
    
    Variable sub = var1 - var2;
    cout << sub << endl;
    
    Variable sub1 = var1 - var3;
    cout << sub1 << endl;

    Variable mult = var1 * var2;
    cout << mult << endl;
    
    Variable mult1 = var1 * var3;
    cout << mult1 << endl;

    Variable div = var1 / var2;
    cout << div << endl;

    Variable div1 = var1 / var3;
    cout << div1 << endl;
}
