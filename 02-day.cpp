#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;

auto getScore(ifstream *input) -> int;

int main() {
    const constexpr char *FILE_NAME{"../inputs/dayTwo"};

    ifstream input{FILE_NAME, ios::in};

    if (!input.good()) {
        cerr << "Error while opening input!" << endl;
        return -1;
    }

    cout << getScore(&input);

    return 0;
}

auto getScore(ifstream *input) -> int {
    string value, delimiter{" "};
    int score{0};

    while (getline(*input, value)) {
        const auto pos{value.find(delimiter)};
        const auto opponent{value.substr(0, pos)},
                   player{value.erase(0, pos + delimiter.length())};

        auto first = opponent.c_str()[0] - 'A';
        auto second = player.c_str()[0] - 'X';
        score += second + 1 + 3 * (
                (second - first + 3 + 1) % 3);
    }

    return score;
}