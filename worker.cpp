#include "Worker.h"
#include <limits>

// ===== Реализация Worker =====

Worker::Worker() : fullName(""), position(""), hireYear(0) {
    std::cout << "[Worker] Вызван конструктор по умолчанию\n";
}

Worker::Worker(const std::string& fullName,
               const std::string& position,
               int hireYear)
    : fullName(fullName), position(position), hireYear(hireYear) {
    std::cout << "[Worker] Вызван конструктор с параметрами для: "
              << this->fullName << "\n";

    if (hireYear <= 0) {
        throw WorkerException("Год поступления должен быть положительным.");
    }
}

Worker::Worker(const Worker& other)
    : fullName(other.fullName),
      position(other.position),
      hireYear(other.hireYear) {
    std::cout << "[Worker] Вызван конструктор копирования для: "
              << fullName << "\n";
}

Worker& Worker::operator=(const Worker& other) {
    if (this != &other) {
        fullName = other.fullName;
        position = other.position;
        hireYear = other.hireYear;
        std::cout << "[Worker] Оператор присваивания для: "
                  << fullName << "\n";
    }
    return *this;
}

Worker::~Worker() {
    std::cout << "[Worker] Вызван деструктор для: "
              << fullName << "\n";
}

const std::string& Worker::getFullName() const {
    return fullName;
}

void Worker::setFullName(const std::string& name) {
    if (name.empty()) {
        throw WorkerException("ФИО не может быть пустым.");
    }
    fullName = name;
}

const std::string& Worker::getPosition() const {
    return position;
}

void Worker::setPosition(const std::string& pos) {
    if (pos.empty()) {
        throw WorkerException("Должность не может быть пустой.");
    }
    position = pos;
}

int Worker::getHireYear() const {
    return hireYear;
}

void Worker::setHireYear(int year) {
    if (year <= 0) {
        throw WorkerException("Год поступления должен быть положительным.");
    }
    hireYear = year;
}

int Worker::getExperience(int currentYear) const {
    if (currentYear < hireYear) {
        throw WorkerException("Текущий год меньше года поступления на работу.");
    }
    return currentYear - hireYear;
}

std::ostream& operator<<(std::ostream& os, const Worker& w) {
    os << "ФИО: " << w.fullName
       << ", Должность: " << w.position
       << ", Год поступления: " << w.hireYear;
    return os;
}

std::istream& operator>>(std::istream& is, Worker& w) {
    std::string name;
    std::string pos;
    int year;

    std::cout << "Введите ФИО работника: ";
    std::getline(is, name);
    if (name.empty()) {
        std::getline(is, name);
    }

    std::cout << "Введите должность: ";
    std::getline(is, pos);

    std::cout << "Введите год поступления на работу: ";
    is >> year;
    if (!is) {
        throw WorkerException("Ошибка ввода года. Ожидалось целое число.");
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    w.setFullName(name);
    w.setPosition(pos);
    w.setHireYear(year);

    return is;
}
