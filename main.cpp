
#include "analyzer.hpp"

#include <iostream>
#include <string>

void print_help() {
    std::cout << "Usage: analyzer [flags] <filename>\n\n";

    std::cout << "Flags:\n";
    std::cout << "  -h, --help       Show this help message\n";
    std::cout << "  -j, --json       Output results as JSON\n";
    std::cout << "  -v, --verbose    Show detailed analysis\n";
    std::cout << "  -?               Show this help message\n";
}

int main(int argc, char* argv[]) {

    bool help = false;
    bool json = false;
    bool verbose = false;

    std::string filename;

    // Parse arguments
    for (int i = 1; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h" || arg == "-?") {
            help = true;
        }
        else if (arg == "--json" || arg == "-j") {
            json = true;
        }
        else if (arg == "--verbose" || arg == "-v") {
            verbose = true;
        }
        else if (!arg.empty() && arg[0] == '-') {
            std::cerr << "Unknown flag: " << arg << '\n';
            return 1;
        }
        else {
            if (!filename.empty()) {
                std::cerr << "Error: multiple filenames provided\n";
                return 1;
            }

            filename = arg;
        }
    }

    // --help / -h / -?
    if (help) {
        print_help();
        return 0;
    }

    // A filename is required
    if (filename.empty()) {
        std::cerr << "Error: no filename provided\n";
        std::cerr << "Use --help for usage information\n";
        return 1;
    }

    AnalysisResult result = analyze_file(filename);

    // JSON output
    if (json) {

        std::cout << "{\n";
        std::cout << "  \"total_lines\": " << result.total_lines << ",\n";
        std::cout << "  \"blank_lines\": " << result.blank_lines << ",\n";
        std::cout << "  \"code_lines\": " << result.code_lines << ",\n";
        std::cout << "  \"comment_lines\": " << result.comment_lines << ",\n";
        std::cout << "  \"todos\": " << result.todos << ",\n";
        std::cout << "  \"fixmes\": " << result.fixmes << ",\n";
        std::cout << "  \"includes\": " << result.includes;
        
        // Verbose JSON information
        if (verbose) {
            
            std::cout << ",\n";
            
            if (result.classes.empty()) {
                std::cout << "\n  \"Classes\": [],\n";
            }
            else {
                std::cout << "\n  \"Classes\": [\n";

                for (size_t i = 0; i < result.classes.size(); i++) {
                    std::cout << "    \"" << result.classes[i] << "\"";

                    if (i + 1 < result.classes.size()) {
                        std::cout << ",";
                    }

                    std::cout << "\n";
                }

                std::cout << "  ],\n";
            }
            
            
            if (result.functions.empty()) {
                std::cout << "\n  \"Functions\": [],\n";
            }
            else {
                std::cout << "\n  \"Functions\": [\n";

                for (size_t i = 0; i < result.functions.size(); i++) {
                    std::cout << "    \"" << result.functions[i] << "\"";

                    if (i + 1 < result.functions.size()) {
                        std::cout << ",";
                    }

                    std::cout << "\n";
                }

                std::cout << "  ]\n";
            }
        }
        
        std::cout << "\n}\n";
        return 0;
    }

    // Normal output
    std::cout << "=== Code Analysis ===\n";
    std::cout << "Total lines:   " << result.total_lines << '\n';
    std::cout << "Blank lines:   " << result.blank_lines << '\n';
    std::cout << "Code lines:    " << result.code_lines << '\n';
    std::cout << "Comments:      " << result.comment_lines << '\n';
    std::cout << "TODOs:         " << result.todos << '\n';
    std::cout << "FIXMEs:        " << result.fixmes << '\n';
    std::cout << "Includes:      " << result.includes << '\n';

    // Verbose output
    if (verbose) {

        std::cout << "\n=== Detailed Analysis ===\n";

        std::cout << "\nClasses:\n";

        if (result.classes.empty()) {
            std::cout << "  None\n";
        }
        else {
            for (const std::string& class_name : result.classes) {
                std::cout << "  " << class_name << '\n';
            }
        }

        std::cout << "\nFunctions:\n";

        if (result.functions.empty()) {
            std::cout << "  None\n";
        }
        else {
            for (const std::string& function_name : result.functions) {
                std::cout << "  " << function_name << '\n';
            }
        }
    }

    return 0;
}

