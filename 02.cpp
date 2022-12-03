#include <iostream>
#include <vector>
#include "parser/Parser.hpp"

using namespace std;

class DayTwo : Parser<int> {
    public:
        explicit DayTwo(const char *fileName): Parser(fileName) {}

        int editState() override {
            string value, delimiter{" "};
            int score{0};
            function<void(string)> F = [&](const string& val){
                auto vl = val;

                const auto pos{
                    vl.find(delimiter)
                };
                const auto opponent{
                    vl.substr(0, pos)
                    }, player{
                    vl.erase(0, pos + delimiter.length())
                };

                auto first = opponent.c_str()[0] - 'A';
                auto second = player.c_str()[0] - 'X';
                score += second + 1 + 3 * (
                        (second - first + 3 + 1) % 3);
            };
            edit(F);
            return score;
        }

        void result() override {
            cout << DayTwo::editState() << endl;
        }
};

int main() {
    auto dayTwo = DayTwo("../inputs/dayTwo");
    dayTwo.result();
    return 0;
}