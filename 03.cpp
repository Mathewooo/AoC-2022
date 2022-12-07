#include <vector>
#include <set>
#include "parser/Parser.hpp"

using namespace std;

enum Priority : int {
    LOW = 1,
    HIGH = 27
};

enum Val : int {
    first = 0, second = 1, third = 2
};

template<int N>
struct TUPLE {
    string *arr = new string[N];

    string* get(const int index) const {
        return &(arr[index]);
    }

    auto set(const int *index,
             const string& val) {
        arr[*index] = val;
    }
};

typedef int TYPE;

class DayThree : Parser<TYPE> {
    private:
        inline static auto _determinePriority(const char cr
                ) -> uint8_t {
            return islower(cr)
                    ? Priority::LOW + cr - 'a'
                    : Priority::HIGH + cr - 'A';
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
            auto F = [&](const string& val){
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
            }; { edit(F); }
            return calc;
        }

        TYPE succeedingState() {
            auto calc {0},
                 index {0};
            TUPLE<3> group;
            auto F = [&](const string& val){
                group.set(&index, val);
                ++index;
                if (index > 2) {
                    const auto first = group.get(Val::first),
                         second = group.get(Val::second),
                         third = group.get(Val::third);
                    char temp {0};
                    for (auto &cr : *first) {
                        if ((second->contains(cr)
                            && third->contains(cr))
                            && cr != temp) {
                            temp = cr;
                            calc += _determinePriority(cr);
                        }
                    }
                    group = {}, index = 0;
                }
            }; { edit(F); }
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
    auto main = DayThree(
            "../inputs/dayThree"
            );
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