#include <vector>
#include "parser/Parser.hpp"

using namespace std;

class DayThree : Parser<int> {
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

        int editState() override {
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

        void result() override {
            cout << DayThree::editState() << endl;
        }
};

int main() {
    auto dayThree = DayThree(
            "../inputs/dayThree"
            );
    dayThree.result();
    return 0;
}