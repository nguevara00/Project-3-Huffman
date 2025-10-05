//Nick Guevara
//Project 3 Part 1
//CS 315
//10-5-2025

#include "Scanner.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"

Scanner::Scanner(std::filesystem::path inputPath) {
    this->inputPath_ = inputPath;
}
error_type Scanner::tokenize(std::vector<std::string>& words) {
    namespace fs = std::filesystem;

    if (inputPath_.has_parent_path() && directoryExists(inputPath_.parent_path().string()) != NO_ERROR) {
        return DIR_NOT_FOUND;
    }

    if (regularFileExistsAndIsAvailable(inputPath_.string()) != NO_ERROR) {
        return FILE_NOT_FOUND;
    }

    std::ifstream inFile(inputPath_.string());
    if (!inFile.is_open()) {
        return UNABLE_TO_OPEN_FILE;
    }

    std::string token;
    while (!(token = readWord(inFile)).empty()) {
        words.push_back(token);
    }
    inFile.close();
    return NO_ERROR;
}

error_type Scanner::tokenize(std::vector<std::string>& words, const std::filesystem::path& outputFile) {
    error_type status = tokenize(words);
    if (status != NO_ERROR) {
        return status;
    }

    return writeVectorToFile(outputFile.string(), words);
}

std::string Scanner::readWord(std::istream& in) {
    std::string token;
    char ch;

    while (in.get(ch)) {
        ch = std::tolower(static_cast<unsigned char>(ch));
        if (ch >= 'a' && ch <= 'z') {
            token += ch;
            break;
        }
    }

    if (token.empty()) {
        return "";
    }

    while(in.get(ch)) {
        ch = std::tolower(static_cast<unsigned char>(ch));

        if (ch >= 'a' && ch <= 'z') {
            token += ch;
        }

        else if (ch == '\'' && !token.empty()) {
            char nextCh = in.peek();
            nextCh = std::tolower(static_cast<unsigned char>(nextCh));
            if (nextCh >= 'a' && nextCh <= 'z') {
                token += '\'';
            }
            else {          
                break;
            }
        }
        else {
            break;
        }
    }
    return token;
}