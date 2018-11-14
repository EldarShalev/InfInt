//
// Created by Eldar on 06-Nov-18.
//

#include <string>
#include <functional>


using namespace std;
#ifndef EX01_BINARY_H
#define EX01_BINARY_H


class Binary {
private:
    string number;
public:

    // Constructor
    Binary(const string number);

    Binary() {};

    // Operators for binary
    Binary operator^(const Binary &number) const;

    Binary operator&(const Binary &number) const;

    Binary &operator&=(const Binary &number);

    Binary operator|(const Binary &number) const;

    Binary &operator+=(const Binary &number);

    Binary bitwiseOperator(const Binary &num2, bool (*func)(bool, bool)) const;

    Binary operator<<(const int &number) const;

    Binary operator>>(const int &number) const;


    // Functions for logical bitwise
    static bool logical_xor(bool x, bool y);

    static bool logical_or(bool x, bool y);

    static bool logical_and(bool x, bool y);


    // Get and set values
    string getValue() const;

    void setValue(const string string1);

    // Deep copy
    Binary deepClone();


};


#endif //EX01_BINARY_H
