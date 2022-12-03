#include <iostream>
#include <vector>
#include "parser/Parser.hpp"

using namespace std;

class DayOne : Parser<vector<int>> {
    private:
        struct {
                bool operator()(int a, int b) const {
                    return a > b;
                }
            } MORE;

    public:
        explicit DayOne(const char *fileName): Parser(fileName) {}

        vector<int> editState() override {
            vector<int> cals;
            int calc { 0 };
            function<void(string)> F = [&](const string& val){
                if (val.empty()) {
                    cals.push_back(calc),
                    calc = 0;
                } else calc += stoi(val);
            };
            edit(F);
            return cals;
        }

        void result() override {
            vector<int> cals{
                DayOne::editState()
            };

            sort(cals.begin(),
                 cals.end(),
                 MORE);

            for (int i = 0; i < 3; ++i) {
                cout <<
                     (i + 1) << ". " << cals.at(i)
                     << endl;
            }
        }
};

int main() {
    auto dayOne = DayOne("../inputs/dayOne");
    dayOne.result();
    return 0;
}