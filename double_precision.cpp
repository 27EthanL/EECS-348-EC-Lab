#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

// Add this to avoid repeating std::
using namespace std;

// Prototype for the extractNumeric function
double extractNumeric(const string& str) {
    int firstTwoNotDigit = 0;
    string firstTwo = str.substr(0, 2);
    string restOfStr = str.substr(1, -1);
    bool negative = false;
    bool decimalspot = false;
    for (char c : firstTwo) {
        if (!isdigit(c)) {
            if (c == '-') {
                negative = true;
            }
            if (c == '.' && firstTwoNotDigit < 2) {
                decimalspot = true;
                firstTwoNotDigit--;
            }
            firstTwoNotDigit++;
        }
    }
    if (firstTwoNotDigit == 2) {
        return -999999.99;
    } else {
        for (char c : restOfStr) {
            if (!isdigit(c)) {
                if (c != '.') {
                    return -999999.99;
                } else {
                    decimalspot = true;
                }
            }
        }
    }

    char decimal = '.';
    string beforeDecimal = "";
    string afterDecimal = "";
    string beforeDecimalReversed = "";
    string number = "";
    string numberReversed = "";
    double result = 0;

    if (decimalspot) {
        int index = str.find(decimal);
        if (firstTwoNotDigit == 1) {
            beforeDecimal = str.substr(1, index - 1);
            afterDecimal = str.substr(index + 1, -1);
        } else {
            beforeDecimal = str.substr(0, index);
            afterDecimal = str.substr(index + 1, -1);
        }

        for (int i = beforeDecimal.length() - 1; i >= 0; i--) {
            beforeDecimalReversed += beforeDecimal[i];
        }

        for (int i = 0; i < beforeDecimalReversed.length(); ++i) {
            int numBefore = beforeDecimalReversed[i] - '0';
            result += numBefore * pow(10, i);
        }

        for (int i = 0; i < afterDecimal.length(); ++i) {
            int numAfter = afterDecimal[i] - '0';
            result += numAfter / pow(10, i + 1);
        }

    } else {
        if (firstTwoNotDigit == 1) {
            number = str.substr(1, -1);
        } else {
            number = str;
        }

        for (int i = number.length() - 1; i >= 0; i--) {
            numberReversed += number[i];
        }

        for (int i = 0; i < numberReversed.length(); ++i) {
            int numBer = numberReversed[i] - '0';
            result += numBer * pow(10, i);
        }
    }

    if (negative) {
        return result * -1;
    }

    return result;
}

int main(){
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        cin >> input;

        if (input == "END") {
            break;
        }

        double number = extractNumeric(input);

        if (number != -999999.99) {
            cout << "The input is: " << fixed << setprecision(4) << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }

    return 0;
}