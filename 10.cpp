#include <numeric>
#include <sstream>
#include <array>
#include <regex>
#include "parser/Parser.hpp"
#include "utilities/Utils.hpp"

#define NOOP "noop"
#define ADDX "addx"

#define HEIGHT 6
#define WIDTH 40

#define LIT '#'
#define DARK '.'

using namespace std;
using namespace Regex;

typedef int TYPE;

class DayTen : Parser<TYPE> {
    private:
        auto _execute(int &x, function<void()> tick) {
            auto F = [&](const string& val){
                if (val == NOOP) {
                    tick(); return;
                } else if (auto temp{
                    split(val, regex{"\\ +"})};
                        temp[0] == ADDX) {
                    for ([[maybe_unused]] auto i : {1, 2})
                        tick();
                    x += stoi(temp[1]);
                }
            }; { edit(F); }
        }

    public:
        explicit DayTen(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE earlyState() {
            vector<int> cycles; auto x{1};

            auto tick = [&cycles, &x]() {
                cycles.push_back(x);
            };

            _execute(x, tick);

            const array<int, 6> positions{20, 60, 100, 140, 180, 220};
            auto sum = reduce(positions.begin(), positions.end(), int64_t{0},
                                       [&cycles](auto& s,
                                                    const auto& pos) {
                return s + cycles[pos - 1] * pos;
            });

            return sum;
        }

        auto succeedingState() -> vector<string> {
            auto x{1}, pos{0};
            array<char, WIDTH * HEIGHT> crt; {
                crt.fill(DARK);
            }

            auto tick = [&crt, &pos, &x]() {
                if (x - 1 <= (pos % WIDTH)
                    && (pos % WIDTH) <= x + 1) {
                    crt[pos] = LIT;
                }
                pos++;
            };

            _execute(x, tick);

            vector<string> res;

            for (size_t h = 0; h < HEIGHT; ++h) {
                string temp;
                for (size_t w = 0; w < WIDTH; ++w) {
                    temp.push_back(crt[h * WIDTH + w]);
                }
                res.push_back(temp);
            }

            return res;
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

            cout << "Result: "
                 << endl;

            for (auto str : succeedingState()) {
                cout << str << '\n';
            }
        }
};

int main() {
    auto main = DayTen(
            "../inputs/dayTen"
    );
    main
      .cacheRes(main
      .earlyState()),
    main.firstFragment(),
    main.secondFragment();
    return EXIT_SUCCESS;
}