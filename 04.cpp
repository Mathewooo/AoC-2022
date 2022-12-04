#include <regex>
#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;
typedef pair<int, int> PAIR;

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

        static auto _split(const string &str,
                               const regex &reg = regex{"\\-+"}) -> vector<string> {
            sregex_token_iterator iter(
                    str.begin(),
                    str.end(),
                    reg, -1
                    );
            sregex_token_iterator end;
            return {iter, end};
        }

        inline static int _toInt(const vector<string> &v,
                                 int index) {
            return stoi(v.at(index));
        }

        static auto returnPair(const pair<string, string> &pr) {
            pair<PAIR, PAIR> pair;
            auto f { _split(pr.first) },
                    s { _split(pr.second) };
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

        inline static auto _overlap(const pair<PAIR, PAIR> &elfPair) -> bool {
            const auto& [e1, e2] = elfPair;
            return e1.second >= e2.first
                && e1.first <= e2.second;
        }

    public:
        explicit DayFour(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            auto calc {0};
            FUNC f = [&](const string& val){
                const pair<string, string> out = {
                        _getOutputs(&val, ",")
                };
                auto elfPair { returnPair(out) };
                if (_contains(elfPair)) {
                    calc += 1;
                }
            }; { edit(f); }
            return calc;
        }

        TYPE succeedingState() {
            auto calc {0};
            FUNC f = [&](const string& val){
                const pair<string, string> out = {
                        _getOutputs(&val, ",")
                };
                auto elfPair { returnPair(out) };
                if (_overlap(elfPair)) {
                    calc += 1;
                }
            }; { edit(f); }
            return calc;
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
    auto main = DayFour("../inputs/dayFour");
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