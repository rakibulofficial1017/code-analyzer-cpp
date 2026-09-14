
#pragma once

#include <string>
#include <string_view>
#include <vector>

struct AnalysisResult {
    int total_lines = 0;
    int blank_lines = 0;
    int code_lines = 0;
    int comment_lines = 0;
    int todos = 0;
    int fixmes = 0;

    int includes = 0;

    std::vector<std::string> classes;
    std::vector<std::string> functions;
};

std::string_view strip_left(std::string_view str);

AnalysisResult analyze_file(const std::string& filename);

