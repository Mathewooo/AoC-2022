#include <set>
#include <array>
#include "parser/Parser.hpp"
#include "utilities/Utils.hpp"

using namespace std;
using namespace Regex;

typedef pair<int, int> Pos;

typedef int TYPE;

class DayNine : Parser<TYPE> {
    private:
        auto _sign(int v) {
            return (v > 0) - (v < 0);
        }

        auto _moveHead(char cr, Pos& head) {
            switch (cr) {
                case 'R':
                    ++head.first; break;
                case 'L':
                    --head.first; break;
                case 'U':
                    ++head.second; break;
                case 'D':
                    --head.second; break;
            }
        }

        auto _moveTail(const Pos &head, Pos &tail) {
            constexpr size_t maxDist{1};
            const auto dh = head.first - tail.first,
                       dv = head.second - tail.second;
            if (abs(dh) > maxDist
                || abs(dv) > maxDist) {
                tail.first += _sign(dh),
                tail.second += _sign(dv);
            }
        }
    public:
        explicit DayNine(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE earlyState() {
            Pos head, tail;
            set<Pos> tailPositions{tail};
            auto F = [&](const string& val){
                auto out = split(val,
                                 regex{"\\ +"});
                const char direction{out[0][0]};
                int steps{stoi(out[1])};
                while (steps-- > 0) {
                    _moveHead(direction, head);
                    _moveTail(head, tail);
                    tailPositions.insert(tail);
                }
            }; { edit(F); }
            return tailPositions.size();
        }

        TYPE succeedingState() {
            constexpr size_t dim{10};
            array<Pos, dim> rope;
            Pos &head{rope[0]}, &tail{rope[dim - 1]};
            set<Pos> tailPositions{tail};
            auto F = [&](const string& val){
                auto out = split(val,
                                 regex{"\\ +"});
                const char direction{out[0][0]};
                int steps{stoi(out[1])};
                while (steps-- > 0) {
                    _moveHead(direction, head);
                    for (size_t i = 0; i < dim - 1; ++i) {
                        _moveTail(rope[i], rope[i + 1]);
                    }
                    tailPositions.insert(tail);
                }
            }; { edit(F); }
            return tailPositions.size();
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
    auto main = DayNine(
            "../inputs/dayNine"
    );
    main
      .cacheRes(main
      .earlyState()),
    main.firstFragment(),
    main
      .cacheRes(main
      .succeedingState());
    main.secondFragment();
    return EXIT_SUCCESS;
}