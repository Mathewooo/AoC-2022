#include <queue>
#include <regex>
#include <numeric>
#include "parser/Parser.hpp"
#include "utilities/Utils.hpp"

using namespace std;
using namespace Hash;
using namespace Regex;
using namespace Trim;

enum class Operation : int32_t {
    Add = 1, Multiply = 2, Square = 3
};

struct {
    bool operator()(int a, int b) const {
        return a > b;
    }
} MORE;

class Monkey {
    private:
        auto _updateItem() -> uint64_t& {
            auto &item{items.front()};
            switch (operation) {
                case Operation::Add:
                    item += update; break;
                case Operation::Multiply:
                    item *= update; break;
                case Operation::Square:
                    item *= item; break;
            }
            return item;
        }

    public:
        queue<uint64_t> items;
        uint64_t divisor;
        pair<uint16_t, uint16_t> destination;
        Operation operation;
        uint64_t update{0}, count;

        pair<uint16_t, uint64_t> throwItem() {
            auto item{items.front()}; {
                items.pop();
            }
            if (item % divisor == 0) {
                return {
                    destination.first, item
                };
            }
            return {
                destination.second, item
            };
        }

        auto inspectFirstItem() {
            if (items.empty()) return false;
            ++count;
            auto &item{_updateItem()};
            item /= 3; return true;
        }

        auto inspectSecondItem(uint64_t div) {
            if (items.empty()) return false;
            ++count;
            auto &item{_updateItem()};
            item %= div; return true;
        }
};

typedef int TYPE;

class DayTen : Parser<TYPE> {
    private:
        auto _initMonkeys() -> vector<Monkey> {
            vector<Monkey> monkeys;
            auto F = [&](const string &val) {
                if (val.empty()) return;
                auto temp{
                    split(reduce(val), regex{"\\ +"})
                };
                switch (hashStr(temp[0])) {
                    case "Monkey"_: {
                        monkeys.emplace_back(Monkey{});
                        break;
                    }
                    case "Starting"_: {
                        for (int i = 2; i < temp.size(); ++i) {
                            auto item{temp[i]};
                            item.erase(remove(item.begin(),
                                              item.end(),
                                              ','),
                                       item.end());
                            monkeys.back()
                                .items.push(stoi(item));
                        }
                        break;
                    }
                    case "Operation:"_: {
                        auto opr{temp[4]}, arg{temp[5]};
                        if (opr == "*" && arg == "old") {
                            monkeys.back()
                                .operation = Operation::Square;
                        } else if (opr == "+") {
                            monkeys.back()
                                .operation = Operation::Add,
                            monkeys.back().update = stoi(arg);
                        } else
                            monkeys.back()
                                .operation = Operation::Multiply,
                            monkeys.back().update = stoi(arg);
                        break;
                    }
                    case "Test:"_: {
                        monkeys.back()
                            .divisor = stoi(temp[3]);
                        break;
                    }
                    case "If"_: {
                        auto trueOrFalse{temp[1]};
                        auto arg{stoi(temp[5])};
                        if (trueOrFalse == "true:") {
                            monkeys.back()
                                .destination.first = arg;
                        } else
                            monkeys.back()
                                .destination.second = arg;
                        break;
                    }
                }
            }; { edit(F); }
            return monkeys;
        }

        int64_t _monkeyBusiness(vector<Monkey> v) {
            vector<uint64_t> inspects{};
            transform(v.begin(),
                      v.end(),
                      back_inserter(inspects),
                           [](const auto& monkey) {
                return monkey.count;
            });
            sort(inspects.begin(),
                 inspects.end(),
                 MORE);
            return inspects[0] * inspects[1];
        }

        const vector<Monkey> _monkeys{
            _initMonkeys()
        };

    public:
        explicit DayTen(const char *fileName) : Parser(fileName) {}

        using Parser::cacheRes;

        TYPE earlyState() {
            auto round{0}; auto temp{_monkeys};

            while (round++ < 20) {
                for (auto& monkey : temp) {
                    while (monkey.inspectFirstItem()) {
                        const auto& [destination, item] {
                            monkey.throwItem()
                        };
                        temp[destination].items.push(item);
                    }
                }
            }

            return _monkeyBusiness(temp);
        }

        TYPE succeedingState() {
            auto round{0}; auto temp{_monkeys};

            const auto division =
                    reduce(temp.begin(),
                           temp.end(),
                           int64_t{1},
                           [](auto &div, auto &monkey) {
                        return div * monkey.divisor;
            });

            while (round++ < 10'000) {
                for (auto& monkey : temp) {
                    while (monkey.inspectSecondItem(division)) {
                        const auto& [destination, item] {
                                monkey.throwItem()
                        };
                        temp[destination].items.push(item);
                    }
                }
            }

            return _monkeyBusiness(temp);
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
    auto main = DayTen("../inputs/dayEleven");
    main
      .cacheRes(main
      .earlyState()),
    main.firstFragment(),
    main
      .cacheRes(main
      .succeedingState()),
    main.secondFragment();
    return EXIT_SUCCESS;
}