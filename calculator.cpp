#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int choice;
    double x;

    cout << "Scientific Calculator\n";
    cout << "1. Square root\n";
    cout << "2. Power\n";
    cout << "3. Sine (degrees)\n";
    cout << "4. Logarithm (base 10)\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "Enter number: ";
            cin >> x;
            if (x >= 0)
                cout << "Result: " << sqrt(x);
            else
                cout << "Invalid input";
            break;

        case 2: {
            double y;
            cout << "Enter base and exponent: ";
            cin >> x >> y;
            cout << "Result: " << pow(x, y);
            break;
        }

        case 3:
            cout << "Enter angle in degrees: ";
            cin >> x;
            cout << "Result: " << sin(x * acos(-1.0) / 180.0);
            break;

        case 4:
            cout << "Enter positive number: ";
            cin >> x;
            if (x > 0)
                cout << "Result: " << log10(x);
            else
                cout << "Invalid input";
            break;

        default:
            cout << "Invalid choice";
    }

    cout << endl;
    return 0;
}