#include <unordered_set>
#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;

class DaySeven : Parser<TYPE> {
    private:

    public:
        explicit DaySeven(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            auto calc {0};

            auto F = [&](const string& val){

            }; { edit(F); }

            return calc;
        }

        void firstFragment() override {

        }

        void secondFragment() override {

        }
};

int main() {
    auto main = DaySeven("../inputs/daySix");
    main
      .cacheRes(main
      .editState());
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}