#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class WorkerException : public std::exception {
private:
    std::string message;
public:
    explicit WorkerException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Worker {
private:
    std::string fullName;   // ФИО
    std::string position;   // Должность
    int hireYear;           // Год поступления на работу

public:
    Worker();
    Worker(const std::string& fullName,
           const std::string& position,
           int hireYear);
    Worker(const Worker& other);
    Worker& operator=(const Worker& other);
    ~Worker();

    const std::string& getFullName() const;
    void setFullName(const std::string& name);

    const std::string& getPosition() const;
    void setPosition(const std::string& pos);

    int getHireYear() const;
    void setHireYear(int year);

    int getExperience(int currentYear) const;

    friend std::ostream& operator<<(std::ostream& os, const Worker& w);
    friend std::istream& operator>>(std::istream& is, Worker& w);
};

