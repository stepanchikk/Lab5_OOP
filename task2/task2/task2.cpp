#include <iostream>    
#include <vector>      
#include <ctime>      
#include <cstdlib>    

using namespace std;    

class Wheel {
private:
    float radius;       // Приватне поле — радіус колеса
public:
    // Конструктор з параметром за замовчуванням (можна не передавати нічого)
    Wheel(float r = 0) : radius(r) {}

    // Метод для вводу радіуса вручну або випадковим чином
    void input(bool random) {
        if (random) {
            radius = 10 + rand() % 21; // Генерація випадкового числа від 10 до 30
        }
        else {
            cout << "Введіть радіус колеса: ";
            cin >> radius;             // Ввід з клавіатури
        }
    }

    // Метод для виводу радіуса
    void display() const {
        cout << "Радіус колеса: " << radius << " см\n";
    }
};

// Абстрактний клас Vehicle (Транспортний засіб)
class Vehicle {
public:
    virtual void input(bool random) = 0;   // Ввід
    virtual void display() const = 0;      // Вивід
    virtual ~Vehicle() {}                  // Віртуальний деструктор (для правильного видалення)
};

// Клас Bicycle (успадковує Vehicle) — Велосипед має 2 колеса
class Bicycle : public Vehicle {
private:
    vector<Wheel> wheels; // Композиція — велосипед містить 2 колеса (масив об'єктів Wheel)
public:
    // Конструктор, створюємо 2 колеса
    Bicycle() : wheels(2) {}

    // Реалізація методу введення
    void input(bool random) override {
        cout << "\n--- Велосипед ---\n";
        for (int i = 0; i < 2; ++i) {
            cout << "Колесо " << i + 1 << ":\n";
            wheels[i].input(random); // Вводимо дані для кожного колеса
        }
    }

    // Реалізація методу виведення
    void display() const override {
        cout << "Велосипед з 2 колесами:\n";
        for (const auto& wheel : wheels) {
            wheel.display(); // Виводимо кожне колесо
        }
    }
};

// Клас Car (успадковує Vehicle) — Автомобіль має 4 колеса
class Car : public Vehicle {
private:
    vector<Wheel> wheels; // Композиція — автомобіль містить 4 колеса
public:
    // Конструктор, створюємо 4 колеса
    Car() : wheels(4) {}

    // Реалізація методу введення
    void input(bool random) override {
        cout << "\n--- Автомобіль ---\n";
        for (int i = 0; i < 4; ++i) {
            cout << "Колесо " << i + 1 << ":\n";
            wheels[i].input(random); // Вводимо дані для кожного колеса
        }
    }

    // Реалізація методу виведення
    void display() const override {
        cout << "Автомобіль з 4 колесами:\n";
        for (const auto& wheel : wheels) {
            wheel.display(); // Виводимо кожне колесо
        }
    }
};

// Головна функція
int main() {
	setlocale(LC_ALL, "ukr"); 
    srand(time(0)); 

    int choice;    
    cout << "Оберіть тип введення даних:\n";
    cout << "1 — Ввести вручну\n";
    cout << "2 — Згенерувати випадково\n";
    cout << "Ваш вибір: ";
    cin >> choice;  

    bool useRandom = (choice == 2); 

    Bicycle bike;   // Створюємо об'єкт велосипеда
    Car car;        // Створюємо об'єкт автомобіля

    bike.input(useRandom);  // Вводимо дані для велосипеда
    car.input(useRandom);   // Вводимо дані для автомобіля

    cout << "\nРезультати:\n";
    bike.display();         // Виводимо дані велосипеда
    car.display();          // Виводимо дані автомобіля

    return 0;               // Завершення програми
}
