#include "WorkerArray.h"
#include <iostream>

WorkerArray::WorkerArray() : data(nullptr), size(0) {
    std::cout << "[WorkerArray] Создан пустой массив\n";
}

WorkerArray::WorkerArray(const WorkerArray& other) : data(nullptr), size(0) {
    size = other.size;
    if (size > 0) {
        data = new Worker[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    std::cout << "[WorkerArray] Вызван конструктор копирования\n";
}

WorkerArray& WorkerArray::operator=(const WorkerArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        if (size > 0) {
            data = new Worker[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
        std::cout << "[WorkerArray] Оператор присваивания\n";
    }
    return *this;
}

WorkerArray::~WorkerArray() {
    delete[] data;
    std::cout << "[WorkerArray] Деструктор, массив очищен\n";
}

int WorkerArray::getSize() const {
    return size;
}

Worker& WorkerArray::at(int index) {
    if (index < 0 || index >= size) {
        throw WorkerException("Индекс вне диапазона (at).");
    }
    return data[index];
}

const Worker& WorkerArray::at(int index) const {
    if (index < 0 || index >= size) {
        throw WorkerException("Индекс вне диапазона (at const).");
    }
    return data[index];
}

void WorkerArray::addAtPosition(const Worker& worker, int position) {
    if (position < 0 || position > size) {
        throw WorkerException("Некорректная позиция при добавлении.");
    }

    Worker* newData = new Worker[size + 1];

    for (int i = 0; i < position; ++i) {
        newData[i] = data[i];
    }

    newData[position] = worker;

    for (int i = position; i < size; ++i) {
        newData[i + 1] = data[i];
    }

    delete[] data;
    data = newData;
    ++size;

    std::cout << "[WorkerArray] Добавлен работник на позицию " << position << "\n";
}

void WorkerArray::removeAtPosition(int position) {
    if (size == 0) {
        throw WorkerException("Невозможно удалить из пустого массива.");
    }
    if (position < 0 || position >= size) {
        throw WorkerException("Некорректная позиция при удалении.");
    }

    Worker* newData = nullptr;
    if (size - 1 > 0) {
        newData = new Worker[size - 1];
    }

    for (int i = 0; i < position; ++i) {
        newData[i] = data[i];
    }
    for (int i = position + 1; i < size; ++i) {
        newData[i - 1] = data[i];
    }

    delete[] data;
    data = newData;
    --size;

    std::cout << "[WorkerArray] Удалён работник с позиции " << position << "\n";
}

void WorkerArray::editAtPosition(int position, const Worker& worker) {
    if (position < 0 || position >= size) {
        throw WorkerException("Некорректная позиция при редактировании.");
    }
    data[position] = worker;
    std::cout << "[WorkerArray] Отредактирован работник на позиции " << position << "\n";
}

void WorkerArray::sortByName() {
    if (size < 2) return;

    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < size - 1; ++i) {
            if (data[i].getFullName() > data[i + 1].getFullName()) {
                Worker temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);

    std::cout << "[WorkerArray] Массив отсортирован по алфавиту\n";
}

void WorkerArray::printAll() const {
    if (size == 0) {
        std::cout << "Список работников пуст.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << i << ": " << data[i] << "\n";
    }
}
