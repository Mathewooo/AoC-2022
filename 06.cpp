#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;

class DaySix : Parser<TYPE> {
    private:

    public:
        explicit DaySix(const char *fileName): Parser(fileName) {}

        using Parser::cacheRes;

        TYPE editState() {
            int calc {0};
            FUNC f = [&](const string& val){

            }; { edit(f); }
            return calc;
        }

        void firstFragment() override {

        }

        void secondFragment() override {

        }
};

int main() {
    auto main = DaySix("../inputs/daySix");
    main
      .cacheRes(main
      .editState());
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}