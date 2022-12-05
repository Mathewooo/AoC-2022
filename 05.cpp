#include <vector>
#include <iterator>
#include <algorithm>
#include "parser/Parser.hpp"

using namespace std;

typedef string TYPE;
typedef vector<vector<char>> STACKS;

class DayOne : Parser<TYPE> {
    private:
        inline auto _splittedInput() -> pair<vector<string>, vector<string>> {
            vector<string> stacks,
                           instructions;
            bool afterSpace {false};
            auto f = [&](const string& val){
                if (val.empty()) {
                    afterSpace = true;
                    return;
                }
                if (!afterSpace && !val.empty()) {
                    stacks.push_back(val);
                } else instructions.push_back(val);
            }; { edit(f); }
            return {
                stacks,
                instructions
            };
        }

        auto _initializeStacks(const vector<string> &input,
                               STACKS &stacks) {
            auto in {input};
            auto stackIndexes {
                    in.back()
            };

            reverse(in.begin(),
                    in.end());

            for (int i = 0; i < stackIndexes.length(); ++i) {
                if (!isblank(stackIndexes[i])) {
                    vector<char> currentItems;
                    for (int j = 1; j < in.size(); ++j) {
                        auto row {
                                in[j]
                        };
                        auto index {0};
                        while (index < i) ++index;
                        const auto crate{
                                row.c_str()[index]
                        };
                        if (index == i && !isblank(crate)) {
                            currentItems.push_back(
                                    crate
                            );
                        }
                    }
                    stacks.push_back(currentItems);
                }
            }
        }

        pair<vector<string>, vector<string>> _in {
                _splittedInput()
        };

    public:
        explicit DayOne(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            string res {""};
            vector<vector<char>> stacks; {
                _initializeStacks(_in.first, stacks);
            }

            for (const auto& instruction : _in.second) {
                int num {0}, from {0}, to {0};
                sscanf(instruction.c_str(),
                       "move %d from %d to %d",
                       &num, &from, &to);
                --from, --to;
                for (int i = 0; i < num; ++i) {
                    stacks[to].emplace_back(stacks[from].back());
                    stacks[from].pop_back();
                }
            }

            for (auto &vl : stacks) {
                res.push_back(vl
                   .back());
            }

            return res;
        }

        TYPE succeedingState() {
            string res {""};
            vector<vector<char>> stacks; {
                _initializeStacks(_in.first, stacks);
            }

            for (const auto& instruction : _in.second) {
                int num {0}, from {0}, to {0};
                sscanf(instruction.c_str(),
                       "move %d from %d to %d",
                       &num, &from, &to);
                --from, --to;
                stacks[to].insert(
                        stacks[to].end(),
                        stacks[from].end() - num,
                        stacks[from].end()
                );
                stacks[from].erase(
                        stacks[from].end() - num,
                        stacks[from].end()
                );
            }

            for (auto &vl : stacks) {
                res.push_back(vl
                   .back());
            }

            return res;
        }

        void firstFragment() override {
            cout << "First Fragment:"
                 << endl << endl;

            cout << "Result: " << *getCache()
                 << endl
                 << endl;
        }

        void secondFragment() override {
            cout << "Second Fragment:"
                 << endl << endl;

            cout << "Result: " << *getCache()
                 << endl;
        }
};

int main() {
    auto main = DayOne("../inputs/dayFive");
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