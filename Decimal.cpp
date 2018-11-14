//
// Created by Eldar on 06-Nov-18.
//

#include <iostream>
#include <cstring>
#include <string>
#include<bits/stdc++.h>
#include "Decimal.h"


using namespace std;

/**
 *
 * @param num a given array of chars.
 */
Decimal::Decimal(const char num[]) : number(num) {
}

Decimal::Decimal(const string num) : number(num) {
}

/**
 *
 * @return the string value.
 */
string Decimal::getValue() const {
    return number;
}

/**
 *  Set new number.
 * @param string1 a given string.
 */
void Decimal::setValue(const string string1) {
    this->number = string1;
}

/**
 *
 * @param number  a given number to subtract.
 * @return the subtraction of two numbers.
 */
Decimal Decimal::operator-(const Decimal &number) const {
    // working with two strings for comfortable operation
    string str1 = number.getValue();
    string str2 = this->getValue();
    // For later result
    string temp = "";

    bool wasSwap = false;

    // In case the second one is minus, it's double minus so we can send to plus operator
    if (str1[0] == '-') {
        str1 = str1.substr(1, str1.length() - 1);
        char finalResult[str1.size() + 1];
        strcpy(finalResult, str1.c_str());
        // Return the InfInt of the result
        Decimal newStr = finalResult;
        return *this + newStr;
    }
    // In case the first one is minus
    if (str2[0] == '-') {
        str2 = str2.substr(1, str2.length() - 1);
        char finalResult[str2.size() + 1];
        strcpy(finalResult, str2.c_str());
        // Return the InfInt of the result
        Decimal newStr = finalResult;
        // like to use plus operator and in the end add the minus.
        newStr = newStr + number;
        // reverse resultant string
        temp = newStr.getValue();
        // adding minus
        reverse(temp.begin(), temp.end());
        temp.push_back('-');
        reverse(temp.begin(), temp.end());
        // copy to string
        strcpy(finalResult, temp.c_str());
        return Decimal(finalResult);
    }

    // to find the smaller - swap and add minus later.
    if (findSmaller(str2, str1)) {
        swap(str2, str1);
        wasSwap = true;
    }

    // Take an empty string for storing result
    string result = "";

    // Calculate length of both strings
    int n1 = str2.length();
    int n2 = str1.length();

    int diff = n1 - n2;

    // Initially take carry zero
    int carry = 0;

    // Calculate the carry each time
    for (int i = n2 - 1; i >= 0; i--) {
        // the mathematics, compute difference between current digits and carry
        int sub = ((str2[i + diff] - '0') - (str1[i] - '0') - carry);
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        } else
            carry = 0;

        // Push result to the string result
        result.push_back(sub + '0');
    }

    // subtract remaining digits of str2[]
    for (int i = n1 - n2 - 1; i >= 0; i--) {
        if (str2[i] == '0' && carry) {
            result.push_back('9');
            continue;
        }
        int sub = ((str2[i] - '0') - carry);
        if (i > 0 || sub > 0) // remove preceding 0's
            result.push_back(sub + '0');
        carry = 0;

    }

    // A function to get rid of all the zero in the end of the string
    while (result[result.length() - 1] == '0') {
        result = result.substr(0, result.length() - 1);
    }
    // If we need to add minus to the result
    if (wasSwap) {
        result.push_back('-');
    }
    // reverse resultant string
    reverse(result.begin(), result.end());
    // Converting all to array of chars, which our constructor works with
    char finalResult[result.size() + 1];
    strcpy(finalResult, result.c_str());
    // Return the InfInt of the result
    if (result == "") {
        return Decimal("0");
    }
    return Decimal(finalResult);

}

/**
 *
 * @param number a given number.
 * @return the sum of the numbers.
 */
Decimal Decimal::operator+(const Decimal &number) const {
    // working with two strings for comfortable operation
    string str1 = number.getValue();
    string str2 = this->getValue();
    bool addMinus = false;

    // If both are negative
    if (str1[0] == '-' && str2[0] == '-') {
        // Cut the minus
        str1 = str1.substr(1, str1.length() - 1);
        str2 = str2.substr(1, str2.length() - 1);
        // Add boolean for later to add the minus
        addMinus = true;
        // If the second(right) number is minus
    } else if (str1[0] == '-') {
        // cut it's minus
        str1 = str1.substr(1, str1.length() - 1);
        char finalResult[str1.size() + 1];
        strcpy(finalResult, str1.c_str());
        // Return the InfInt of the result
        Decimal newStr = finalResult;
        // Same as using minus between the second number to the one we cut it's minus
        return *this - newStr;
        // If the first(left) number is minus
    } else if (str2[0] == '-') {
        str2 = str2.substr(1, str2.length() - 1);
        char finalResult[str2.size() + 1];
        strcpy(finalResult, str2.c_str());
        // Return the InfInt of the result
        Decimal const newStr = finalResult;
        // Same as minus the second with the first
        Decimal temp = number;
        return temp - newStr;
    }
    //make sure length of str2 is larger, else swap.
    if (str1.length() > str2.length()) {
        swap(str1, str2);
    }
    // Take an empty string for storing result
    string result = "";

    // Calculate length of both strings
    int n1 = str1.length();
    int n2 = str2.length();

    // Reverse both of strings because we want to sum the number from the least bit to small number
    // begin and end because we want an iterator to the beginning/ending of the string
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    // The carry if we get more then 10 when summing
    int carry = 0;
    for (int i = 0; i < n1; i++) {
        // compute sum of current digits and carry
        int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
        // Push every sum into the result string
        // push_back to Appends character into the end of the string and increasing its length by one
        result.push_back(sum % 10 + '0');

        // Calculate carry for next step
        carry = sum / 10;
    }

    // Add remaining digits of larger number
    for (int i = n1; i < n2; i++) {
        int sum = ((str2[i] - '0') + carry);
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    // Add remaining carry
    if (carry) {
        result.push_back(carry + '0');
    }

    // if both of the numbers were with minus
    if (addMinus) {
        result.push_back('-');
    }
    // reverse resultant string
    reverse(result.begin(), result.end());

    // Return the InfInt of the result
    return Decimal(result.c_str());

}


/**
 *
 * @param number a given number.
 * @return the multiplication between the numbers.
 */
Decimal Decimal::operator*(const Decimal &number) const {
    // working with two strings for comfortable operation
    string str1 = number.getValue();
    string str2 = this->getValue();
    bool addMinus = false;

    if (str1[0] == '-' && str2[0] == '-') {
        // Cut the minus they are not necessary
        str1 = str1.substr(1);
        str2 = str2.substr(1);
    } else if (str1[0] == '-') {
        // cut it's minus
        str1 = str1.substr(1);
        addMinus = true;
    } else if (str2[0] == '-') {
        str2 = str2.substr(1);
        addMinus = true;
    }

    int n1 = str1.size();
    int n2 = str2.size();
    if (n1 == 0 || n2 == 0) {
        return "0";
    }

    //for keeping the result number in vector in reverse order
    vector<int> result(n1 + n2, 0);

    // two indexes are used to find positions in result
    int positionOne = 0;
    int positionTwo = 0;

    // Go from right to left in num1
    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = str1[i] - '0';

        // shift position to left after every multiplication of a digit in num2
        positionTwo = 0;

        // Go from right to left in num2
        for (int j = n2 - 1; j >= 0; j--) {
            // Take current digit of second number
            int n2 = str2[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[positionOne + positionTwo] + carry;

            // Carry for next iteration
            carry = sum / 10;

            // Store result
            result[positionOne + positionTwo] = sum % 10;

            positionTwo++;
        }

        // store carry in next cell
        if (carry > 0)
            result[positionOne + positionTwo] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        positionOne++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // means one or both were 0
    if (i == -1)
        return "0";

    // for the final result
    string resultS = "";

    // Add the result
    while (i >= 0) {
        resultS += intToString(result[i--]);
    }


    // for negative numbers
    if (addMinus) {
        reverse(resultS.begin(), resultS.end());
        resultS.push_back('-');
        reverse(resultS.begin(), resultS.end());
    }
    // Return the InfInt of the result
    return Decimal(resultS.c_str());


}

/**
 *
 * @param str1 number a.
 * @param str2 number b.
 * @return true if a<b, false otherwise
 */
bool Decimal::findSmaller(string str1, string str2) const {
    // Calculate lengths of both string
    int n1 = str1.length();
    int n2 = str2.length();
    bool isNegative = false;
    // If we deal with negative numbers the logic changes so we swap the numbers
    if (str1[0] == '-' && str2[0] == '-') {
        str1 = str1.substr(1, str1.length() - 1);
        str2 = str2.substr(1, str2.length() - 1);
        swap(str1, str2);
        isNegative = true;
    } else if (str1[0] == '-') {
        return true;
    } else if (str2[0] == '-') {
        return false;
    }

    // Check for length only for positive numbers
    if (!isNegative) {
        if (n1 < n2)
            return true;
        if (n1 > n2)
            return false;
    }

    // For loop to compare each digit
    for (int i = 0; i < n1; i++) {
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
    }
    return false;
}

/**
 *
 * @param number a given number.
 * @return this number with the sum of the given number.
 */
Decimal &Decimal::operator+=(const Decimal &number) {
    string str1 = number.getValue();
    string str2 = this->getValue();

    // Getting temp
    Decimal temp = Decimal(str1.c_str()) + Decimal(str2.c_str());
    // Assign to temp value.
    this->number = temp.getValue();
    return *this;
}

/**
 *
 * @param number a given number.
 * @return this number subtract the other number.
 */
Decimal &Decimal::operator-=(const Decimal &number) {
    string str1 = number.getValue();
    string str2 = this->getValue();

    Decimal temp = Decimal(str2.c_str()) - Decimal(str1.c_str());
    this->number = temp.getValue();
    return *this;
}

/**
 *
 * @param number a given number.
 * @return this number multiply the other number.
 */
Decimal &Decimal::operator*=(const Decimal &number) {
    string str1 = number.getValue();
    string str2 = this->getValue();


    Decimal temp = Decimal(str1.c_str()) * Decimal(str2.c_str());
    this->number = temp.getValue();
    return *this;
}

/**
 *
 * @param number a given number.
 * @return true if this number greater then the number.
 */
bool Decimal::operator>(const Decimal &number) const {
    // Edge case for same numbers
    if (this->getValue() == number.getValue()) {
        return false;
    }
    return findSmaller(number.getValue(), this->getValue());
}


/**
 *
 * @param number a given number.
 * @return true if this number greater or equal then the number.
 */
bool Decimal::operator>=(const Decimal &number) const {
    return (findSmaller(number.getValue(), this->getValue())) || number.getValue() == this->getValue();
}

/**
 *
 * @param number a given number.
 * @return true if this number lower  then the number.
 */
bool Decimal::operator<(const Decimal &number) const {
    // Edge case for same numbers
    if (this->getValue() == number.getValue()) {
        return false;
    }
    return !(findSmaller(number.getValue(), this->getValue()));
}

/**
 *
 * @param number a given number.
 * @return true if this number lower  then the number.
 */
bool Decimal::operator<=(const Decimal &number) const {
    return !(findSmaller(number.getValue(), this->getValue())) || number.getValue() == this->getValue();
}

/**
 *
 * @param number a given number.
 * @return true if this number equal to the number.
 */
bool Decimal::operator==(const Decimal &number) const {
    return number.getValue() == this->getValue();
}

/**
 *
 * @param number a given int number.
 * @return the result after shifting left.
 */
Decimal Decimal::operator<<(const int number) const {
    string str1 = intToString(number);
    string str2 = this->getValue();
    Decimal power = "1";
    for (int i = 1; i <= number; i++) {
        power = power * Decimal("2");
    }
    Decimal result = Decimal(str2.c_str()) * power;
    return result;
}

/**
 *
 * @param number a given int number.
 * @return the result after shifting right.
 */
Decimal Decimal::operator>>(const int number) const {
    string decimaly1 = this->getValue();
    Decimal afterDivision;
    Decimal power = "1";
    // Increases power multiple 2 every iteration
    for (int i = 0; i < number; i++) {
        power = power * "2";
    }
    bool isNegative = false;
    if (decimaly1.at(0) == '-') {
        isNegative = true;
    }
    // Divide with the desired power
    afterDivision = Decimal(decimaly1.c_str()) / power;
    // Edge case
    if (isNegative && afterDivision == "0") {
        afterDivision = afterDivision - "1";
    }
    return afterDivision;
}


/**
 *
 * @param number a given int number.
 * @return this number after shifting right.
 */
Decimal Decimal::operator>>=(const int number) {
    string decimaly1 = this->getValue();
    Decimal afterDivision;
    bool isNegative = false;
    Decimal power = "1";
    for (int i = 0; i < number; i++) {
        power = power * "2";
    }
    if (decimaly1.at(0) == '-') {
        isNegative = true;
    }
    afterDivision = Decimal(decimaly1.c_str()) / power;
    // Edge case
    if (isNegative && afterDivision == "0") {
        afterDivision = afterDivision - "1";
    }
    this->number = afterDivision.getValue().c_str();
    return *this;
}

/**
 *
 * @param number  a given number.
 * @return the division of this number with the divisor.
 */
Decimal Decimal::operator/(const Decimal &number) const {
    // working with two strings for comfortable operation
    string divisor = number.getValue();
    string num = this->getValue();
    // Boolean if one of the number has minus
    bool addMinus = false;

    // Avoiding division by zero
    if (divisor.at(0) == '0') {
        throw overflow_error("Cannot divide by zero");
    }

    // All the options for minus
    if (num.at(0) == '-' && divisor.at(0) == '-') {
        // Cut the minus they are not necessary
        num = num.substr(1, num.length() - 1);
        divisor = divisor.substr(1, divisor.length() - 1);
    } else if (num.at(0) == '-') {
        // cut it's minus
        num = num.substr(1, num.length() - 1);
        addMinus = true;
    } else if (divisor.at(0) == '-') {
        divisor = divisor.substr(1, num.length() - 1);
        addMinus = true;
    }
    // To save runtime memory
    if (findSmaller(num, divisor)) {
        return Decimal("0");
    }
    if (num == divisor) {
        return Decimal("1");
    }
    // Calling for long division with two strings and true flag for division.
    string finalResult = longDivision(num, divisor, true);
    // For negative numbers
    if (addMinus) {
        reverse(finalResult.begin(), finalResult.end());
        finalResult.push_back('-');
        reverse(finalResult.begin(), finalResult.end());
    }
    return (Decimal(finalResult.c_str()));

}

/**
 * This is long division function which return the result or the carry depends on the flag
 * @param number number a.
 * @param divisor the divisor.
 * @param flg true for returning division, false for returning the carry.
 * @return the division or the carry according to flag.
 */
string Decimal::longDivision(string number, string divisor, bool flg) const {
    // As result can be very large store it in string
    string resultOfDivision = "";

    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    string temp = "";
    bool wasPushed = false;
    while (Decimal(temp.c_str()) < Decimal(divisor.c_str())) {
        temp.push_back(number.at(idx++));
    }

    string temp2 = "";
    // Repeatedly divide divisor with temp. After every division, update temp to include one more digit.
    while (number.size() >= idx) {
        // If we got a division which is not zero (means we don't need to add digits)
        if ((cut(temp, divisor, true).getValue() == "0")) {
            wasPushed = true;
        }
        // push to string the result.
        resultOfDivision.append((cut(temp, divisor, true)).getValue());
        idx++;
        // If we are out of size.
        if (idx - 1 == number.size()) {
            break;
        }
        // Take next digit of number
        if (cut(temp, divisor, true) > Decimal("0") || temp == "0") {
            temp2 = "";
            wasPushed = false;
        }
        // to avoid pushing endless zeroes to the temp string.
        if (cut(temp, divisor, false).getValue() != "0" && !wasPushed) {
            temp2.append(cut(temp, divisor, false).getValue());
        }

        // push to temp2 and assign it to temp.
        temp2.push_back(number.at(idx - 1));
        temp = temp2;
    }

    // Return the result of division.
    if (flg) {
        return resultOfDivision;
    }
    // Return the remainder
    Decimal carryResult = cut(temp, divisor, false);
    return carryResult.getValue();

}

/**
 * This function give the division between two (small) numbers using subtract.
 * @param number a given number.
 * @param divisor the divisior.
 * @param flg flag for division or carry.
 * @return the division or carry after divided number with divisor.
 */
Decimal Decimal::cut(string number, string divisor, bool flg) const {
    int counter = 0;
    // 2 decimals to copy the const objects.
    Decimal num = Decimal(number.c_str());
    Decimal myDivisor = Decimal(divisor.c_str());
    // count how much time mydivisor is contained in num
    while (num >= myDivisor) {
        num = num - myDivisor;
        counter++;
    }
    // To know if to return the remainder or the result itself
    if (flg) {
        return Decimal(intToString(counter).c_str());
    }
    return Decimal(num.getValue().c_str());

}

/**
 *
 * @param number a given number.
 * @return the carry after dividing the number with the other number.
 */
Decimal Decimal::operator%(const Decimal &number) const {
    // working with two strings for comfortable operation
    string divisor = number.getValue();
    string num = this->getValue();
    // Boolean if one of the number has minus

    // Avoiding division by zero
    if (divisor.at(0) == '0') {
        throw overflow_error("Cannot divide by zero");
    }

    // All the options for minus
    if (num.at(0) == '-' && divisor.at(0) == '-') {
        // Cut the minus they are not necessary
        num = num.substr(1, num.length() - 1);
        divisor = divisor.substr(1, divisor.length() - 1);
    } else if (num.at(0) == '-') {
        // cut it's minus
        num = num.substr(1, num.length() - 1);
    } else if (divisor.at(0) == '-') {
        divisor = divisor.substr(1, num.length() - 1);
    }
    // To save runtime memory
    if (findSmaller(num, divisor)) {
        return Decimal(num.c_str());
    }
    if (num == divisor) {
        return Decimal("0");
    }

    // Using long division with flag for carry.
    string finalResult = longDivision(num, divisor, false);
    if (finalResult[0] == '-') {
        finalResult.substr(1, finalResult.length());
    }
    // In case there is no remain after division.
    if (finalResult == "") {
        finalResult = "0";
    }

    return (Decimal(finalResult.c_str()));
}

/**
 *
 * @return the number +1.
 */
Decimal &Decimal::operator++() {
    // ++prefix
    Decimal temp = Decimal(this->getValue().c_str()) + Decimal("1");
    this->number = temp.getValue();
    return *this;

}

/**
 *
 * @return the minus +1.
 */
Decimal &Decimal::operator--() {
    // --prefix
    Decimal temp = Decimal(this->getValue().c_str()) - Decimal("1");
    this->number = temp.getValue();
    return *this;
}

/**
 *
 * @return the number itself before adding 1 to it.
 */
Decimal Decimal::operator++(int) {
    // postfix ++
    Decimal temp = Decimal(this->getValue().c_str()) + Decimal("1");
    this->number = temp.getValue();
    return *this - "1";
}

/**
 *
 * @return the number itself before subtract 1 to it.
 */
Decimal Decimal::operator--(int) {
    // postfix ++
    Decimal temp = Decimal(this->getValue().c_str()) - Decimal("1");
    this->number = temp.getValue();
    return *this + "1";
}

/**
 *
 * @return deep clone of Decimal object.
 */
Decimal Decimal::deepClone() {
    string temp = this->getValue();
    return Decimal(temp.c_str());
}


/**
 *
 * @param x a given int x.
 * @return the string format of this int.
 */
string Decimal::intToString(const long int x) {

    ostringstream convert;
    convert << x;
    return convert.str();
}

/**
 *
 * @param str a string.
 * @return the integer format of this string.
 */
int Decimal::stringToInt(const string str) {
    int i = 0;
    istringstream(str) >> i;
    return i;
}

