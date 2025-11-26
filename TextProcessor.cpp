#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>

void printSentencesWithoutCommas(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << filename << "\n";
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    std::string currentSentence;
    bool hasComma = false;

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        currentSentence.push_back(c);
        if (c == ',') {
            hasComma = true;
        }

        if (c == '.' || c == '!' || c == '?') {
            size_t start = currentSentence.find_first_not_of(" \n\r\t");
            size_t end   = currentSentence.find_last_not_of(" \n\r\t");

            if (start != std::string::npos && end != std::string::npos) {
                std::string trimmed = currentSentence.substr(start, end - start + 1);
                if (!hasComma) {
                    std::cout << trimmed << "\n";
                }
            }

            currentSentence.clear();
            hasComma = false;
        }
    }
}
