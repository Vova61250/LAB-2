#pragma once
#include "Worker.h"

class WorkerArray {
private:
    Worker* data;
    int size;

public:
    WorkerArray();
    WorkerArray(const WorkerArray& other);
    WorkerArray& operator=(const WorkerArray& other);
    ~WorkerArray();

    int getSize() const;

    Worker& at(int index);
    const Worker& at(int index) const;

    // Добавить работника на позицию [0..size]
    void addAtPosition(const Worker& worker, int position);

    // Удалить работника с позиции [0..size-1]
    void removeAtPosition(int position);

    // Отредактировать работника на позиции (полная замена)
    void editAtPosition(int position, const Worker& worker);

    // Сортировка по алфавиту по ФИО
    void sortByName();

    // Печать всех работников
    void printAll() const;
};
