//
// Created by Eldar on 06-Nov-18.
//

#include <string>

using namespace std;
#ifndef EX01_DECIMAL_H
#define EX01_DECIMAL_H


class Decimal {

private:
    string number;

public:

    // Constructors
    Decimal(const char number[]);
    Decimal(const string num);

    Decimal() {};

    // Operators
    Decimal operator+(const Decimal &number) const;

    Decimal operator-(const Decimal &number) const;

    Decimal operator*(const Decimal &number) const;

    Decimal operator/(const Decimal &number) const;

    Decimal operator%(const Decimal &number) const;


    Decimal &operator+=(const Decimal &number);

    Decimal &operator-=(const Decimal &number);


    Decimal &operator*=(const Decimal &number);

    bool operator>(const Decimal &number) const;

    bool operator>=(const Decimal &number) const;

    bool operator<(const Decimal &number) const;

    bool operator<=(const Decimal &number) const;

    bool operator==(const Decimal &number) const;

    Decimal operator<<(const int number) const;

    Decimal operator>>(const int number) const;

    Decimal operator>>=(const int number);

    Decimal &operator++();

    Decimal operator++(int);

    Decimal &operator--();

    Decimal operator--(int);

    // Function to find smaller number, return true if str1 smaller then str2
    bool findSmaller(string str1, string str2) const;

    // Assist function for long division, return remainer or value according to flag bool
    string longDivision(string number, string divisor, bool flg) const;

    // Subtract function to assist long division for small numbers
    Decimal cut(string number, string divisor, bool flg) const;

    // Get and set
    string getValue() const;

    void setValue(const string string1);

    // Deep copy for cloning
    Decimal deepClone();


    // Function to convert from int to string and vice versa
    static string intToString(const long int x);

    static int stringToInt(const string str);
};


#endif //EX01_DECIMAL_H
