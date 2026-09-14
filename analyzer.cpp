
#include "analyzer.hpp"

#include <fstream>
#include <regex>
#include <string>

std::string_view strip_left(std::string_view str) {
    size_t start = str.find_first_not_of(" \t\n\r");

    return (start == std::string_view::npos)
        ? ""
        : str.substr(start);
}

AnalysisResult analyze_file(const std::string& filename) {

    AnalysisResult result;

    std::ifstream myFile(filename);

    if (!myFile.is_open()) {
        return result;
    }

    // Line analysis
    const std::regex blank_regex(
        R"(^\s*$)"
    );

    const std::regex comment_regex(
        R"(^\s*//)"
    );

    const std::regex todo_regex(
        R"(^\s*//\s*TODO\b)"
    );

    const std::regex fixme_regex(
        R"(^\s*//\s*FIXME\b)"
    );

    // C++ structure
    const std::regex include_regex(
        R"(^\s*#include\s*[<"]([^>"]+)[>"])"
    );

    const std::regex class_regex(
        R"(^\s*class\s+([A-Za-z_][A-Za-z0-9_]*))"
    );

    const std::regex function_regex(
        R"(^\s*(?:[\w:<>]+(?:\s*[*&])?\s+)+([A-Za-z_][A-Za-z0-9_]*)\s*\([^;]*\)\s*(?:const)?\s*(?:\{|$))"
    );

    std::string line;
    std::smatch match;

    while (std::getline(myFile, line)) {

        result.total_lines++;

        // Blank line
        if (std::regex_match(line, blank_regex)) {
            result.blank_lines++;
            continue;
        }

        // Single-line comment
        if (std::regex_search(line, comment_regex)) {

            result.comment_lines++;

            if (std::regex_search(line, todo_regex)) {
                result.todos++;
            }

            if (std::regex_search(line, fixme_regex)) {
                result.fixmes++;
            }

            continue;
        }

        // Non-comment line = code
        result.code_lines++;

        // #include
        if (std::regex_search(line, match, include_regex)) {
            result.includes++;
        }

        // class
        if (std::regex_search(line, match, class_regex)) {
            result.classes.push_back(match[1].str());
        }

        // function
        if (std::regex_search(line, match, function_regex)) {
            result.functions.push_back(match[1].str());
        }
    }

    return result;
}

