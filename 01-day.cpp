#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

auto allInvSummed(ifstream *input) -> vector<int>;

struct {
    bool operator()(int a, int b) const {
        return a > b;
    }
} MORE;

int main() {
    const constexpr char *FILE_NAME{
        "../inputs/dayOne"
    };

    ifstream input{
        FILE_NAME, ios::in
    };

    if (!input.good()) {
        cerr << "Error while opening input!" << endl;
        return -1;
    }

    vector<int> cals{allInvSummed(&input)};

    sort(cals.begin(),
         cals.end(),
         MORE);

    for (int i = 0; i < 3; ++i) {
        cout <<
            (i + 1) << ". " << cals.at(i)
        << endl;
    }

    return 0;
}

auto allInvSummed(ifstream *input) -> vector<int> {
    vector<int> calories;
    int calc { 0 };
    string value;

    while (getline(*input, value)) {
        if (value.empty()) {
            calories.push_back(calc),
            calc = 0;
        } else calc += stoi(value);
    }

    return calories;
}