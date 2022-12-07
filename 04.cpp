#include <regex>
#include "parser/Parser.hpp"
#include "utilities/Utils.hpp"

using namespace std;
using namespace Regex;

typedef pair<int, int> PAIR;
typedef vector<pair<PAIR, PAIR>> TYPE;

class DayFour : Parser<TYPE> {
    private:
        static auto _getOutputs(const string *val,
                                const string &delimiter) -> pair<string, string> {
            const auto pos{val->find(delimiter)};
            return {
                    val->substr(0, pos),
                    val->substr(pos + delimiter.length(),
                                val->size())
            };
        }

        inline static int _toInt(const vector<string> &v,
                                 int index) {
            return stoi(v.at(index));
        }

        static auto _returnPair(
                    const pair<string, string> &pr
                ) -> pair<PAIR, PAIR> {
            pair<PAIR, PAIR> pair;
            const auto reg {regex{"\\-+"}};
            auto f {split(pr.first, reg)},
                 s {split(pr.second, reg)};
            pair.first = {
                    _toInt(f, 0),
                    _toInt(f, 1)
            }; pair.second = {
                    _toInt(s, 0),
                    _toInt(s, 1)
            };
            return pair;
        }

        static auto _contain(
                const PAIR &e1, const PAIR &e2) -> bool {
            return e1.first <= e2.first
                && e1.second >= e2.second;
        }

        inline static auto _contains(
                const pair<PAIR, PAIR> &elfPair) -> bool {
            const auto& [e1, e2] = elfPair;
            return _contain(e1, e2)
                || _contain(e2, e1);
        }

        inline static auto _overlap(
                const pair<PAIR, PAIR> &elfPair) -> bool {
            const auto& [e1, e2] = elfPair;
            return e1.second >= e2.first
                && e1.first <= e2.second;
        }

    public:
        explicit DayFour(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            vector<pair<PAIR, PAIR>> v;
            FUNC F = [&](const string& val) {
                const pair<string, string> out = {
                        _getOutputs(&val, ",")
                };
                auto elfPair { _returnPair(out) };
                v.push_back(elfPair);
            }; { edit(F); }
            return v;
        }

        void firstFragment() override {
            auto calc{0};

            for (const auto &pair : *getCache()) {
                if (_contains(pair)) {
                    calc += 1;
                }
            }

            cout << "First Fragment:"
                 << endl << endl;

            cout << "Total: " << calc
                 << endl
                 << endl;
        }

        void secondFragment() override {
            auto calc{0};

            for (const auto &pair : *getCache()) {
                if (_overlap(pair)) {
                    calc += 1;
                }
            }

            cout << "Second Fragment:"
                 << endl << endl;

            cout << "Total: " << calc
                 << endl;
        }
};

int main() {
    auto main = DayFour("../inputs/dayFour");
    main
      .cacheRes(main
      .editState());
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}