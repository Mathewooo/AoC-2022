#include <unordered_set>
#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;

class DaySix : Parser<TYPE> {
    private:
        static auto _startOfMarker(const string& str,
                                   int range) -> int {
            for (int i = 0; (range + i) < str.length(); ++i) {
                const auto pad {
                    str.begin() + i
                };
                unordered_set<char> current(
                        pad, pad + range
                );
                if (current.size() == range) {
                    return (range + i);
                }
            }
            return -1;
        }

        inline auto _initInput() -> string {
            string in;
            auto F = [&](const string& val){
                for (const auto &cr : val) {
                    in.push_back(cr);
                }
            }; { edit(F); }
            return in;
        }

        const string _in {_initInput()};

    public:
        explicit DaySix(const char *fileName): Parser(fileName) {}

        void firstFragment() override {
            constexpr auto RANGE{4};

            cout << "First Fragment:"
                 << endl << endl;

            cout << "Total: " << _startOfMarker(
                    _in, RANGE)
                 << endl
                 << endl;
        }

        void secondFragment() override {
            constexpr auto RANGE{14};

            cout << "Second Fragment:"
                 << endl << endl;

            cout << "Total: " << _startOfMarker(
                    _in, RANGE)
                 << endl;
        }
};

int main() {
    auto main = DaySix("../inputs/daySix");
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}