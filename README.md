# C++ Code Analyzer

A lightweight command-line tool for analyzing C++ source code, written in **C++23**.

Analyzer scans a C++ source file and reports useful statistics and information such as line counts, comments, TODOs, FIXME markers, includes, classes, and functions.

## Features

* Count total, blank, code, and comment lines
* Detect `TODO` comments
* Detect `FIXME` comments
* Count `#include` directives
* Detect classes
* Detect functions
* Verbose analysis mode
* JSON output
* Short and long command-line flags
* Flags can be combined in any order
* Prebuilt executables for Linux and Windows
* No external libraries or dependencies

## Getting Started

You **do not need to compile the project yourself**.

Prebuilt executables are included in the repository:

* `analyzer` — Linux executable
* `analyzer.exe` — Windows executable

### Linux

Make the executable executable if necessary:

```bash
chmod +x analyzer
```

Then run:

```bash
./analyzer foo.cpp
```

### Windows

Run from PowerShell or Command Prompt:

```powershell
.\analyzer.exe foo.cpp
```

## Usage

```text
analyzer [flags] <filename>
```

For example:

```bash
./analyzer foo.cpp
```

Example output:

```text
=== Code Analysis ===
Total lines:   25
Blank lines:   5
Code lines:    14
Comments:      6
TODOs:         2
FIXMEs:        1
Includes:      2
```

## Command-line options

| Short | Long        | Description            |
| ----- | ----------- | ---------------------- |
| `-h`  | `--help`    | Show help information  |
| `-j`  | `--json`    | Output results as JSON |
| `-v`  | `--verbose` | Show detailed analysis |
| `-?`  | —           | Show help information  |

Flags can be used in any order and combined together.

For example, all of these are valid:

```bash
./analyzer foo.cpp --json
./analyzer foo.cpp --verbose
./analyzer foo.cpp --json --verbose
./analyzer --verbose --json foo.cpp
./analyzer -j -v foo.cpp
```

## JSON Output

Use `-j` or `--json` to output the analysis as JSON:

```bash
./analyzer foo.cpp --json
```

Example output:

```json
{
  "total_lines": 25,
  "blank_lines": 5,
  "code_lines": 14,
  "comment_lines": 6,
  "todos": 2,
  "fixmes": 1,
  "includes": 2,
  "Classes": [
    "User"
  ],
  "Functions": [
    "main",
    "calculateScore"
  ]
}
```

An example of the actual JSON output is included in the repository as **`foo.json`**.

You can also use normal shell output redirection to save the result:

```bash
./analyzer foo.cpp --json > foo.json
```

## Verbose Mode

Use `-v` or `--verbose` to display additional information about detected classes and functions:

```bash
./analyzer foo.cpp --verbose
```

Verbose mode can be combined with JSON output:

```bash
./analyzer foo.cpp --json --verbose
```

## Building From Source

If you prefer to compile the project yourself, a C++23-compatible `g++` compiler is required.

### Linux

```bash
g++ -std=c++23 main.cpp analyzer.cpp -o analyzer
```

Run:

```bash
./analyzer foo.cpp
```

### Windows

```powershell
g++ -std=c++23 main.cpp analyzer.cpp -o analyzer.exe
```

Run:

```powershell
.\analyzer.exe foo.cpp
```

## Project Structure

```text
C++ Code Analyzer/
├── analyzer          # Prebuilt Linux executable
├── analyzer.exe      # Prebuilt Windows executable
├── analyzer.cpp      # Analysis implementation
├── analyzer.hpp      # Analysis declarations
├── foo.cpp           # Example C++ source file
├── foo.json          # Example JSON output
├── main.cpp          # CLI and argument handling
└── README.md
```

### Source Files

**`main.cpp`**

Handles command-line arguments, flags, and formatting of the analysis results.

**`analyzer.cpp`**

Contains the source-code analysis logic and regular expressions used to identify C++ structures.

**`analyzer.hpp`**

Contains the `AnalysisResult` structure and function declarations.

### Example Files

**`foo.cpp`**

A sample C++ source file used to demonstrate and test the analyzer.

**`foo.json`**

An example JSON report generated from `foo.cpp`.

## How It Works

Analyzer reads the source file line by line and uses regular expressions to identify various elements of the code.

It currently analyzes:

* Lines
* Blank lines
* Comments
* TODOs
* FIXMEs
* `#include` directives
* Classes
* Functions

The project intentionally uses a lightweight approach rather than a full C++ parser.

## Limitations

Because Analyzer uses regular expressions instead of a full C++ parser, it does not attempt to correctly parse every possible C++ construct.

Complex templates, macros, multiline declarations, lambdas, and other advanced syntax may not always be detected correctly.

The goal is to provide a **small, fast, and useful command-line analysis tool**, not to replace a compiler or full static-analysis framework.
## License

This project is licensed under the **MIT License**.

See the [`LICENSE`](LICENSE) file for the full license text.