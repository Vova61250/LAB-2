#include <iostream>
#include <limits>
#include <clocale>

#include "WorkerArray.h"
#include "TextProcessor.h"

int getIntFromUser(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Попробуйте ещё раз.\n";
        }
    }
}

void menu() {
    WorkerArray workers;
    bool running = true;

    while (running) {
        std::cout << "\n===== МЕНЮ =====\n";
        std::cout << "1. Добавить работника\n";
        std::cout << "2. Удалить работника\n";
        std::cout << "3. Редактировать работника\n";
        std::cout << "4. Показать всех работников\n";
        std::cout << "5. Показать работников со стажем больше заданного\n";
        std::cout << "6. Обработать текстовый файл (предложения без запятых)\n";
        std::cout << "0. Выход\n";

        int choice = getIntFromUser("Выберите пункт меню: ");

        try {
            switch (choice) {
            case 1: {
                std::cout << "=== Добавление работника ===\n";
                Worker w;
                std::cin >> w;

                int pos = workers.getSize();
                std::cout << "Введите позицию для вставки (0.." << pos << "): ";
                pos = getIntFromUser("");

                workers.addAtPosition(w, pos);
                workers.sortByName();
                break;
            }
            case 2: {
                std::cout << "=== Удаление работника ===\n";
                int size = workers.getSize();
                if (size == 0) {
                    std::cout << "Список пуст, удалять нечего.\n";
                    break;
                }
                workers.printAll();
                int pos = getIntFromUser("Введите позицию для удаления: ");
                workers.removeAtPosition(pos);
                break;
            }
            case 3: {
                std::cout << "=== Редактирование работника ===\n";
                int size = workers.getSize();
                if (size == 0) {
                    std::cout << "Список пуст.\n";
                    break;
                }
                workers.printAll();
                int pos = getIntFromUser("Введите позицию для редактирования: ");
                Worker w;
                std::cin >> w;
                workers.editAtPosition(pos, w);
                workers.sortByName();
                break;
            }
            case 4: {
                std::cout << "=== Список всех работников ===\n";
                workers.printAll();
                break;
            }
            case 5: {
                std::cout << "=== Работники со стажем больше заданного ===\n";
                int currentYear   = getIntFromUser("Введите текущий год: ");
                int minExperience = getIntFromUser("Введите минимальный стаж (в годах): ");

                bool found = false;
                int size = workers.getSize();
                for (int i = 0; i < size; ++i) {
                    int exp = workers.at(i).getExperience(currentYear);
                    if (exp > minExperience) {
                        if (!found) {
                            std::cout << "Работники со стажем больше "
                                      << minExperience << " лет:\n";
                        }
                        std::cout << workers.at(i)
                                  << " (стаж: " << exp << " лет)\n";
                        found = true;
                    }
                }
                if (!found) {
                    std::cout << "Нет работников с таким стажем.\n";
                }
                break;
            }
            case 6: {
                std::cout << "=== Предложения без запятых из файла ===\n";
                std::string filename;
                std::cout << "Введите имя файла (например, input.txt): ";
                std::getline(std::cin, filename);
                if (filename.empty()) {
                    std::getline(std::cin, filename);
                }
                printSentencesWithoutCommas(filename);
                break;
            }
            case 0:
                running = false;
                break;

            default:
                std::cout << "Неизвестный пункт меню. Попробуйте ещё раз.\n";
                break;
            }
        }
        catch (const WorkerException& ex) {
            std::cout << "Ошибка (WorkerException): " << ex.what() << "\n";
        }
        catch (const std::exception& ex) {
            std::cout << "Стандартное исключение: " << ex.what() << "\n";
        }
        catch (...) {
            std::cout << "Неизвестная ошибка.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "");
    menu();
    return 0;
}