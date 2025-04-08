#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int age;

public:
    // Конструктор за замовчуванням
    Person() : name(""), age(0) {}

    // Параметризований конструктор
    Person(const std::string& name, int age) : name(name), age(age) {}

    // Конструктор копіювання
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Person copy constructor\n";
    }

    // Конструктор переміщення
    Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {
        std::cout << "Person move constructor\n";
    }

    // Оператор копіювального присвоювання
    Person& operator=(const Person& other) {
        std::cout << "Person copy assignment\n";
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }

    // Оператор переміщення присвоювання
    Person& operator=(Person&& other) noexcept {
        std::cout << "Person move assignment\n";
        if (this != &other) {
            name = std::move(other.name);
            age = other.age;
        }
        return *this;
    }

    // Віртуальний деструктор
    virtual ~Person() {}

    // Друзі: оператори вводу/виводу
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "Name: " << p.name << ", Age: " << p.age;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Person& p) {
        std::cout << "Enter name: ";
        is >> p.name;
        std::cout << "Enter age: ";
        is >> p.age;
        return is;
    }
};

// Похідний клас - викладач
class Teacher : public Person {
private:
    std::string subject;

public:
    // Конструктор за замовчуванням
    Teacher() : Person(), subject("") {}

    // Параметризований конструктор
    Teacher(const std::string& name, int age, const std::string& subject)
        : Person(name, age), subject(subject) {
    }

    // Конструктор копіювання
    Teacher(const Teacher& other)
        : Person(other), subject(other.subject) {
        std::cout << "Teacher copy constructor\n";
    }

    // Конструктор переміщення
    Teacher(Teacher&& other) noexcept
        : Person(std::move(other)), subject(std::move(other.subject)) {
        std::cout << "Teacher move constructor\n";
    }

    // Оператор копіювального присвоювання
    Teacher& operator=(const Teacher& other) {
        std::cout << "Teacher copy assignment\n";
        if (this != &other) {
            Person::operator=(other);
            subject = other.subject;
        }
        return *this;
    }

    // Оператор переміщення присвоювання
    Teacher& operator=(Teacher&& other) noexcept {
        std::cout << "Teacher move assignment\n";
        if (this != &other) {
            Person::operator=(std::move(other));
            subject = std::move(other.subject);
        }
        return *this;
    }

    // Друзі: оператори вводу/виводу
    friend std::ostream& operator<<(std::ostream& os, const Teacher& t) {
        os << static_cast<const Person&>(t);
        os << ", Subject: " << t.subject;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Teacher& t) {
        is >> static_cast<Person&>(t);
        std::cout << "Enter subject: ";
        is >> t.subject;
        return is;
    }
};
