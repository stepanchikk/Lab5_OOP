#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Клас Pair — пара чисел
class Pair {
protected:
    double a, b;

public:
    Pair(double a = 0, double b = 0) : a(a), b(b) {}

    void setA(double value) { a = value; }
    void setB(double value) { b = value; }

    double getA() const { return a; }
    double getB() const { return b; }

    double product() const {
        return a * b;
    }

    void inputFromKeyboard() {
        cout << "Введіть перше число (a): ";
        cin >> a;
        cout << "Введіть друге число (b): ";
        cin >> b;
    }

    void inputRandomly() {
        a = rand() % 100 + 1;
        b = rand() % 100 + 1;
        cout << "Згенеровані випадкові значення: a = " << a << ", b = " << b << endl;
    }

    void print() const {
        cout << "a = " << a << ", b = " << b << endl;
    }
};

// Похідний клас RightAngled — прямокутний трикутник
class RightAngled : public Pair {
public:
    RightAngled(double a = 0, double b = 0) : Pair(a, b) {}

    double hypotenuse() const {
        return sqrt(a * a + b * b);
    }

    double area() const {
        return 0.5 * a * b;
    }

    void printInfo() const {
        cout << "Катети: a = " << a << ", b = " << b << endl;
        cout << "Гіпотенуза: " << hypotenuse() << endl;
        cout << "Площа: " << area() << endl;
    }
};

int main() {
	setlocale(LC_ALL, "ukrainian"); // Встановлення української локалі
    srand(time(0)); // ініціалізація генератора випадкових чисел

    RightAngled triangle;

    int choice;
    cout << "Оберіть спосіб введення даних:" << endl;
    cout << "1 — Ввести вручну" << endl;
    cout << "2 — Згенерувати випадково" << endl;
    cout << "Ваш вибір: ";
    cin >> choice;

    if (choice == 1) {
        triangle.inputFromKeyboard();
    }
    else if (choice == 2) {
        triangle.inputRandomly();
    }
    else {
        cout << "Невірний вибір. Завершення програми." << endl;
        return 1;
    }

    cout << "\n--- Результати ---" << endl;
    triangle.printInfo();

    return 0;
}
