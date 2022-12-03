#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class Parser {
    private:
        ifstream _input;

        auto _getInput() -> vector<string> {
            vector<string> in;
            string line;
            while (getline(
                    Parser::_input, line
            )) {
                in.push_back(line);
            }
            _input.close();
            return in;
        }

    public:
        explicit Parser(const char *file) {
            _input.open(file, ios::in);
            if (!_input.good()) {
                cerr <<
                    "Error while opening input!"
                    << endl;
            }
        }

        auto edit(function<
                    void(const string &val)
                > f) {
            auto in = _getInput();
            std::for_each(in.begin(),
                          in.end(),
                          std::move(f));
        }

        virtual T editState() = 0;
        virtual void result() = 0;
};