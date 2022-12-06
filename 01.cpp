#include <iostream>
#include <vector>
#include "parser/Parser.hpp"

using namespace std;

typedef vector<int> TYPE;

class DayOne : Parser<TYPE> {
    private:
        struct {
            bool operator()(int a, int b) const {
                return a > b;
            }
        } MORE;

        inline static auto _slice(vector<int> const *v,
                    int x, int y) -> vector<int> {
            auto first = v->begin() + x;
            auto last = v->begin() + y + 1;
            vector<int> vector(first, last);
            return vector;
        }

    public:
        explicit DayOne(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            vector<int> cals;
            int calc;
            FUNC F = [&](const string& val){
                if (val.empty()) {
                    cals.push_back(calc),
                    calc = 0;
                } else calc += stoi(val);
            }; { edit(F); }
            sort(cals.begin(),
                 cals.end(),
                 MORE);
            return cals;
        }

        void firstFragment() override {
            const auto cals{
                    getCache()
            };

            cout << "First Fragment:"
                << endl << endl;

            cout << "Total: " << cals->at(0)
                << endl << endl;
        }

        void secondFragment() override {
            const auto cals{
                _slice(getCache(), 0, 2)
            };

            cout << "Second Fragment:"
                << endl << endl;

            int index {0}, total {0};
            for (auto &i : cals) {
                cout <<
                     (++index) << ". " << i
                     << endl;
                total += i;
            }

            cout << endl << "Total: " << total << endl;
        }
};

int main() {
    auto main = DayOne("../inputs/dayOne");
    main
      .cacheRes(main
      .editState());
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}