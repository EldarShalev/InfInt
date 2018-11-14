// 312349103 Eldar Shalev
// Created by Eldar on 06-Nov-18.
//

#include <string>
#include "InfInt.h"
#include <iostream>
#include <cstring>
#include<bits/stdc++.h>
#include<bits/stdc++.h>


using namespace std;

/**
 *
 * @param num array of chars for constructor.
 */
InfInt::InfInt(const char num[]) : data(new MyData()) {

    if (num[0] == '0') {
        string s = num;
        s = s.substr(1);
        data->decimal.setValue(s);
        data->binary = fromDecimalToBinary(s);
    } else {
        data->decimal.setValue(num);
        data->binary = fromDecimalToBinary(num);
    }
}

InfInt::InfInt(string num) : data(new MyData()) {
    data->binary = fromDecimalToBinary(num);
    data->decimal = num;
}

/**
 * Default constructor.
 */
InfInt::InfInt() : data(new MyData()) {
    data->decimal.setValue("0");
    data->binary = fromDecimalToBinary("0");
}

/**
 *
 * @param num constructor for integers.
 */
InfInt::InfInt(int num) : data(new MyData()) {
    data->decimal = (std::to_string(num).c_str());
    data->binary = fromDecimalToBinary(std::to_string(num).c_str());
}

/**
 *
 * @param num constructor for integers.
 */
InfInt::InfInt(long int num) : data(new MyData()) {
    data->decimal = (std::to_string(num).c_str());
    data->binary = fromDecimalToBinary(std::to_string(num).c_str());
}

/**
 *
 * @param number copy constructor.
 */
InfInt::InfInt(const InfInt &number) {
    // Init data member (shallow copy)
    this->data = number.data;
    //increment data counter
    this->data->increament();
}


/**
 *
 * @return the decimal number.
 */
Decimal InfInt::getDecimal() const {
    return data->decimal;
}

/**
 *
 * @return the binary number.
 */
Binary InfInt::getBinary() const {
    return data->binary;
}

/**
 *
 * @param number number to use the operator +.
 * @return the sum of the numbers.
 */
InfInt InfInt::operator+(const InfInt &number) const {
    Decimal a = (this->data->decimal + number.getDecimal());
    string value = a.getValue();
    return InfInt(a.getValue().c_str());
}

/**
 *
 * @param number number to use the operator +=.
 * @return the sum of the numbers and assign it to this.
 */
InfInt &InfInt::operator+=(const InfInt &number) {

    // If there is more then one pointer- first deep copy.
    if (this->getCount() > 1) {
        this->deepCopy();
    }
    this->data->decimal += number.getDecimal();
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    return *this;

}

/**
 *
 * @param number number to use the operator -=.
 * @return the subtract of the numbers and assign it to this.
 */
InfInt &InfInt::operator-=(const InfInt &number) {

    // If there is more then one pointer- first deep copy
    if (this->getCount() > 1) {
        this->deepCopy();
    }
    // Move to decimal operator
    this->data->decimal -= number.getDecimal();
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    return *this;

}

/**
 *
 * @param number pointergiven number to use the operator *=.
 * @return the multiple between two numbers and assign it to this.
 */
InfInt &InfInt::operator*=(const InfInt &number) {

    // If there is more then one pointer- first deep copy
    if (this->getCount() > 1) {
        this->deepCopy();
    }
    // Move to decimal operator
    this->data->decimal *= number.getDecimal();
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    // finally return *this
    return *this;

}

/**
 *
 * @param number number to shift right.
 * @return this number after shifting.
 */
InfInt &InfInt::operator>>=(const int number) {

    if (number < 0) {
        throw invalid_argument("Negative value for bitwise shift");
    }

    // If there is more then one pointer- first deep copy
    if (this->getCount() > 1) {
        this->deepCopy();
    }
    // Move to decimal operator
    this->data->decimal >>= number;
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    return *this;

}

/**
 *
 * @param numberpointergiven number to use AND logic with.
 * @return the AND logic between the numbers and assign to this.
 */
InfInt &InfInt::operator&=(const InfInt &number) {

    // If there is more then one pointer- first deep copy
    if (this->getCount() > 1) {
        this->deepCopy();
    }
    // Move to binary operator
    this->data->binary &= number.getBinary();
    this->setDecimal(fromBinaryToDecimal(this->data->binary.getValue()));
    return *this;

}

/**
 *
 * @param string1pointergiven string to set the binary number.
 */
void InfInt::setBinary(const string string1) {
    this->data->binary.setValue(string1);
}

/**
 *
 * @param string1pointergiven string to set the decimal number.
 */
void InfInt::setDecimal(const string string1) {
    this->data->decimal.setValue(string1);

}

/**
 *
 * @param numberpointergiven number to use for subtract with.
 * @return the subtraction between two numbers.
 */
InfInt InfInt::operator-(const InfInt &number) const {

    // Move to decimal operator
    Decimal decimal1 = (this->data->decimal - number.getDecimal());
    return InfInt(decimal1.getValue().c_str());


}

/**
 *
 * @param numberpointergiven number to use for multiple with.
 * @return the multiple between two numbers.
 */
InfInt InfInt::operator*(const InfInt &number) const {

    // Move to decimal operator
    Decimal decimal1 = (this->data->decimal * number.getDecimal());
    return InfInt(decimal1.getValue().c_str());

}

/**
 * Divison function.
 * @param number a given number to divide.
 * @return the divided number.
 */
InfInt InfInt::operator/(const InfInt &number) const {
    Decimal decimal1 = (this->data->decimal / number.getDecimal());
    return InfInt(decimal1.getValue().c_str());
}

/**
 * Mudulo number.
 * @param number  a given divisor to modulu.
 * @return the carry.
 */
InfInt InfInt::operator%(const InfInt &number) const {
    // Move to decimal operator
    Decimal decimal1 = (this->data->decimal % number.getDecimal());
    return InfInt(decimal1.getValue().c_str());
}

/**
 *
 * @param number a given number for AND logic.
 * @return the AND logic between two numbers.
 */
InfInt InfInt::operator&(const InfInt &number) const {
    // Move to binary operator
    Binary binary1 = (this->data->binary & number.getBinary());
    string temp = fromBinaryToDecimal(binary1.getValue());
    return InfInt(temp.c_str());
}

/**
 *
 * @param number a given number for OR logic.
 * @return the OR logic between two numbers.
 */
InfInt InfInt::operator|(const InfInt &number) const {
    // Move to binary operator
    Binary binary1 = (this->data->binary | number.getBinary());
    string temp = fromBinaryToDecimal(binary1.getValue());
    return InfInt(temp.c_str());

}

/**
 *
 * @param number a given number for XOR logic.
 * @return the XOR logic between two numbers.
 */
InfInt InfInt::operator^(const InfInt &number) const {
    // Move to binary operator
    Binary binary1 = (this->data->binary ^ number.getBinary());
    string temp = fromBinaryToDecimal(binary1.getValue());
    return InfInt(temp.c_str());
}

/**
 *
 * @param number a given number to comapre with.
 * @return true if this number grater then the second one.
 */
bool InfInt::operator>(const InfInt &number) const {
    // Move to decimal operator
    return this->getDecimal() > number.getDecimal();
}

/**
 *
 * @param number a given number to comapre with.
 * @return true if this number grater or equal then the second one.
 */
bool InfInt::operator>=(const InfInt &number) const {
    // Move to decimal operator
    return this->getDecimal() >= number.getDecimal();
}

/**
 *
 * @param number a given number to comapre with.
 * @return true if this number lower then the second one.
 */
bool InfInt::operator<(const InfInt &number) const {
    // Move to decimal operator
    return this->getDecimal() < number.getDecimal();
}


/**
 *
 * @param number a given number to comapre with.
 * @return true if this number lower or equal then the second one.
 */
bool InfInt::operator<=(const InfInt &number) const {
    // Move to decimal operator
    return this->getDecimal() <= number.getDecimal();
}

/**
 *
 * @param number a given number to comapre with.
 * @return true if this number is equal to the second one.
 */
bool InfInt::operator==(const InfInt &number) const {
    // Move to decimal operator
    return this->getDecimal() == number.getDecimal();
}


/**
 *
 * @param number the length of bits to shift left.
 * @return the result of shifting.
 */
InfInt InfInt::operator<<(const int number) const {

    if (number < 0) {
        throw invalid_argument("Negative value for bitwise shift");
    }
    // Move to decimal operator
    Decimal decimal1 = (this->data->decimal << number);
    return InfInt(decimal1.getValue().c_str());

}

/**
 *
 * @param number the length of bits to shift right.
 * @return the result of shifting.
 */
InfInt InfInt::operator>>(const int number) const {
    if (number < 0) {
        throw invalid_argument("Negative value for bitwise shift");
    }
    // Move to decimal operator
    Decimal decimal1 = (this->data->decimal >> number);
    return InfInt(decimal1.getValue().c_str());

}

/**
 * This function convert from Decimal to binary using the '5' carry logic for each digit.
 * @param number a given string in decimal format.
 * @return the string in binary format.
 */
string InfInt::fromDecimalToBinary(const string n) const {
    string number = n;
    string blank = "";
    string bin = "";
    bool isNegative = false;

    // Edge cases for 1 and zero.
    if (number == "1") {
        return "00000001";
    }
    if (number == "0") {
        return "00000000";
    }
    // If we got a neagtive number, flag for dealing with it.
    if (number[0] == '-') {
        isNegative = true;
        number = number.substr(1, number.length() - 1);
    }
    unsigned long int size = number.length();
    for (int i = 0; i < size; i++) {
        blank.push_back('0');
    }
    // As long as we have place- push the number with the algorithm - Fill to 5.
    while (number != blank) {
        int carry = 0;
        for (int i = 0; i < size; i++) {
            int digit = number[i] - '0';
            number[i] = ((number[i] - '0') / 2) + carry + '0';
            // The algorithm push 5 for odd numbers and 0 for even numbers
            if (digit % 2) {
                carry = 5;
            } else {
                carry = 0;
            }
        }
        // to know if to push 1 or zero according to the carry (zero or 5)
        if (carry) {
            // Push 1 if we had a carry after divided by 2
            bin.push_back('1');
        } else {
            // Push 0 if we hadn't a carry after divided by 2
            bin.push_back('0');
        }
    }
    // Push last bit
    bin.push_back('0');
    // Reverse the output
    reverse(bin.begin(), bin.end());
    // Check if negative
    if (isNegative) {
        negativeBinary(bin);
    }
    // Fill to '2' algorithm - 0/1 according if negative or not.
    if (bin.size() % 8 != 0) {
        reverse(bin.begin(), bin.end());
        if (isNegative) {
            while (bin.size() % 8 != 0) {
                bin.push_back('1');
            }
        } else {
            while (bin.size() % 8 != 0) {
                bin.push_back('0');
            }
        }
        // reverse again
        reverse(bin.begin(), bin.end());
    }
    // return the binary number
    return bin;
}

/**
 * This is function for negative binary.
 * @param number a given negative binary string
 */
void InfInt::negativeBinary(string &number) const {
    unsigned long int size = number.length();
    // Swap the bits because its negative
    for (int i = 0; i < size; i++) {
        if (number[i] == '1') {
            number[i] = '0';
        } else {
            number[i] = '1';
        }
    }
    // Minus 1 to size
    size--;
    while (number[size] != '0' && size >= 0) {
        number[size] = '0';
        size--;
    }
    if (size >= 0) {
        number[size] = '1';
    }
}

/**
 * This is from binary to decimaly. where there is digit 1 we multiple by the relecant power.
 * @param number a given binary string.
 * @return the decimal format.
 */
string InfInt::fromBinaryToDecimal(const string number) const {
    string result1 = "";
    Decimal finalResult("0");
    // Init power
    Decimal power = "1";
    string exponent;
    // if the bit is 1 - according to the place it's the power of 2.
    for (int i = number.length() - 1; i > 0; i--) {
        if (number[i] == '1') {
            result1 = power.getValue();
            finalResult = finalResult + Decimal(result1.c_str());
        }
        // Increase power
        power = power * Decimal("2");
    }

    // If negative
    if (number.at(0) == '1') {
        // Subtract the final result with the MSB - this is actually the negative value
        return (finalResult - Decimal(power.getValue().c_str())).getValue();
    } else {
        return finalResult.getValue();
    }
}


/**
 *
 * @return the number+1.
 */
InfInt &InfInt::operator++() {
    // ++prefix plus plus
    ++data->decimal;
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    return *this;
}

/**
 *
 * @return the number minus 1.
 */
InfInt &InfInt::operator--() {
    // --prefix minus minus
    --data->decimal;
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    return *this;
}

/**
 *
 * @return the number as is and add to it 1.
 */
InfInt InfInt::operator++(int) {
    // postfix ++
    string temp = this->getDecimal().getValue();
    ++(this->data->decimal);
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    // return the temp so we will no get the increased value
    return InfInt(temp.c_str());
}


/**
 *
 * @return the number as is and minus to it 1.
 */
InfInt InfInt::operator--(int) {
    // postfix ++
    string temp = this->getDecimal().getValue();
    --(this->data->decimal);
    this->setBinary(fromDecimalToBinary(this->data->decimal.getValue()));
    // Return temp so we will not decrease the value.
    return InfInt(temp.c_str());
}

/**
 *
 * @param os a given steam.
 * @param inf  the number.
 * @return the printed number.
 */
ostream &operator<<(ostream &os, const InfInt &inf) {
    os << inf.getDecimal().getValue();
    return os;
}

/**
 *
 * @param in a given input stream.
 * @param d  a given number.
 * @return the number after getting it from input.
 */
istream &operator>>(istream &in, InfInt &d) {

    // Get temp to input
    string temp;
    in >> temp;
    // Make infint with the input string
//    Decimal(temp.c_str());
    d = InfInt(temp.c_str());
    // Set the binary value according to dec string
//    d.setBinary(d.fromDecimalToBinary(temp));
    return in;
}

/**
 *
 * @return the conversion between InfInt to int.
 */
InfInt::operator int() const {
    // Get the binary value
    string bin = data->binary.getValue();
    // Subtract if more then 32 digits
    if (bin.size() > 32) {
        bin = bin.substr(bin.size() - 32, bin.size());
    }
    // Return the Decimal of the string
    string dec = fromBinaryToDecimal(bin);
    return Decimal::stringToInt(dec);
}

/**
 *
 * @param other a given number.
 * @return the assignment of the operator and increase the counter.
 */
InfInt &InfInt::operator=(const InfInt &other) {
    // Edge case if we got to assign same object
    if (*this == other) {
        return *this;
    }

    // store current data in temp var
    MyData *temp = this->data;
    // assign other data to my data
    this->data = other.data;
    // increment other data counter
    this->data->increament();
    // decrement my data pointer (and delete if needed)
    temp->decrement();
    if (temp->counter == 0) {
        delete (temp);
    }
    return *this;

}

/**
 *
 * @return the current counter for all pointers that point to the object.
 */
int InfInt::getCount() const {
    return this->data->counter;
}

/**
 *
 * @return Deep copy of Infint using deep copy of data member.
 */
InfInt InfInt::deepCopy() const {
    this->data->deepClone();
}