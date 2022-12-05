#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

typedef function<
        void(const string &val)
> FUNC;

template<typename T>
class Parser {
    private:
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

        ifstream _input;
        T _cache;
        vector<string> _in;

    public:
        explicit Parser(const char *file) {
            _input.open(file, ios::in);
            if (!_input.good()) {
                cerr <<
                    "Error while opening input!"
                    << endl;
            }
            _in = _getInput();
        }

        auto edit(FUNC f) {
            const auto in = _in;
            for_each(in.begin(),
                     in.end(),
                     std::move(f));
        }

        T *getCache() {
            return &_cache;
        }

        virtual void cacheRes(T r) {
            _cache = r;
        }

        virtual void firstFragment() = 0;
        virtual void secondFragment() = 0;
};

