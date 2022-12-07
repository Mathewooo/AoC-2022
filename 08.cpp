#include "parser/Parser.hpp"

using namespace std;

typedef int TYPE;

class DayEight : Parser<TYPE> {

public:
    explicit DayEight(const char *fileName) : Parser(fileName) {}

    using Parser::cacheRes;

    TYPE editState() {
        auto calc{0};

        return calc;
    }

    void firstFragment() override {

    }

    void secondFragment() override {

    }
};

int main() {
    auto main = DayEight("../inputs/dayEight");
    main
      .cacheRes(main
      .editState());
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}