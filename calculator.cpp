
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>

using namespace std;

const double PI = 3.14159265358979323846;

vector<string> history;

double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

void showHistory() {
    cout << "\n========== CALCULATION HISTORY ==========\n";

    if (history.empty()) {
        cout << "No calculations yet.\n";
    } else {
        for (int i = 0; i < (int)history.size(); i++) {
            cout << i + 1 << ". " << history[i] << '\n';
        }
    }

    cout << "=========================================\n";
}

double getNumber(const string& message) {
    double number;

    while (true) {
        cout << message;

        if (cin >> number && isfinite(number)) {
            return number;
        }

        cout << "Invalid input! Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void recordResult(const string& expression, double result) {
    cout << "\nResult: " << setprecision(12) << result << "\n";
    history.push_back(expression + " = " + to_string(result));
}

int main() {
    int choice;

    cout << fixed << setprecision(6);

    do {
        cout << "\n";
        cout << "=========================================\n";
        cout << "       ADVANCED SCIENTIFIC CALCULATOR\n";
        cout << "=========================================\n";
        cout << " 1. Addition\n";
        cout << " 2. Subtraction\n";
        cout << " 3. Multiplication\n";
        cout << " 4. Division\n";
        cout << " 5. Power (x^y)\n";
        cout << " 6. Square Root\n";
        cout << " 7. Cube Root\n";
        cout << " 8. Modulus (integers)\n";
        cout << " 9. Sine (degrees)\n";
        cout << "10. Cosine (degrees)\n";
        cout << "11. Tangent (degrees)\n";
        cout << "12. Natural Log (ln)\n";
        cout << "13. Log Base 10\n";
        cout << "14. Exponential (e^x)\n";
        cout << "15. Absolute Value\n";
        cout << "16. Factorial\n";
        cout << "17. Percentage\n";
        cout << "18. Show History\n";
        cout << "19. Clear History\n";
        cout << " 0. Exit\n";
        cout << "=========================================\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid menu input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        double a, b, result = 0.0;
        bool valid = true;
        string expression;

        switch (choice) {
            case 1:
                a = getNumber("Enter first number: ");
                b = getNumber("Enter second number: ");
                result = a + b;
                expression = to_string(a) + " + " + to_string(b);
                break;

            case 2:
                a = getNumber("Enter first number: ");
                b = getNumber("Enter second number: ");
                result = a - b;
                expression = to_string(a) + " - " + to_string(b);
                break;

            case 3:
                a = getNumber("Enter first number: ");
                b = getNumber("Enter second number: ");
                result = a * b;
                expression = to_string(a) + " * " + to_string(b);
                break;

            case 4:
                a = getNumber("Enter numerator: ");
                b = getNumber("Enter denominator: ");

                if (b == 0) {
                    cout << "Error: Division by zero is not allowed.\n";
                    valid = false;
                } else {
                    result = a / b;
                    expression = to_string(a) + " / " + to_string(b);
                }
                break;

            case 5:
                a = getNumber("Enter base: ");
                b = getNumber("Enter exponent: ");
                result = pow(a, b);

                if (!isfinite(result)) {
                    cout << "Error: Result is outside the supported range.\n";
                    valid = false;
                } else {
                    expression = to_string(a) + " ^ " + to_string(b);
                }
                break;

            case 6:
                a = getNumber("Enter number: ");

                if (a < 0) {
                    cout << "Error: Square root of a negative number "
                         << "is not real.\n";
                    valid = false;
                } else {
                    result = sqrt(a);
                    expression = "sqrt(" + to_string(a) + ")";
                }
                break;

            case 7:
                a = getNumber("Enter number: ");
                result = cbrt(a);
                expression = "cbrt(" + to_string(a) + ")";
                break;

            case 8: {
                long long x, y;

                cout << "Enter first integer: ";
                if (!(cin >> x)) {
                    cout << "Invalid integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    valid = false;
                    break;
                }

                cout << "Enter second integer: ";
                if (!(cin >> y)) {
                    cout << "Invalid integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    valid = false;
                    break;
                }

                if (y == 0) {
                    cout << "Error: Modulus by zero is not allowed.\n";
                    valid = false;
                } else {
                    result = static_cast<double>(x % y);
                    expression = to_string(x) + " % " + to_string(y);
                }
                break;
            }

            case 9:
                a = getNumber("Enter angle in degrees: ");
                result = sin(toRadians(a));
                expression = "sin(" + to_string(a) + " degrees)";
                break;

            case 10:
                a = getNumber("Enter angle in degrees: ");
                result = cos(toRadians(a));
                expression = "cos(" + to_string(a) + " degrees)";
                break;

            case 11:
                a = getNumber("Enter angle in degrees: ");

                if (fabs(cos(toRadians(a))) < 1e-12) {
                    cout << "Error: Tangent is undefined at this angle.\n";
                    valid = false;
                } else {
                    result = tan(toRadians(a));
                    expression = "tan(" + to_string(a) + " degrees)";
                }
                break;

            case 12:
                a = getNumber("Enter positive number: ");

                if (a <= 0) {
                    cout << "Error: ln is defined only for positive numbers.\n";
                    valid = false;
                } else {
                    result = log(a);
                    expression = "ln(" + to_string(a) + ")";
                }
                break;

            case 13:
                a = getNumber("Enter positive number: ");

                if (a <= 0) {
                    cout << "Error: Logarithm requires a positive number.\n";
                    valid = false;
                } else {
                    result = log10(a);
                    expression = "log10(" + to_string(a) + ")";
                }
                break;

            case 14:
                a = getNumber("Enter exponent: ");
                result = exp(a);

                if (!isfinite(result)) {
                    cout << "Error: Result is outside the supported range.\n";
                    valid = false;
                } else {
                    expression = "exp(" + to_string(a) + ")";
                }
                break;

            case 15:
                a = getNumber("Enter number: ");
                result = fabs(a);
                expression = "abs(" + to_string(a) + ")";
                break;

            case 16: {
                cout << "Enter a non-negative integer (0-170): ";
                long long n;

                if (!(cin >> n)) {
                    cout << "Invalid integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    valid = false;
                    break;
                }

                if (n < 0 || n > 170) {
                    cout << "Error: Enter an integer from 0 to 170.\n";
                    valid = false;
                } else {
                    result = 1;

                    for (int i = 2; i <= n; i++) {
                        result *= i;
                    }

                    expression = to_string(n) + "!";
                }
                break;
            }

            case 17:
                a = getNumber("Enter total value: ");
                b = getNumber("Enter percentage: ");
                result = a * b / 100.0;
                expression = to_string(b) + "% of " + to_string(a);
                break;

            case 18:
                showHistory();
                continue;

            case 19:
                history.clear();
                cout << "Calculation history cleared.\n";
                continue;

            case 0:
                cout << "\nThank you for using the calculator!\n";
                cout << "Keep learning C++ and building projects!\n";
                break;

            default:
                cout << "Invalid choice. Select an option from 0 to 19.\n";
                continue;
        }

        if (valid && choice != 0) {
            if (!isfinite(result)) {
                cout << "Error: Result is outside the supported range.\n";
            } else {
                recordResult(expression, result);
            }
        }

    } while (choice != 0);

    return 0;
}
