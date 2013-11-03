/*
* Copyright S. V. Paulauskas 2012
* stanpaulauskas@gmail.com
* Distributed under GNU General Public Licence v3
*/

/*! \file Variable.hpp
 *  \brief A class for variables in equations. 
 *  \author S. V. Paulauskas
 *  \date 09 November 2012
 */
#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__
#include <string>

class Variable {
public:
    Variable(){};
    Variable(const double &value, const double &error, 
             const std::string &units) {
        value_ = value;
        error_ = error;
        units_ = units;
    };
    ~Variable(){};

    void SetValue(const double &a) {value_ = a;};
    void SetError(const double &a) {error_ = a;};
    void SetUnits(const std::string &a) {units_ = a;};
    

    double GetValue(void) const {return(value_);};
    double GetError(void) const {return(error_);};
    std::string GetUnits(void) const {return(units_);};
private:
    double value_, error_;
    std::string units_;
}; //class Variable
#endif //__VARIABLE_HPP__
