
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <limits>

using namespace std;

const double PI = acos(-1.0);
vector<string> history;

double inputNumber(const string& message) {
    double value;

    while (true) {
        cout << message;

        if (cin >> value && isfinite(value))
            return value;

        cout << "Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int inputInt(const string& message, int low, int high) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value && value >= low && value <= high)
            return value;

        cout << "Enter an integer from " << low << " to "
             << high << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void showResult(const string& expression, double result) {
    if (!isfinite(result)) {
        cout << "Error: Result is outside the supported range.\n";
        return;
    }

    cout << "\nResult: " << setprecision(12) << result << '\n';
    history.push_back(expression + " = " + to_string(result));
}

void arithmetic() {
    cout << "\n--- ARITHMETIC ---\n";
    cout << "1. Addition\n2. Subtraction\n3. Multiplication\n";
    cout << "4. Division\n5. Power\n6. Remainder\n";

    int choice = inputInt("Choose: ", 1, 6);
    double a = inputNumber("First number: ");
    double b = inputNumber("Second number: ");
    double result = 0;
    string op;

    switch (choice) {
        case 1: result = a + b; op = "+"; break;
        case 2: result = a - b; op = "-"; break;
        case 3: result = a * b; op = "*"; break;

        case 4:
            if (b == 0) {
                cout << "Cannot divide by zero.\n";
                return;
            }
            result = a / b;
            op = "/";
            break;

        case 5:
            result = pow(a, b);
            op = "^";
            break;

        case 6:
            if (b == 0) {
                cout << "Cannot calculate remainder with zero.\n";
                return;
            }
            result = fmod(a, b);
            op = "mod";
            break;
    }

    showResult(to_string(a) + " " + op + " " + to_string(b), result);
}

void scientific() {
    cout << "\n--- SCIENTIFIC FUNCTIONS ---\n";
    cout << "1. Square root\n2. Cube root\n3. Square\n";
    cout << "4. Cube\n5. Absolute value\n6. Factorial\n";
    cout << "7. Sine (degrees)\n8. Cosine (degrees)\n";
    cout << "9. Tangent (degrees)\n10. Natural logarithm\n";
    cout << "11. Log base 10\n12. Exponential (e^x)\n";

    int choice = inputInt("Choose: ", 1, 12);
    double x = inputNumber("Enter number: ");
    double result = 0;
    string name;

    switch (choice) {
        case 1:
            if (x < 0) {
                cout << "Square root requires a non-negative number.\n";
                return;
            }
            result = sqrt(x); name = "sqrt"; break;

        case 2:
            result = cbrt(x); name = "cbrt"; break;

        case 3:
            result = x * x; name = "square"; break;

        case 4:
            result = x * x * x; name = "cube"; break;

        case 5:
            result = fabs(x); name = "abs"; break;

        case 6: {
            if (x < 0 || x != trunc(x) || x > 170) {
                cout << "Factorial requires an integer from 0 to 170.\n";
                return;
            }

            result = 1;
            for (int i = 2; i <= static_cast<int>(x); ++i)
                result *= i;

            name = "factorial";
            break;
        }

        case 7:
            result = sin(x * PI / 180.0); name = "sin"; break;

        case 8:
            result = cos(x * PI / 180.0); name = "cos"; break;

        case 9:
            if (fabs(cos(x * PI / 180.0)) < 1e-12) {
                cout << "Tangent is undefined at this angle.\n";
                return;
            }
            result = tan(x * PI / 180.0); name = "tan"; break;

        case 10:
            if (x <= 0) {
                cout << "Natural logarithm requires x > 0.\n";
                return;
            }
            result = log(x); name = "ln"; break;

        case 11:
            if (x <= 0) {
                cout << "Logarithm requires x > 0.\n";
                return;
            }
            result = log10(x); name = "log10"; break;

        case 12:
            result = exp(x); name = "exp"; break;
    }

    showResult(name + "(" + to_string(x) + ")", result);
}

void percentage() {
    double total = inputNumber("Enter total value: ");
    double percent = inputNumber("Enter percentage: ");

    showResult(to_string(percent) + "% of " + to_string(total),
               total * percent / 100.0);
}

void statistics() {
    int n = inputInt("How many numbers (1-100)? ", 1, 100);
    vector<double> values;

    for (int i = 0; i < n; ++i)
        values.push_back(inputNumber("Enter number: "));

    double sum = accumulate(values.begin(), values.end(), 0.0);
    double mean = sum / n;

    vector<double> sorted = values;
    sort(sorted.begin(), sorted.end());

    double median;
    if (n % 2 == 1)
        median = sorted[n / 2];
    else
        median = sorted[n / 2 - 1] / 2.0 + sorted[n / 2] / 2.0;

    double variance = 0;
    for (double x : values)
        variance += (x - mean) * (x - mean);
    variance /= n;

    cout << "\n--- STATISTICS ---\n";
    cout << "Count: " << n << '\n';
    cout << "Sum: " << sum << '\n';
    cout << "Mean: " << mean << '\n';
    cout << "Median: " << median << '\n';
    cout << "Minimum: " << sorted.front() << '\n';
    cout << "Maximum: " << sorted.back() << '\n';
    cout << "Population variance: " << variance << '\n';
    cout << "Population standard deviation: "
         << sqrt(variance) << '\n';

    history.push_back("Statistics calculated for " +
                      to_string(n) + " values");
}

void solveEquation() {
    cout << "\nEquation format: ax + b = 0\n";

    double a = inputNumber("Enter coefficient a: ");
    double b = inputNumber("Enter coefficient b: ");

    if (a == 0) {
        if (b == 0)
            cout << "Infinitely many solutions.\n";
        else
            cout << "No solution.\n";
        return;
    }

    double x = -b / a;
    showResult("Solve " + to_string(a) + "x + " +
               to_string(b) + " = 0", x);
}

void convertBase() {
    long long number;
    cout << "Enter an integer: ";

    if (!(cin >> number)) {
        cout << "Invalid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    unsigned long long magnitude;
    if (number < 0)
        magnitude = 0ULL - static_cast<unsigned long long>(number);
    else
        magnitude = static_cast<unsigned long long>(number);

    auto convert = [](unsigned long long n, int base) {
        const string digits = "0123456789ABCDEF";
        string output;

        do {
            output.push_back(digits[n % base]);
            n /= base;
        } while (n > 0);

        reverse(output.begin(), output.end());
        return output;
    };

    string sign = number < 0 ? "-" : "";

    cout << "Binary: " << sign << convert(magnitude, 2) << '\n';
    cout << "Octal: " << sign << convert(magnitude, 8) << '\n';
    cout << "Hexadecimal: " << sign << convert(magnitude, 16) << '\n';

    history.push_back("Converted integer " + to_string(number) +
                      " to binary, octal and hexadecimal");
}

void showHistory() {
    cout << "\n--- CALCULATION HISTORY ---\n";

    if (history.empty()) {
        cout << "No calculations yet.\n";
        return;
    }

    for (size_t i = 0; i < history.size(); ++i)
        cout << i + 1 << ". " << history[i] << '\n';
}

int main() {
    cout << fixed << setprecision(6);

    while (true) {
        cout << "\n====================================\n";
        cout << "       CALCPRO 2.0 - C++\n";
        cout << "====================================\n";
        cout << "1. Arithmetic operations\n";
        cout << "2. Scientific functions\n";
        cout << "3. Percentage calculator\n";
        cout << "4. Statistics calculator\n";
        cout << "5. Linear equation solver\n";
        cout << "6. Number system converter\n";
        cout << "7. View history\n";
        cout << "8. Clear history\n";
        cout << "0. Exit\n";

        int choice = inputInt("Select option: ", 0, 8);

        switch (choice) {
            case 1: arithmetic(); break;
            case 2: scientific(); break;
            case 3: percentage(); break;
            case 4: statistics(); break;
            case 5: solveEquation(); break;
            case 6: convertBase(); break;
            case 7: showHistory(); break;

            case 8:
                history.clear();
                cout << "History cleared.\n";
                break;

            case 0:
                cout << "Thanks for using CalcPro 2.0!\n";
                return 0;
        }
    }
}
