
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <bitset>
#include <limits>
#include <cstdint>

using namespace std;

const double PI = acos(-1.0);

double readNumber(const string& prompt) {
    double x;

    while (true) {
        cout << prompt;

        if (cin >> x && isfinite(x))
            return x;

        cout << "Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readChoice(int low, int high) {
    int choice;

    while (true) {
        cout << "Select option: ";

        if (cin >> choice && choice >= low && choice <= high)
            return choice;

        cout << "Enter a number from " << low << " to " << high << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void showResult(const string& label, double result) {
    if (!isfinite(result)) {
        cout << "\nError: Result is outside the supported range.\n";
        return;
    }

    cout << "\n------------------------------------\n";
    cout << label << " = " << setprecision(12) << result << '\n';
    cout << "------------------------------------\n";
}

void arithmeticMode() {
    cout << "\n--- ARITHMETIC MODE ---\n";
    cout << "1. Add\n2. Subtract\n3. Multiply\n";
    cout << "4. Divide\n5. Power\n6. Remainder\n";

    int op = readChoice(1, 6);
    double a = readNumber("First number: ");
    double b = readNumber("Second number: ");
    double result = 0;
    string symbol;

    switch (op) {
        case 1: result = a + b; symbol = "+"; break;
        case 2: result = a - b; symbol = "-"; break;
        case 3: result = a * b; symbol = "*"; break;

        case 4:
            if (b == 0) {
                cout << "Error: Cannot divide by zero.\n";
                return;
            }
            result = a / b;
            symbol = "/";
            break;

        case 5:
            result = pow(a, b);
            symbol = "^";
            break;

        case 6:
            if (b == 0) {
                cout << "Error: Remainder by zero is undefined.\n";
                return;
            }
            result = fmod(a, b);
            symbol = "mod";
            break;
    }

    showResult(to_string(a) + " " + symbol + " " + to_string(b), result);
}

void scientificMode() {
    cout << "\n--- SCIENTIFIC MODE ---\n";
    cout << "1. Square root\n2. Cube root\n3. Square\n";
    cout << "4. Sine (degrees)\n5. Cosine (degrees)\n";
    cout << "6. Tangent (degrees)\n7. Natural log\n";
    cout << "8. Log base 10\n9. Exponential e^x\n";
    cout << "10. Absolute value\n11. Factorial\n";
    cout << "12. Reciprocal\n";

    int op = readChoice(1, 12);
    double x = readNumber("Enter value: ");
    double result = 0;
    string name;

    switch (op) {
        case 1:
            if (x < 0) {
                cout << "Error: Square root requires x >= 0.\n";
                return;
            }
            result = sqrt(x);
            name = "sqrt";
            break;

        case 2:
            result = cbrt(x);
            name = "cbrt";
            break;

        case 3:
            result = x * x;
            name = "square";
            break;

        case 4:
            result = sin(x * PI / 180.0);
            name = "sin";
            break;

        case 5:
            result = cos(x * PI / 180.0);
            name = "cos";
            break;

        case 6:
            if (fabs(cos(x * PI / 180.0)) < 1e-12) {
                cout << "Error: Tangent is undefined at this angle.\n";
                return;
            }
            result = tan(x * PI / 180.0);
            name = "tan";
            break;

        case 7:
            if (x <= 0) {
                cout << "Error: ln requires a positive value.\n";
                return;
            }
            result = log(x);
            name = "ln";
            break;

        case 8:
            if (x <= 0) {
                cout << "Error: log requires a positive value.\n";
                return;
            }
            result = log10(x);
            name = "log10";
            break;

        case 9:
            result = exp(x);
            name = "exp";
            break;

        case 10:
            result = fabs(x);
            name = "abs";
            break;

        case 11:
            if (x < 0 || x != trunc(x) || x > 170) {
                cout << "Enter an integer from 0 to 170.\n";
                return;
            }
            result = 1;
            for (int i = 2; i <= static_cast<int>(x); ++i)
                result *= i;
            name = "factorial";
            break;

        case 12:
            if (x == 0) {
                cout << "Error: Reciprocal of zero is undefined.\n";
                return;
            }
            result = 1.0 / x;
            name = "reciprocal";
            break;
    }

    showResult(name + "(" + to_string(x) + ")", result);
}

void programmerMode() {
    cout << "\n--- PROGRAMMER MODE ---\n";
    cout << "1. Decimal to binary\n";
    cout << "2. Decimal to hexadecimal\n";
    cout << "3. Bitwise AND\n";
    cout << "4. Bitwise OR\n";
    cout << "5. Bitwise XOR\n";
    cout << "6. Left shift\n";
    cout << "7. Right shift\n";

    int op = readChoice(1, 7);
    long long a, b = 0;

    cout << "Enter first integer: ";

    if (!(cin >> a)) {
        cout << "Invalid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (op >= 3) {
        cout << "Enter second integer (shift amount for shifts): ";

        if (!(cin >> b)) {
            cout << "Invalid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
    }

    if (op <= 2) {
        if (a < 0) {
            cout << "Enter a non-negative integer for base conversion.\n";
            return;
        }

        unsigned long long n = static_cast<unsigned long long>(a);

        if (op == 1) {
            if (n == 0) {
                cout << "Binary: 0\n";
                return;
            }

            string binary;
            while (n > 0) {
                binary = char('0' + n % 2) + binary;
                n /= 2;
            }
            cout << "Binary: " << binary << '\n';
        } else {
            stringstream ss;
            ss << hex << uppercase << n;
            cout << "Hexadecimal: 0x" << ss.str() << '\n';
        }
        return;
    }

    if (op >= 6 && (b < 0 || b >= 64)) {
        cout << "Shift amount must be from 0 to 63.\n";
        return;
    }

    if (op == 7 && a < 0) {
        cout << "Right-shifting negative integers is implementation-defined.\n";
        return;
    }

    // Unsigned operations avoid undefined signed left-shift behavior.
    uint64_t x = static_cast<uint64_t>(a);
    uint64_t y = static_cast<uint64_t>(b);
    uint64_t result = 0;

    switch (op) {
        case 3: result = x & y; break;
        case 4: result = x | y; break;
        case 5: result = x ^ y; break;
        case 6: result = x << b; break;
        case 7: result = x >> b; break;
    }

    cout << "Unsigned 64-bit result: " << result << '\n';
    cout << "Binary: " << bitset<64>(result) << '\n';
}

void percentageMode() {
    double total = readNumber("Enter total: ");
    double percentage = readNumber("Enter percentage: ");

    showResult(to_string(percentage) + "% of " + to_string(total),
               total * percentage / 100.0);
}

int main() {
    cout << fixed << setprecision(6);

    while (true) {
        cout << "\n";
        cout << "========================================\n";
        cout << "          CALCPRO PRO 3.0\n";
        cout << "       SCIENTIFIC CALCULATOR\n";
        cout << "========================================\n";
        cout << "1. Arithmetic calculator\n";
        cout << "2. Scientific calculator\n";
        cout << "3. Programmer calculator\n";
        cout << "4. Percentage calculator\n";
        cout << "0. Exit\n";
        cout << "========================================\n";

        int choice = readChoice(0, 4);

        switch (choice) {
            case 1: arithmeticMode(); break;
            case 2: scientificMode(); break;
            case 3: programmerMode(); break;
            case 4: percentageMode(); break;
            case 0:
                cout << "Thank you for using CalcPro Pro!\n";
                return 0;
        }
    }
}
