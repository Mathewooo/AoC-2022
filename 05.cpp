#include <vector>
#include <iterator>
#include <algorithm>
#include "parser/Parser.hpp"

using namespace std;

typedef string TYPE;

class DayOne : Parser<TYPE> {
    private:
        pair<vector<string>, vector<string>> _in {
                _splittedInput()
        };
        vector<vector<char>> _stacks;

        inline auto _splittedInput() -> pair<vector<string>, vector<string>> {
            vector<string> stacks,
                           instructions;
            bool afterSpace {false};
            auto F = [&](const string& val){
                if (val.empty()) {
                    afterSpace = true;
                    return;
                }
                if (!afterSpace && !val.empty()) {
                    stacks.push_back(val);
                } else instructions.push_back(val);
            }; { edit(F); }
            return {
                stacks,
                instructions
            };
        }

        inline auto _initStacks() {
            auto in {&_in.first};
            auto stackIndexes {
                    in->back()
            };

            reverse(in->begin(),
                    in->end());

            for (int i = 0; i < stackIndexes.length(); ++i) {
                if (!isblank(stackIndexes[i])) {
                    vector<char> currentItems;
                    auto index {0};
                    while (++index < in->size()) {
                        const auto crate{
                                in->at(index).at(i)
                        };
                        if (!isblank(crate)) {
                            currentItems.push_back(
                                    crate
                            );
                        }
                    }
                    _stacks.push_back(currentItems);
                }
            }
        }

        auto _returnRes(const vector<vector<char>> &stacks) -> string {
            string res;
            for (auto &cr : stacks) {
                res.push_back(cr
                   .back());
            }
            return res;
        }

    public:
        explicit DayOne(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        auto initStacks() {
            _initStacks();
        }

        TYPE editState() {
            auto stacks {_stacks};

            for (const auto& instruction : _in.second) {
                auto num {0}, from {0}, to {0};
                sscanf(instruction.c_str(),
                       "move %d from %d to %d",
                       &num, &from, &to);
                --from, --to;
                for (int i = 0; i < num; ++i) {
                    stacks[to].emplace_back(stacks[from].back());
                    stacks[from].pop_back();
                }
            }

            return _returnRes(stacks);
        }

        TYPE succeedingState() {
            auto stacks {_stacks};

            for (const auto& instruction : _in.second) {
                auto num {0}, from {0}, to {0};
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

            return _returnRes(stacks);
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
    main.initStacks();
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