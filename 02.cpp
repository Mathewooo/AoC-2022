#include <iostream>
#include <vector>
#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;

class DayTwo : Parser<TYPE> {
private:
    enum Res : int {
        WIN = 6, LOSE = 0, TIE = 3
    };

    static auto _getOutputs(const string *val,
                            const string &delimiter) -> pair<char, char> {
        const auto pos{val->find(delimiter)};
        return {
            val->substr(0, pos)
                        .c_str()[0],
            val->substr(pos + delimiter.length(),
                        val->size())
                        .c_str()[0]
        };
    }

public:
    explicit DayTwo(const char *fileName) : Parser(fileName) {}

    using Parser::cacheRes;

    TYPE editState() {
        int score{0};
        auto F = [&](const string &val) {
            auto vl = val;
            auto out = _getOutputs(
                    &vl," "
                    );
            auto opponent = out.first - 'A',
                 player = out.second - 'X';
            const auto ahead {(
                    player - opponent + 3
                    ) % 3};

            switch (ahead) {
                case 2: score += Res::LOSE;
                    break;
                case 1: score += Res::WIN;
                    break;
                case 0: score += Res::TIE;
                    break;
                default: break;
            }

            score += player + 1;
        };
        { edit(F); }
        return score;
    }

    TYPE succeedingState() {
        int score{0};
        auto F = [&](const string &val) {
            auto vl = val;
            auto out = _getOutputs(
                    &vl," "
            );

            int opponent = out.first - 'A',
                player = out.second - 'X';

            switch (player) {
                case 2: player = (
                        opponent + 1
                        ) % 3 + Res::WIN;
                    break;
                case 1: player
                    = opponent + Res::TIE;
                    break;
                case 0: player = (
                        opponent + 2
                        ) % 3 + Res::LOSE;
                    break;
                default: break;
            }

            score += player + 1;
        };
        { edit(F); }
        return score;
    }

    void firstFragment() override {
        cout << "First Fragment:"
             << endl << endl;

        cout << "Total: " << *getCache()
             << endl
             << endl;
    }

    void secondFragment() override {
        cout << "Second Fragment:"
             << endl << endl;

        cout << "Total: " << *getCache()
             << endl;
    }
};

int main() {
    auto main = DayTwo("../inputs/dayTwo");
    main
      .cacheRes(main
      .editState());
    main.firstFragment();
    main
      .cacheRes(main
      .succeedingState());
    main.secondFragment();
    return EXIT_SUCCESS;
}