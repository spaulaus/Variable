///@file Variable.hpp
///@brief A class that handles calculations of physically interesting numbers.
///@author S. V. Paulauskas
///@date November 09, 2013
/// @copyright Copyright (c) 2013-2017 S. V. Paulauskas.
/// @copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__
#include <iostream>
#include <string>
#include <sstream>

#include <cmath>

///Defines the Variable class. A physical quantity always has a value, error, and units. This class provides a way to
/// organize that information, and propagates the errors as mathematical operations are performed on the variables.
/// At the moment we only accept quantities that have symmetric error bars.
class Variable {
public:
    /// Default constructor
    Variable(){};

    /// Constructor that sets all the values.
    /// @param[in] value : The value that the variable has
    /// @param[in] error : The error on the units. We only accept symmetric error bars.
    /// @param[in] units : The units on the variable.
    Variable(const double &value, const double &error,
             const std::string &units) : value_(value), error_(error), units_(units) { };

    /// Default Destructor
    ~Variable(){};

    /// The Equality operator
    /// @param[in] rhs : The variable that we are going to be comparing against
    /// @returns True if the variables are equal
    inline bool operator== (const Variable &rhs) const {
        if(UnitCheck(this->GetUnits(), rhs.GetUnits()))
            return this->GetValue() == rhs.GetValue();
        return false;
    }; const

    /// The Not Equality operator, just the negative of the equality operator
    /// @param[in] rhs : The Variable that we are going to be comparing with.
    /// @returns True if the variables are not equal
    inline bool operator!= (const Variable &rhs) const { return !(*this==rhs); }

    /// The Greater than operator
    /// @param[in] rhs : The variable that we want to know if we're greater than.
    /// @returns True if we were greater than the RHS
    inline bool operator> (const Variable &rhs) const {
        if(UnitCheck(this->GetUnits(), rhs.GetUnits()))
            return this->GetValue() > rhs.GetValue();
        return false;
    }; const

    /// The less than operator
    /// @param[in] rhs : The variable that we want to check if we're less than
    /// @returns True if we were less than the RHS
    inline bool operator< (const Variable &rhs) const { return !(*this > rhs); }

    /// The Greater than or equal operator
    /// @param[in] rhs : The variable that we want to know if we're greater than or equal to
    /// @returns True if we were greater than the RHS.
    inline bool operator>= (const Variable &rhs) const {
        if(UnitCheck(this->GetUnits(), rhs.GetUnits()))
            return this->GetValue() >= rhs.GetValue();
        return false;
    }; const

    /// The less than or equal to operator
    /// @param[in] rhs : The variable that we want to check if we're less than
    /// @returns True if we were less than the RHS
    inline bool operator<= (const Variable &rhs) const { return !(*this >= rhs); }

    /// The addition operator. We can only add together variables that have matching units. Otherwise our
    /// calculations are not physically meaningful
    /// @param[in] rhs : The right hand side of our addition
    /// @throws invalid_argument if we did not have matching units
    /// @returns The sum of the two variables, along with the error propagated appropriately.
    inline Variable operator+(const Variable&rhs) const {
        if(!UnitCheck(this->GetUnits(), rhs.GetUnits()))
            return(Variable(0.0,0.0,""));
        return Variable(this->GetValue() + rhs.GetValue(),
                        CalculateAdditionSubtractionError(this->GetError(),rhs.GetError()), this->GetUnits());
    }

    /// The subtraction operator. We can only subtract variables that have matching units. Otherwise our
    /// calculations are not physically meaningful
    /// @param[in] rhs : The right hand side of our subtraction
    /// @throws invalid_argument if we did not have matching units
    /// @returns The sum of the two variables, along with the error propagated appropriately.
    inline Variable operator-(const Variable&rhs) const {
        if(!UnitCheck(this->GetUnits(), rhs.GetUnits()))
            return(Variable(0.0,0.0,""));
        double val = this->GetValue() - rhs.GetValue();
        double err = CalculateAdditionSubtractionError(this->GetError(),rhs.GetError());
        std::string unit = this->GetUnits();
        return(Variable(val,err,unit));
    }

    /// The multiplication operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product
    /// @returns The product of the two variables, along with the error propagated appropriately.
    inline Variable operator*(const Variable&rhs) const {
        double val = this->GetValue() * rhs.GetValue();
        double err = CalculateMultiplicationDivisonError(val,*this,rhs);
        std::stringstream ss;
        ss << this->GetUnits() << "*" << rhs.GetUnits();
        return(Variable(val,err,ss.str()));
    }

    /// The division operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our division
    /// @returns The quotient of the two variables, along with the error propagated appropriately.
    inline Variable operator/(const Variable&v) const {
        double val = this->GetValue() / v.GetValue();
        double err = CalculateMultiplicationDivisonError(val,*this,v);
        std::stringstream ss;
        ss << this->GetUnits() << "/" << v.GetUnits();
        std::string unit = this->GetUnits();
        return(Variable(val,err,ss.str()));
    };

    /// The bitwise left shift operator, this operator is used so that we can output the variable to output streams
    /// like cout.
    /// @param[in] out : The output file stream that we want to use
    /// @param[in] v : The variable that we want to output to the stream.
    /// @returns A reference to the stream that we passed into the method.
    friend std::ostream& operator<<(std::ostream& out, const Variable &v) {
        out << std::to_string(v.GetValue()) << " +- " << std::to_string(v.GetError()) <<  " " << v.GetUnits() << " ";
        return out;
    }

    /// Sets the value of the variable
    /// @param[in] a : The value to set
    inline void SetValue(const double &a) {value_ = a;}

    /// Sets the error on the variable
    /// @param[in] a : The value to set
    inline void SetError(const double &a) {error_ = a;}

    /// Sets the units on the variable
    /// @param[in] a : The value to set
    inline void SetUnits(const std::string &a) {units_ = a;}

    /// Get the value of the Variable
    /// @returns the value
    inline double GetValue(void) const {return value_; }

    /// Get the value of the error
    /// @returns the error bars
    inline double GetError(void) const {return error_;}

    /// Get the value of the Variable
    /// @returns the value
    inline std::string GetUnits(void) const {return units_;}

private:
    double value_; ///< The value of the Variable
    double error_; ///< The error on the Variable
    std::string units_; ///< The units on the Variable

    /// Provides a check on the units for situations where we are adding or subtracting
    ///@param[in] u1 : The units on the LHS
    ///@param[in] u2 : The units on the RHS
    bool UnitCheck(const std::string &lhs, const std::string &rhs) const {
        if(lhs == rhs)
            return true;
        // std::cerr << "WARNING!!!!! You are trying to operate on "
        //           << "two variables that have different units!!!"
        //           << std::endl << u1 << " != " << u2 << std::endl;
        return false;
    };

    /// Propagates the error on addition and subtraction operations.
    /// @param[in] lhs : The error bar on the left hand side
    /// @param[in] rhs : The error bar on the right hand side
    /// @returns the propagated error bar on the variable
    double CalculateAdditionSubtractionError(const double &lhs, const double &rhs) const {
        return sqrt(lhs*lhs + rhs*rhs);
    };

    /// Propagates the error on addition and subtraction operations.
    /// @param[in] val : The value of the original multiplication or division operation. This needs multiplied in to
    /// properly propagate the error.
    /// @param[in] lhs : The error bar on the left hand side
    /// @param[in] rhs : The error bar on the right hand side
    /// @returns the propagated error bar on the variable
    double CalculateMultiplicationDivisonError(const double &val, const Variable &lhs, const Variable &rhs) const {
        return val* sqrt(v1.GetError()*v1.GetError()/v1.GetValue()/v1.GetValue()
                         + v2.GetError()*v2.GetError()/v2.GetValue()/v2.GetValue());
    }
}; //class Variable
#endif //__VARIABLE_HPP__
