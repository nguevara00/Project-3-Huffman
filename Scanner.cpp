#include "Scanner.hpp"
#include <iostream>
#include <fstream>
#include <cctype>
#include "utils.hpp"

Scanner::Scanner(std::filesystem::path inputPath)
    : inputPath_(std::move(inputPath)) {}

error_type Scanner::tokenize(std::vector<std::string>& words) {
    if (error_type status = regularFileExistsAndIsAvailable(inputPath_.string()); status != NO_ERROR) {
        return status;
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
    
    //look for the start of the token
    while (in.get(ch)) {
        unsigned char c = static_cast<unsigned char>(ch);
        if (c > 127) continue;
        ch = std::tolower(c);
        if (ch >= 'a' && ch <= 'z') {
            token += ch;
            break;
        }
    }
    //if a token cannot be found (eof)
    if (token.empty()) {
        return "";
    }

    //consume the rest of the token with internal apostrophes
    while (in.get(ch)) {
        unsigned char c = static_cast<unsigned char>(ch);
        if (c > 127) break; // non-ASCII stops token
        ch = std::tolower(c);

        if (ch >= 'a' && ch <= 'z') {
            token += ch;
        }
        else if (ch == '\'' && !token.empty()) {
            char nextCh = in.peek();
            if (nextCh != EOF && std::isalpha(static_cast<unsigned char>(nextCh))) {
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

    // Drop trailing apostrophe if any
    if (!token.empty() && token.back() == '\'') {
        token.pop_back();
    }

    return token;
}
