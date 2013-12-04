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
#include <iostream>
#include <string>
#include <sstream>

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

    //Overloading the comparison operators here
    inline bool operator== (const Variable &v) {
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() == v.GetValue());
        else
            return(false);
    };
    inline bool operator!= (const Variable &v){
        return(!(*this==v));
    };
    inline bool operator> (const Variable &v2){
        if(UnitCheck(this->GetUnits(), v2.GetUnits()))
            return(this->GetValue() > v2.GetValue());
        else
            return(false);
    };
    inline bool operator< (const Variable &v){
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() < v.GetValue());
        else
            return(false);
    };
    inline bool operator<= (const Variable &v){
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() <= v.GetValue());
        else
            return(false);
    };
    inline bool operator>= (const Variable &v){
        if(UnitCheck(this->GetUnits(), v.GetUnits()))
            return(this->GetValue() >= v.GetValue());
        else
            return(false);
    };
        
    inline void SetValue(const double &a) {value_ = a;};
    inline void SetError(const double &a) {error_ = a;};
    inline void SetUnits(const std::string &a) {units_ = a;};
    

    inline double GetValue(void) const {return(value_);};
    inline double GetError(void) const {return(error_);};
    inline std::string GetUnits(void) const {return(units_);};

    inline std::string Output(void) const {
        std::stringstream ss;
        ss << value_ << " +- " << error_ << " " << units_; 
        return(ss.str());
    };
private:
    double value_, error_;
    std::string units_;
    
    bool UnitCheck(const std::string &u1, const std::string &u2) {
        if(u1 == u2)
            return(true);
        else {
            std::cerr << "WARNING!!!!! You are trying to compare two variables "
                      << "that have different units!!!" << std::endl
                      << u1 << " != " << u2 << std::endl;
            return(false);
        }
    };
}; //class Variable
#endif //__VARIABLE_HPP__
