#ifndef IMPLEMENTATION_FILETOWORDS_HPP
#define IMPLEMENTATION_FILETOWORDS_HPP
#include <string>
#include <vector>
#include <filesystem>

#include "utils.hpp"

class Scanner {
public:
    explicit Scanner(std::filesystem::path inputPath);


    error_type tokenize(std::vector<std::string>& words);

    error_type tokenize(std::vector<std::string>& words,
        const std::filesystem::path& outputFile);

    ~Scanner() = default;

private:

    static std::string readWord(std::istream& in);

    std::filesystem::path inputPath_;
};

#endif //IMPLEMENTATION_FILETOWORDS_HPP