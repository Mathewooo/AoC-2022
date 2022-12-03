#include <vector>
#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;

class DayThree : Parser<TYPE> {
    private:
        enum PRIORITY : int {
            LOW = 1,
            HIGH = 27
        };

        static auto _determinePriority(const char cr) -> uint8_t {
            return islower(cr)
                    ? PRIORITY::LOW + cr - 'a'
                    : PRIORITY::HIGH + cr - 'A';
        }

        static auto _getCompartments(
                const int *size, const string& vl
        ) -> pair<string, string> {
            return {
                vl.substr(0, *size),
                vl.substr(*size)
            };
        }

    public:
        explicit DayThree(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE earlyState() {
            int calc { 0 };
            function<void(string)> F = [&](const string& val){
                if (val.size() % 2 != 0) return;
                const auto ctSize {
                    static_cast<int>(val.size() / 2)
                };
                const auto cts {
                    _getCompartments(&ctSize, val)
                };
                char temp{0};
                for (auto cr : cts.first) {
                    if (cts.second.contains(cr)
                        && cr != temp) {
                        temp = cr;
                        calc += _determinePriority(cr);
                    }
                }
            };
            edit(F);
            return calc;
        }

        TYPE succeedingState() {
            auto calc { 0 },
                 index { 0 };
            vector<string> group;
            function<void(string)> F = [&](const string& val){
                index++;
                if (index >= 3) {

                } else {
                    group.push_back(val);
                }
            };
            edit(F);
            return calc;
        }

        void firstFragment() override {

        }

        void secondFragment() override {

        }
};

int main() {
    auto dayThree = DayThree(
            "../inputs/dayThree"
            );
    dayThree.cacheRes(dayThree.earlyState());
    dayThree.firstFragment();
    dayThree.cacheRes(dayThree.succeedingState());
    dayThree.secondFragment();
    return 0;
}