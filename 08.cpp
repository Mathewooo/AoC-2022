#include <iterator>
#include "parser/Parser.hpp"
#define SIZE 99

using namespace std;

typedef struct {
    int data[SIZE][SIZE];
} Grid;

typedef int TYPE;

class DayEight : Parser<TYPE> {
    private:
        auto _getGrid() -> Grid {
            Grid grid; auto index{0};

            auto F = [&](const string& val){
                for (int i = 0; i < val.length(); ++i) {
                    grid.data[index][i] = static_cast<int>
                    (val[i]);
                }
                ++index;
            }; { edit(F); }

            return grid;
        }

        auto _isVisible(int x, int y) -> bool {
            if (x == 0 || x == SIZE - 1
                || y == 0 || y == SIZE - 1) {
                return true;
            }

            const auto cur{_grid.data[x][y]};
            vector<bool> v {true, true, true, true};

            for (int i = y + 1; i < SIZE; i++) {
                if (_grid.data[x][i] >= cur)
                    v[0] = false;
            }

            for (int i = y - 1; i > -1; i--) {
                if (_grid.data[x][i] >= cur)
                    v[1] = false;
            }

            for (int i = x + 1; i < SIZE; i++) {
                if (_grid.data[i][y] >= cur)
                    v[2] = false;
            }

            for (int i = x - 1; i > -1; i--) {
                if (_grid.data[i][y] >= cur)
                    v[3] = false;
            }

            if (count(v.begin(),
                      v.end(), true)) {
                return true;
            } else return false;
        }

        auto _getScore(int x, int y) -> int {
            auto up{0}, down{0}, left{0}, right{0};
            const auto cur{_grid.data[x][y]};

            for (int i = y + 1; i < SIZE; i++) {
                up++;
                if (_grid.data[x][i] >= cur) break;
            }

            for (int i = y - 1; i > -1; i--) {
                down++;
                if (_grid.data[x][i] >= cur) break;
            }

            for (int i = x + 1; i < SIZE; i++) {
                left++;
                if (_grid.data[i][y] >= cur) break;
            }

            for (int i = x - 1; i > -1; i--) {
                right++;
                if (_grid.data[i][y] >= cur) break;
            }

            return up * down * left * right;
        }

        Grid _grid{
            _getGrid()
        };
    public:
        explicit DayEight(const char *fileName) : Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            auto calc{0};

            for (int x = 0; x < SIZE; ++x) {
                for (int y = 0; y < SIZE; ++y) {
                    if (_isVisible(x, y)) calc++;
                }
            }

            return calc;
        }

        TYPE succeedingState() {
            auto calc{0};

            for (int x = 0; x < SIZE; ++x) {
                for (int y = 0; y < SIZE; ++y) {
                    calc = max(calc, _getScore(x, y));
                }
            }

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
    auto main = DayEight("../inputs/dayEight");
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