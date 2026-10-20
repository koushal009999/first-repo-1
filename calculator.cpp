
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

const double PI = 3.14159265358979323846;

vector<string> history;
double memoryValue = 0.0;
bool memorySet = false;

// Convert degrees to radians
double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

// Format numbers without unnecessary trailing zeros
string formatNumber(double value) {
    ostringstream out;
    out << setprecision(12) << defaultfloat << value;
    return out.str();
}

// Safely read a number
double getNumber(const string& message) {
    double number;

    while (true) {
        cout << message;

        if (cin >> number && isfinite(number)) {
            return number;
        }

        cout << "Invalid input! Enter a valid finite number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Safely read an integer
int getChoice() {
    int choice;

    while (true) {
        cout << "\nEnter your choice: ";

        if (cin >> choice) {
            return choice;
        }

        cout << "Invalid input! Enter an integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Display result and save calculation
void recordResult(const string& expression, double result) {
    cout << "\n-----------------------------------------\n";
    cout << "Expression : " << expression << '\n';
    cout << "Result     : " << formatNumber(result) << '\n';
    cout << "-----------------------------------------\n";

    history.push_back(expression + " = " + formatNumber(result));
}

// Check result before recording
void finishCalculation(const string& expression, double result) {
    if (!isfinite(result)) {
        cout << "Error: Result is outside the supported range.\n";
        return;
    }

    recordResult(expression, result);
}

// Show calculation history
void showHistory() {
    cout << "\n========== CALCULATION HISTORY ==========\n";

    if (history.empty()) {
        cout << "No calculations recorded yet.\n";
    } else {
        for (size_t i = 0; i < history.size(); ++i) {
            cout << i + 1 << ". " << history[i] << '\n';
        }
    }

    cout << "=========================================\n";
}

// Basic arithmetic
void basicOperations(int choice) {
    double a = getNumber("Enter first number: ");
    double b = getNumber("Enter second number: ");
    double result = 0.0;
    string expression;

    switch (choice) {
        case 1:
            result = a + b;
            expression = formatNumber(a) + " + " + formatNumber(b);
            break;

        case 2:
            result = a - b;
            expression = formatNumber(a) + " - " + formatNumber(b);
            break;

        case 3:
            result = a * b;
            expression = formatNumber(a) + " * " + formatNumber(b);
            break;

        case 4:
            if (b == 0.0) {
                cout << "Error: Division by zero is not allowed.\n";
                return;
            }
            result = a / b;
            expression = formatNumber(a) + " / " + formatNumber(b);
            break;

        case 5:
            result = fmod(a, b);
            if (b == 0.0) {
                cout << "Error: Modulus by zero is not allowed.\n";
                return;
            }
            expression = formatNumber(a) + " mod " + formatNumber(b);
            break;

        case 6:
            result = pow(a, b);
            expression = formatNumber(a) + " ^ " + formatNumber(b);
            break;

        default:
            return;
    }

    finishCalculation(expression, result);
}

// Powers and roots
void powerRootOperations(int choice) {
    double a, b, result;
    string expression;

    switch (choice) {
        case 7:
            a = getNumber("Enter number: ");
            result = sqrt(a);

            if (a < 0) {
                cout << "Error: Real square root requires a non-negative number.\n";
                return;
            }

            expression = "sqrt(" + formatNumber(a) + ")";
            break;

        case 8:
            a = getNumber("Enter number: ");
            result = cbrt(a);
            expression = "cbrt(" + formatNumber(a) + ")";
            break;

        case 9:
            a = getNumber("Enter number: ");
            result = a * a;
            expression = formatNumber(a) + "^2";
            break;

        case 10:
            a = getNumber("Enter number: ");
            result = a * a * a;
            expression = formatNumber(a) + "^3";
            break;

        case 11:
            a = getNumber("Enter number: ");

            if (a == 0.0) {
                cout << "Error: Zero has no reciprocal.\n";
                return;
            }

            result = 1.0 / a;
            expression = "1 / " + formatNumber(a);
            break;

        case 12:
            a = getNumber("Enter number: ");
            b = getNumber("Enter root index: ");

            if (b == 0.0) {
                cout << "Error: Root index cannot be zero.\n";
                return;
            }

            if (a < 0.0) {
                if (b != trunc(b) ||
                    fmod(fabs(b), 2.0) != 1.0) {
                    cout << "Error: Negative numbers require an odd integer root index.\n";
                    return;
                }

                result = -pow(-a, 1.0 / b);
            } else {
                result = pow(a, 1.0 / b);
            }

            expression = formatNumber(b) + "th root of "
                       + formatNumber(a);
            break;

        default:
            return;
    }

    finishCalculation(expression, result);
}

// Trigonometric operations: angles in degrees
void trigonometry(int choice) {
    double angle = getNumber("Enter angle in degrees: ");
    double radians = toRadians(angle);
    double result;
    string expression;

    switch (choice) {
        case 13:
            result = sin(radians);
            expression = "sin(" + formatNumber(angle) + " deg)";
            break;

        case 14:
            result = cos(radians);
            expression = "cos(" + formatNumber(angle) + " deg)";
            break;

        case 15:
            if (fabs(cos(radians)) < 1e-12) {
                cout << "Error: Tangent is undefined at this angle.\n";
                return;
            }
            result = tan(radians);
            expression = "tan(" + formatNumber(angle) + " deg)";
            break;

        case 16:
            if (angle < -1.0 || angle > 1.0) {
                cout << "Error: asin input must be between -1 and 1.\n";
                return;
            }
            result = asin(angle) * 180.0 / PI;
            expression = "asin(" + formatNumber(angle) + ")";
            break;

        case 17:
            if (angle < -1.0 || angle > 1.0) {
                cout << "Error: acos input must be between -1 and 1.\n";
                return;
            }
            result = acos(angle) * 180.0 / PI;
            expression = "acos(" + formatNumber(angle) + ")";
            break;

        case 18:
            result = atan(angle) * 180.0 / PI;
            expression = "atan(" + formatNumber(angle) + ")";
            break;

        default:
            return;
    }

    finishCalculation(expression, result);
}

// Logarithms and exponential
void logarithmOperations(int choice) {
    double a = getNumber("Enter number: ");
    double result;
    string expression;

    switch (choice) {
        case 19:
            if (a <= 0.0) {
                cout << "Error: ln requires a positive number.\n";
                return;
            }
            result = log(a);
            expression = "ln(" + formatNumber(a) + ")";
            break;

        case 20:
            if (a <= 0.0) {
                cout << "Error: Log requires a positive number.\n";
                return;
            }
            result = log10(a);
            expression = "log10(" + formatNumber(a) + ")";
            break;

        case 21:
            result = exp(a);
            expression = "e^" + formatNumber(a);
            break;

        default:
            return;
    }

    finishCalculation(expression, result);
}

// Other mathematical functions
void otherOperations(int choice) {
    double a = getNumber("Enter number: ");
    double result;
    string expression;

    switch (choice) {
        case 22:
            result = fabs(a);
            expression = "abs(" + formatNumber(a) + ")";
            break;

        case 23:
            if (a < 0.0 || a != trunc(a) || a > 170.0) {
                cout << "Error: Enter a whole number from 0 to 170.\n";
                return;
            }

            result = 1.0;

            for (int i = 2; i <= static_cast<int>(a); ++i) {
                result *= i;
            }

            expression = formatNumber(a) + "!";
            break;

        case 24:
            result = round(a);
            expression = "round(" + formatNumber(a) + ")";
            break;

        case 25:
            result = floor(a);
            expression = "floor(" + formatNumber(a) + ")";
            break;

        case 26:
            result = ceil(a);
            expression = "ceil(" + formatNumber(a) + ")";
            break;

        case 27:
            result = a / 100.0;
            expression = formatNumber(a) + "%";
            break;

        default:
            return;
    }

    finishCalculation(expression, result);
}

// Memory menu
void memoryOperations() {
    cout << "\n========== MEMORY ==========\n";
    cout << "1. Store a number in memory\n";
    cout << "2. Recall memory\n";
    cout << "3. Add a number to memory\n";
    cout << "4. Clear memory\n";
    cout << "0. Back to main menu\n";

    int choice = getChoice();

    switch (choice) {
        case 1:
            memoryValue = getNumber("Enter value to store: ");
            memorySet = true;
            cout << "Value stored in memory.\n";
            break;

        case 2:
            if (memorySet) {
                cout << "Memory: " << formatNumber(memoryValue) << '\n';
            } else {
                cout << "Memory is empty.\n";
            }
            break;

        case 3: {
            double value = getNumber("Enter value to add: ");
            double updatedValue = memoryValue + value;

            if (!isfinite(updatedValue)) {
                cout << "Error: Memory result is outside the supported range.\n";
                break;
            }

            memoryValue = updatedValue;
            memorySet = true;
            cout << "Updated memory: " << formatNumber(memoryValue) << '\n';
            break;
        }

        case 4:
            memoryValue = 0.0;
            memorySet = false;
            cout << "Memory cleared.\n";
            break;

        case 0:
            break;

        default:
            cout << "Invalid memory option.\n";
    }
}

// Main menu
void showMenu() {
    cout << "\n";
    cout << "============================================\n";
    cout << "       ADVANCED SCIENTIFIC CALCULATOR\n";
    cout << "============================================\n";
    cout << " BASIC OPERATIONS\n";
    cout << " 1. Addition             2. Subtraction\n";
    cout << " 3. Multiplication       4. Division\n";
    cout << " 5. Modulus              6. Power (x^y)\n";
    cout << "--------------------------------------------\n";
    cout << " POWERS AND ROOTS\n";
    cout << " 7. Square Root          8. Cube Root\n";
    cout << " 9. Square              10. Cube\n";
    cout << "11. Reciprocal          12. Nth Root\n";
    cout << "--------------------------------------------\n";
    cout << " TRIGONOMETRY (DEGREES)\n";
    cout << "13. Sine                14. Cosine\n";
    cout << "15. Tangent             16. Inverse Sine\n";
    cout << "17. Inverse Cosine      18. Inverse Tangent\n";
    cout << "--------------------------------------------\n";
    cout << " LOGARITHMS\n";
    cout << "19. Natural Log (ln)    20. Log Base 10\n";
    cout << "21. Exponential (e^x)\n";
    cout << "--------------------------------------------\n";
    cout << " OTHER FUNCTIONS\n";
    cout << "22. Absolute Value      23. Factorial\n";
    cout << "24. Round               25. Floor\n";
    cout << "26. Ceiling             27. Percentage\n";
    cout << "--------------------------------------------\n";
    cout << "28. Show History        29. Clear History\n";
    cout << "30. Memory Functions\n";
    cout << " 0. Exit\n";
    cout << "============================================\n";
}

int main() {
    cout << setprecision(12);

    cout << "\nWelcome to the Advanced Scientific Calculator!\n";

    while (true) {
        showMenu();
        int choice = getChoice();

        if (choice == 0) {
            cout << "\nThank you for using the calculator!\n";
            cout << "Keep learning C++ and building projects!\n";
            break;
        }

        if (choice >= 1 && choice <= 6) {
            basicOperations(choice);
        } else if (choice >= 7 && choice <= 12) {
            powerRootOperations(choice);
        } else if (choice >= 13 && choice <= 18) {
            trigonometry(choice);
        } else if (choice >= 19 && choice <= 21) {
            logarithmOperations(choice);
        } else if (choice >= 22 && choice <= 27) {
            otherOperations(choice);
        } else {
            switch (choice) {
                case 28:
                    showHistory();
                    break;

                case 29:
                    history.clear();
                    cout << "Calculation history cleared.\n";
                    break;

                case 30:
                    memoryOperations();
                    break;

                default:
                    cout << "Invalid choice! Select 0 to 30.\n";
            }
        }
    }

    return 0;
}
