#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class Person {
protected:
    std::string name;
    int age;

public:
    Person() : name(""), age(0) {}
    Person(const std::string& name, int age) : name(name), age(age) {}

    // Конструктор копіювання
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "[INFO] Person: Copy constructor called\n";
    }

    // Конструктор перенесення
    Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {
        std::cout << "[INFO] Person: Move constructor called\n";
    }

    // Оператор копіювального присвоєння
    Person& operator=(const Person& other) {
        std::cout << "[INFO] Person: Copy assignment operator called\n";
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }

    // Оператор перенесення
    Person& operator=(Person&& other) noexcept {
        std::cout << "[INFO] Person: Move assignment operator called\n";
        if (this != &other) {
            name = std::move(other.name);
            age = other.age;
        }
        return *this;
    }

    virtual ~Person() {}

    // Методи для введення і виведення
    virtual void input(std::istream& is) {
        std::cout << "Enter name: ";
        is >> name;
        std::cout << "Enter age: ";
        is >> age;
    }

    virtual void print(std::ostream& os) const {
        os << "Name: " << name << ", Age: " << age;
    }
};

class Teacher : public Person {
private:
    std::string subject;

public:
    Teacher() : Person(), subject("") {}
    Teacher(const std::string& name, int age, const std::string& subject)
        : Person(name, age), subject(subject) {}

    // Конструктор копіювання
    Teacher(const Teacher& other)
        : Person(other), subject(other.subject) {
        std::cout << "[INFO] Teacher: Copy constructor called\n";
    }

    // Конструктор перенесення
    Teacher(Teacher&& other) noexcept
        : Person(std::move(other)), subject(std::move(other.subject)) {
        std::cout << "[INFO] Teacher: Move constructor called\n";
    }

    // Оператор копіювального присвоєння
    Teacher& operator=(const Teacher& other) {
        std::cout << "[INFO] Teacher: Copy assignment operator called\n";
        if (this != &other) {
            Person::operator=(other);
            subject = other.subject;
        }
        return *this;
    }

    // Оператор перенесення
    Teacher& operator=(Teacher&& other) noexcept {
        std::cout << "[INFO] Teacher: Move assignment operator called\n";
        if (this != &other) {
            Person::operator=(std::move(other));
            subject = std::move(other.subject);
        }
        return *this;
    }

    void input(std::istream& is) override {
        Person::input(is);
        std::cout << "Enter subject: ";
        is >> subject;
    }

    void print(std::ostream& os) const override {
        Person::print(os);
        os << ", Subject: " << subject;
    }
};

// Зовнішні оператори без friend
std::ostream& operator<<(std::ostream& os, const Person& p) {
    p.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Person& p) {
    p.input(is);
    return is;
}

// Функція генерації випадкових імен та предметів
std::string getRandomName() {
    std::string names[] = {"Ivan", "Oksana", "Petro", "Maria", "Andriy"};
    return names[rand() % 5];
}

std::string getRandomSubject() {
    std::string subjects[] = {"Math", "History", "Physics", "Literature", "IT"};
    return subjects[rand() % 5];
}

int getRandomAge() {
    return 25 + rand() % 40; // від 25 до 64
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<Teacher> teachers;
    int count;
    std::cout << "How many teachers? ";
    std::cin >> count;

    int choice;
    std::cout << "1 - Manual input\n2 - Random generation\nChoice: ";
    std::cin >> choice;

    for (int i = 0; i < count; ++i) {
        if (choice == 1) {
            Teacher t;
            std::cin >> t;
            teachers.push_back(t);
        } else {
            Teacher t(getRandomName(), getRandomAge(), getRandomSubject());
            teachers.push_back(std::move(t));
        }
    }

    std::cout << "\nTeachers list:\n";
    for (const auto& t : teachers) {
        std::cout << t << std::endl;
    }

    return 0;
}