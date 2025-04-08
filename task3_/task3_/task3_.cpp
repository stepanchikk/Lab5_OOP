#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Person {
protected:
    std::string name;
    int age;

public:
    Person() : name(""), age(0) {}

    Person(const std::string& name, int age) : name(name), age(age) {}

    Person(const Person& other) : name(other.name), age(other.age) {}//Конструктор копіюванн

    Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {}//Конструктор перенесення

    Person& operator=(const Person& other) { //Оператори присвоєння
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }

    Person& operator=(Person&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            age = other.age;
        }
        return *this;
    }

    virtual ~Person() {}

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

class Teacher : public Person {
private:
    std::string subject;

public:
    Teacher() : Person(), subject("") {}

    Teacher(const std::string& name, int age, const std::string& subject)
        : Person(name, age), subject(subject) {
    }

    Teacher(const Teacher& other)
        : Person(other), subject(other.subject) {
        std::cout << "[INFO] Copy constructor called\n";
    }

    Teacher(Teacher&& other) noexcept
        : Person(std::move(other)), subject(std::move(other.subject)) {
        std::cout << "[INFO] Move constructor called\n";
    }

    Teacher& operator=(const Teacher& other) {
        if (this != &other) {
            Person::operator=(other);
            subject = other.subject;
        }
        std::cout << "[INFO] Copy assignment operator called\n";
        return *this;
    }

    Teacher& operator=(Teacher&& other) noexcept {
        if (this != &other) {
            Person::operator=(std::move(other));
            subject = std::move(other.subject);
        }
        std::cout << "[INFO] Move assignment operator called\n";
        return *this;
    }

    ~Teacher() {}

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

std::string getRandomName() {
    std::string names[] = { "Olena", "Ivan", "Taras", "Nina", "Kateryna" };
    return names[rand() % 5];
}

std::string getRandomSubject() {
    std::string subjects[] = { "Math", "Physics", "History", "Biology", "Informatics" };
    return subjects[rand() % 5];
}

int getRandomAge() {
    return 25 + rand() % 35;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int choice;
    std::cout << "Choose option:\n";
    std::cout << "1 - Enter teacher manually\n";
    std::cout << "2 - Generate random teacher\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    Teacher teacher;

    if (choice == 1) {
        std::cin >> teacher;
    }
    else if (choice == 2) {
        teacher = Teacher(getRandomName(), getRandomAge(), getRandomSubject());
    }
    else {
        std::cout << "Invalid choice. Exiting...\n";
        return 1;
    }

    std::cout << "\nTeacher info:\n" << teacher << "\n";

    // Демонстрація з повідомленнями:
    std::cout << "\n--- Copying teacher ---\n";
    Teacher t_copy = teacher;

    std::cout << "\n--- Moving teacher ---\n";
    Teacher t_move = std::move(t_copy);

    std::cout << "\n--- Copy assigning teacher ---\n";
    Teacher t_assign;
    t_assign = teacher;

    std::cout << "\n--- Move assigning teacher ---\n";
    Teacher t_assign_move;
    t_assign_move = std::move(t_assign);

    std::cout << "\nDone.\n";

    return 0;
}
