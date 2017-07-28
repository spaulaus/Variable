///@file Variable.hpp
///@brief A class that handles calculations of physically interesting numbers.
///@author S. V. Paulauskas
///@date November 09, 2013
///@copyright Copyright (c) 2013-2017 S. V. Paulauskas.
///@copyright All rights reserved. Released under the Creative Commons Attribution-ShareAlike 4.0 International License
#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include <iostream>
#include <stdexcept>
#include <string>

#include <cmath>

///Defines the Variable class. A physical quantity always has a value, error, and units. This class provides a way to
/// organize that information, and propagates the errors as mathematical operations are performed on the variables.
/// At the moment we only accept quantities that have symmetric error bars.
class Variable {
public:
    /// Default constructor
    Variable() {}

    /// Constructor that sets all the values.
    /// @param[in] value : The value that the variable has
    /// @param[in] error : The error on the units. We only accept symmetric error bars.
    /// @param[in] units : The units on the variable.
    Variable(const double &value, const double &error, const std::string &units)
            : value_(value), error_(error), units_(units) {}

    /// Default Destructor
    ~Variable() {}

    /// The Equality operator. To make an accurate comparison we must compare objects with the same units.
    /// @param[in] rhs : The variable that we are going to be comparing against
    /// @returns True if the variables are equal
    inline bool operator==(const Variable &rhs) const {
        if (this->GetUnits() != rhs.GetUnits())
            throw std::invalid_argument("Variable::operator== : Cannot compare objects with different units! We have"
                                        + this->GetUnits() + " and " + rhs.GetUnits());
        return this->GetValue() == rhs.GetValue();
    }

    /// The Not Equality operator, just the negative of the equality operator
    /// @param[in] rhs : The Variable that we are going to be comparing with.
    /// @returns True if the variables are not equal
    inline bool operator!=(const Variable &rhs) const { return !(*this == rhs); }

    /// The Greater than operator. To make an accurate comparison we must compare objects with the same units.
    /// @param[in] rhs : The variable that we want to know if we're greater than.
    /// @returns True if we were greater than the RHS
    inline bool operator>(const Variable &rhs) const {
        if (this->GetUnits() != rhs.GetUnits())
            throw std::invalid_argument("Variable: Cannot compare objects with different units! We have"
                                        + this->GetUnits() + " and " + rhs.GetUnits());
        return this->GetValue() > rhs.GetValue();
    }

    /// The less than operator.
    /// @param[in] rhs : The variable that we want to check if we're less than
    /// @returns True if we were less than the RHS
    inline bool operator<(const Variable &rhs) const { return rhs > *this; }

    /// The Greater than or equal operator.
    /// @param[in] rhs : The variable that we want to know if we're greater than or equal to
    /// @returns True if we were greater than the RHS.
    inline bool operator>=(const Variable &rhs) const { return !(*this < rhs); }

    /// The less than or equal to operator.
    /// @param[in] rhs : The variable that we want to check if we're less than
    /// @returns True if we were less than the RHS
    inline bool operator<=(const Variable &rhs) const { return !(*this > rhs); }

    /// The compound addition operator. We can only add together variables that have matching units. Otherwise our
    /// calculations are not physically meaningful
    /// @param[in] rhs : The right hand side of our addition
    /// @throws invalid_argument if we did not have matching units
    /// @returns The sum of the two variables
    inline Variable &operator+=(const Variable &rhs) {
        if (this->GetUnits() != rhs.GetUnits())
            throw std::invalid_argument("Variable : Cannot add objects with different units! We have "
                                        + this->GetUnits() + " and " + rhs.GetUnits());
        this->SetValue(this->GetValue() + rhs.GetValue());
        this->SetError(CalculateAdditionSubtractionError(this->GetError(), rhs.GetError()));
        return *this;
    }

    /// The addition operator. We can only add together variables that have matching units. Otherwise our
    /// calculations are not physically meaningful
    /// @param[in] rhs : The right hand side of our addition
    /// @throws invalid_argument if we did not have matching units
    /// @returns The sum of the two variables, along with the error propagated appropriately.
    inline Variable operator+(const Variable &rhs) const {
        Variable lhs = *this;
        lhs += rhs;
        return lhs;
    }

    /// The subtraction operator. We can only subtract variables that have matching units. Otherwise our
    /// calculations are not physically meaningful
    /// @param[in] rhs : The right hand side of our subtraction
    /// @throws invalid_argument if we did not have matching units
    /// @returns The difference of the two variables, along with the error propagated appropriately.
    inline Variable &operator-=(const Variable &rhs) {
        if (this->GetUnits() != rhs.GetUnits())
            throw std::invalid_argument("Variable : Cannot subtract objects with different units! We have "
                                        + this->GetUnits() + " and " + rhs.GetUnits());
        this->SetValue(this->GetValue() - rhs.GetValue());
        this->SetError(CalculateAdditionSubtractionError(this->GetError(), rhs.GetError()));
        return *this;
    }

    /// The subtraction operator. We can only subtract variables that have matching units. Otherwise our
    /// calculations are not physically meaningful
    /// @param[in] rhs : The right hand side of our subtraction
    /// @throws invalid_argument if we did not have matching units
    /// @returns The difference of the two variables, along with the error propagated appropriately.
    inline Variable operator-(const Variable &rhs) const {
        Variable lhs = *this;
        lhs -= rhs;
        return lhs;
    }

    /// The compound multiplication operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product
    /// @returns The product of the two variables, along with the error propagated appropriately.
    inline Variable &operator*=(const Variable &rhs) {
        this->SetValue(this->GetValue() * rhs.GetValue());
        this->SetError(CalculateMultiplicationDivisonError(this->GetValue(), *this, rhs));
        this->SetUnits(this->GetUnits() + "*" + rhs.GetUnits());
        return *this;
    }

    /// The multiplication operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product
    /// @returns The product of the two variables, along with the error propagated appropriately.
    inline Variable operator*(const Variable &rhs) const {
        Variable lhs = *this;
        lhs *= rhs;
        return lhs;
    }

    /// The templated compound multiplication operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product, which can be any standard c++ class (int, double, etc.).
    /// @returns The product of the two variables, along with the error propagated appropriately.
    template <class T>
    inline Variable &operator*=(const T &rhs) {
        this->SetValue(this->GetValue() * rhs);
        this->SetError(this->GetError() * rhs);
        return *this;
    }

    /// The templated multiplication operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product, which can be any standard c++ class (int, double, etc.).
    /// @returns The product of the two variables, along with the error propagated appropriately.
    template <class T>
    inline Variable operator*(const T &rhs) const {
        Variable lhs = *this;
        lhs *= rhs;
        return lhs;
    }

    /// The compound division operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our division
    /// @returns The quotient of the two variables, along with the error propagated appropriately.
    inline Variable &operator/=(const Variable &rhs) {
        this->SetValue(this->GetValue() / rhs.GetValue());
        this->SetError(CalculateMultiplicationDivisonError(this->GetValue(), *this, rhs));
        this->SetUnits(this->GetUnits() + "/" + rhs.GetUnits());
        return *this;
    }

    /// The division operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our division
    /// @returns The quotient of the two variables, along with the error propagated appropriately.
    inline Variable operator/(const Variable &rhs) const {
        Variable lhs = *this;
        lhs /= rhs;
        return lhs;
    }

    /// The templated compound division operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product, which can be any standard c++ class (int, double, etc.).
    /// @returns The quotient of the two variables, along with the error propagated appropriately.
    template <class T>
    inline Variable &operator/=(const T &rhs) {
        this->SetValue(this->GetValue() / rhs);
        this->SetError(this->GetError() / rhs);
        return *this;
    }

    /// The templated division operator. We currently concatenate the units and do not simplify them
    /// @param[in] rhs : The right hand side of our product, which can be any standard c++ class (int, double, etc.).
    /// @returns The quotient of the two variables, along with the error propagated appropriately.
    template <class T>
    inline Variable operator/(const T &rhs) const {
        Variable lhs = *this;
        lhs /= rhs;
        return lhs;
    }

    /// The bitwise left shift operator, this operator is used so that we can output the variable to output streams
    /// like cout.
    /// @param[in] out : The output file stream that we want to use
    /// @param[in] v : The variable that we want to output to the stream.
    /// @returns A reference to the stream that we passed into the method.
    friend std::ostream &operator<<(std::ostream &out, const Variable &v) {
        out << std::to_string(v.GetValue()) << " +- " << std::to_string(v.GetError()) << " " << v.GetUnits();
        return out;
    }

    /// A method that will allow one to output just the value and error, this is useful when writing simple data
    /// files to disk.
    /// @returns A string containing the value, a space, and the error.
    std::string OutputForDataFile(void) const {
        return std::to_string(this->GetValue()) + " " + std::to_string(this->GetError());
    }

    /// Sets the value of the variable
    /// @param[in] a : The value to set
    inline void SetValue(const double &a) { value_ = a; }

    /// Sets the error on the variable
    /// @param[in] a : The value to set
    inline void SetError(const double &a) { error_ = a; }

    /// Sets the units on the variable
    /// @param[in] a : The value to set
    inline void SetUnits(const std::string &a) { units_ = a; }

    /// Get the value of the Variable
    /// @returns the value
    inline double GetValue(void) const { return value_; }

    /// Get the value of the error
    /// @returns the error bars
    inline double GetError(void) const { return error_; }

    /// Get the value of the Variable
    /// @returns the value
    inline std::string GetUnits(void) const { return units_; }

private:
    double value_; ///< The value of the Variable
    double error_; ///< The error on the Variable
    std::string units_; ///< The units on the Variable

    /// Propagates the error on addition and subtraction operations.
    /// @param[in] lhs : The error bar on the left hand side
    /// @param[in] rhs : The error bar on the right hand side
    /// @returns the propagated error bar on the variable
    double CalculateAdditionSubtractionError(const double &lhs, const double &rhs) const {
        return sqrt(lhs * lhs + rhs * rhs);
    }

    /// Propagates the error on addition and subtraction operations.
    /// @param[in] val : The value of the original multiplication or division operation. This needs multiplied in to
    /// properly propagate the error.
    /// @param[in] lhs : The error bar on the left hand side
    /// @param[in] rhs : The error bar on the right hand side
    /// @returns the propagated error bar on the variable
    double CalculateMultiplicationDivisonError(const double &val, const Variable &lhs, const Variable &rhs) const {
        return val * sqrt(pow(lhs.GetError() / lhs.GetValue(), 2) + pow(rhs.GetError() / rhs.GetValue(), 2));
    }
}; //class Variable
#endif //__VARIABLE_HPP__
