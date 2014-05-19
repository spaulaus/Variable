/***************************************************************************
  *  Copyright S. V. Paulauskas 2014                                       *
  *                                                                        *
  *  This program is free software: you can redistribute it and/or modify  *
  *  it under the terms of the GNU General Public License as published by  *
  *  the Free Software Foundation, version 3.0 License.                    *
  *                                                                        *
  *  This program is distributed in the hope that it will be useful,       *
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
  *  GNU General Public License for more details.                          *
  *                                                                        *
  *  You should have received a copy of the GNU General Public License     *
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
  **************************************************************************
*/

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
    Variable var(123.45, 0.6789, "keV/MeV");
    Variable var1(123.45, 0.0987, "keV/MeV");
    Variable var2(123.45, 0.6789, "MeV");
    Variable var3(123.45, 3465.84, "keV/MeV");
    
    cout << "The Current information for var: " << var.Output() << endl;

    var.SetValue(987.65);
    var.SetUnits("hbar/c/G");

    cout << "The Updated information for var: " << var.Output() << endl;

    cout << endl << "We are now going to try to compare things. " << endl;
    bool temp =  var1 == var2;
    cout << "Does var1 = " << var1.Output() << " compare equal to var2 = " 
         << var2.Output() << "?!?!" << endl << "Answer: " << temp << endl; 

    bool temp1 = var1 == var3;
    cout << endl
         << "Does var1 = " << var1.Output() << " compare equal to var3 = " 
         << var3.Output() << "?!?!" << endl << "Answer: " << temp1 << endl;

    cout << "We are going to do some maths now." << endl;
    Variable add = var1 + var2;
    cout << add.Output() << endl;
    
    Variable add1 = var1 + var3;
    cout << add1.Output() << endl;
    
    Variable sub = var1 - var2;
    cout << sub.Output() << endl;
    
    Variable sub1 = var1 - var3;
    cout << sub1.Output() << endl;

    Variable mult = var1 * var2;
    cout << mult.Output() << endl;
    
    Variable mult1 = var1 * var3;
    cout << mult1.Output() << endl;

    Variable div = var1 / var2;
    cout << div.Output() << endl;

    Variable div1 = var1 / var3;
    cout << div1.Output() << endl;
}
