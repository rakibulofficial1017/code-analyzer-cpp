#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

// TODO: replace this with a proper configuration system
const int MAX_USERS = 100;

class User {
public:
    string name;
    int age;

    User(string n, int a) {
        name = n;
        age = a;
    }

    void printInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

// FIXME: this function is way too long
int calculateScore(const vector<int>& scores) {
    int total = 0;
    int unusedVariable = 42;

    for (int score : scores) {
        total += score;
    }

    double average = 0;

    if (!scores.empty()) {
        average = static_cast<double>(total) / scores.size();
    }

    cout << "Total: " << total << endl;
    cout << "Average: " << average << endl;

    if (average >= 90) {
        cout << "Grade: A*" << endl;
    } else if (average >= 80) {
        cout << "Grade: A" << endl;
    } else if (average >= 70) {
        cout << "Grade: B" << endl;
    } else if (average >= 60) {
        cout << "Grade: C" << endl;
    } else {
        cout << "Grade: F" << endl;
    }

    if (total > 500) {
        cout << "Excellent total!" << endl;
    }

    return total;
}

void loadUsers(const string& filename, vector<User>& users) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Could not open file!" << endl;
        return;
    }

    string name;
    int age;

    while (file >> name >> age) {
        users.emplace_back(name, age);
    }
}

void findUser(const vector<User>& users, const string& target) {
    for (const auto& user : users) {
        if (user.name == target) {
            cout << "Found user: " << user.name << endl;
            return;
        }
    }

    cout << "User not found." << endl;
}

int main() {
    vector<int> scores = {
        95, 87, 76, 92, 64, 88
    };

    vector<User> users;

    loadUsers("users.txt", users);

    calculateScore(scores);

    findUser(users, "Rakibul");

    // TODO: add sorting
    // TODO: add JSON output

    return 0;
}