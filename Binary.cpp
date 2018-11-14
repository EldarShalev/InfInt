//
// Created by Eldar on 06-Nov-18.
//

#include <string>
#include <algorithm>
#include "Binary.h"
#include <functional>

using namespace std;

/**
 *
 * @param num given number to constructor.
 */
Binary::Binary(const string num) : number(num) {
}

/**
 *
 * @return the value as string.
 */
string Binary::getValue() const {
    return number;
}

/**
 *
 * @param string1 set the value af given string.
 */
void Binary::setValue(const string string1) {
    this->number = string1;
}

/**
 *
 * @param number  a given binary number.
 * @return the logical AND.
 */
Binary Binary::operator&(const Binary &number) const {
    return bitwiseOperator(number, logical_and);

}

/**
 *
 * @param number  a given binary number.
 * @return the logical AND and add it to *this.
 */
Binary &Binary::operator&=(const Binary &number) {
    Binary binary = bitwiseOperator(number, logical_and);
    this->number = binary.getValue();
    return *this;

}

/**
 *
 * @param number  a given binary number.
 * @return the logical OR.
 */
Binary Binary::operator|(const Binary &number) const {
    return bitwiseOperator(number, logical_or);
}

/**
 *
 * @param number  a given binary number.
 * @return the logical XOR.
 */
Binary Binary::operator^(const Binary &number) const {
    return bitwiseOperator(number, logical_xor);
}

/**
 * Creating new function of logical xor.
 * @param x bool x.
 * @param y bool y.
 * @return xor between x and y.
 */
bool Binary::logical_xor(bool x, bool y) {
    return (x || y) && !(x && y);
}

/**
 * Creating new function of logical or.
 * @param x bool x.
 * @param y bool y.
 * @return or between x and y.
 */
bool Binary::logical_or(bool x, bool y) {
    return (x || y);
}

/**
 * Creating new function of logical and.
 * @param x bool x.
 * @param y bool y.
 * @return and between x and y.
 */
bool Binary::logical_and(bool x, bool y) {
    return (x && y);
}

/**
 * A bitwise operator for all the bitwise logic in one function.
 * @param num2 a binary number.
 * @param func the function we want to use (OR, AND, XOR)
 * @return the relevant operator according to given function.
 */
Binary Binary::bitwiseOperator(const Binary &num2, bool(*func)(bool, bool)) const {
    unsigned long int i;
    string result;
    // Get the strings.
    string this_str = this->number;
    string other_str = num2.number;
    // Get the msb
    string msb = "";
    int offset = (int) this_str.size() - (int) num2.number.size();

    // We want both of the numbers to be represented in the same bit length
    if (offset < 0) {
        // this_str is smaller
        char m = this_str.at(0);
        msb += m;
        for (i = 0; i < (-1) * offset; i++) {
            this_str.insert(0, msb);
        }
    } else if (offset > 0) {
        // other_str is smaller
        char m = other_str.at(0);
        msb += m;
        for (i = 0; i < offset; i++) {
            other_str.insert(0, msb);
        }
    }

    // this for is to add 1 or 0 to 'fill' the lower number
    for (i = 0; i < this_str.size(); i++) {
        if (func(this_str.at(i) == '1', other_str.at(i) == '1')) {
            result += '1';
        } else {
            result += '0';
        }
    }

    // Return the Binary number
    return Binary(result);
}




/**
 *
 * @return deep clone of Binary object, means creating new string and assign the string to it.
 */
Binary Binary::deepClone() {
    string temp = this->getValue();
    return Binary(temp.c_str());
}

