//
// Created by Eldar on 06-Nov-18.
//

#ifndef EX01_INFINT_H

#include "Decimal.h"
#include "Binary.h"
#include <iostream>

#define EX01_INFINT_H


using namespace std;


/**
 * Class for InfInt.
 */
class InfInt {

private:

    /**
     * Inner class for Mydata
     */
    class MyData {
    public:
        // Public members for class Infint
        Decimal decimal;
        Binary binary;
        int counter = 1;

        // Default constructor
        MyData() {};

        // Func increament
        void increament() {
            this->counter++;
        }

        // Fun decrement
        void decrement() {
            this->counter--;
        }

        /**
         * Deep Cloning of mydata, creating all new members.
         * @return deep clone of mydata
         */
        MyData deepClone() {
            MyData *tempMyData = new MyData();
            tempMyData->decimal = this->decimal.deepClone();
            tempMyData->binary = this->binary.deepClone();
            return *tempMyData;
        }
    };

    // Member in Infint class
    MyData *data;// = new MyData();
public:

    // Destructor to delete allocated memory
    ~InfInt() {
        if (this->getCount() == 1) {
            delete (data);
            // Decrease by 1
        } else {
            this->data->decrement();
        }
    }
    //The constructors:

    //For pointer of chars
    InfInt(const char num[]);

    // Copy constructors
    InfInt(const InfInt &number);

    // Default (empty) constructor
    InfInt();

    // Constructor for regular int
    InfInt(int num);

    // Constructor for long int
    InfInt(long int num);

    InfInt(string num);

    operator int() const;


    //All the operators
    InfInt operator+(const InfInt &number) const;

    InfInt &operator+=(const InfInt &number);

    InfInt &operator-=(const InfInt &number);

    InfInt &operator*=(const InfInt &number);

    InfInt operator-(const InfInt &number) const;

    InfInt operator*(const InfInt &number) const;

    InfInt operator/(const InfInt &number) const;

    InfInt operator%(const InfInt &number) const;

    InfInt operator&(const InfInt &number) const;

    InfInt operator^(const InfInt &number) const;

    InfInt operator|(const InfInt &number) const;

    bool operator>(const InfInt &number) const;

    bool operator>=(const InfInt &number) const;

    bool operator<(const InfInt &number) const;

    bool operator<=(const InfInt &number) const;

    bool operator==(const InfInt &number) const;

    InfInt operator<<(const int number) const;

    InfInt operator>>(const int number) const;

    InfInt &operator=(const InfInt &other);

    InfInt &operator>>=(const int number);

    InfInt &operator&=(const InfInt &number);

    InfInt &operator++();

    InfInt operator++(int);

    InfInt &operator--();

    InfInt operator--(int);

    // Operator for stream - in and out
    friend ostream &operator<<(ostream &os, const InfInt &inf);

    friend istream &operator>>(istream &input, InfInt &d);

    // Functions for conversion between decimaly to binary and vice versa

    string fromDecimalToBinary(string number) const;

    string fromBinaryToDecimal(string number) const;

    // Convert to negative binary

    void negativeBinary(string &number) const;


    // Getters and Setters for all members
    Decimal getDecimal() const;

    void setDecimal(const string string1);

    void setBinary(const string string1);

    int getCount() const;

    Binary getBinary() const;

    // Deep copy for reference counting

    InfInt deepCopy() const;


};


#endif //EX01_INFINT_H
