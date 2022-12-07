#include <regex>
#include <unordered_map>
#include <sstream>
#include "parser/Parser.hpp"
#include "utilities/Utils.hpp"

using namespace std;
using namespace Hash;
using namespace Regex;

struct File {
    string name;
    uint64_t size{0};
};

struct Directory {
    string name;
    uint64_t size{0};
    vector<File> files;
    vector<shared_ptr<Directory
    >> dirs;
    weak_ptr<Directory> parent;

    Directory() {}

    Directory(const string &name, weak_ptr<Directory> &parent) : name{name}, parent{parent} {}

    weak_ptr<Directory> getDir(const string &str) {
        return *find_if(dirs.begin(), dirs.end(),
                        [&](const auto &dir) {
            return dir.get()->name == str;
        });
    }
};

typedef shared_ptr<Directory> TYPE;

class DaySeven : Parser<TYPE> {
private:
    inline static auto _parse(const string &cmd,
                       weak_ptr<Directory> &dir) -> weak_ptr<Directory> {
        auto temp{split(cmd, regex{"\\ +"})};
        if (temp[0] == "dir") {
            auto subDir = make_shared<Directory>(
                    temp[1], dir
                    );
            dir.lock()->dirs.push_back(subDir);
            return dir;
        }
        const auto command{temp[1]};
        switch (hashStr(command)) {
            case "cd"_: {
                const auto arg{temp[2]};
                switch (hashStr(arg)) {
                    case "/"_:
                        return dir;
                    case ".."_:
                        return dir.lock()->parent;
                    default:
                        return dir.lock()
                            ->getDir(arg);
                }
            }
            case "ls"_:
                return dir;
        }
        File file{};
        stringstream stream(cmd);
        stream >> file.size >> file.name;
        dir.lock()->files.push_back(file);
        return dir;
    }

    constexpr auto _calcSizes(shared_ptr<Directory> &dir) -> void {
        for (auto &subDir: dir.get()->dirs) {
            _calcSizes(subDir);
            dir.get()->size += subDir.get()->size;
        }
        for (auto &file: dir.get()->files) {
            dir.get()->size += file.size;
        }
    }

    constexpr auto _sumSizes(shared_ptr<Directory> &dir,
                             uint64_t threshold) -> uint64_t {
        uint64_t res{0};
        for (auto &subDir: dir.get()->dirs) {
            if (subDir.get()->size <= threshold) {
                res += subDir.get()->size;
            }
            res += _sumSizes(subDir, threshold);
        }
        return res;
    }

    constexpr auto _minSpaceToDelete(shared_ptr<Directory> &dir,
                                     const uint64_t &req, const uint64_t &min) -> uint64_t {
        uint64_t res{min};
        for (auto &subDir: dir.get()->dirs) {
            if (subDir.get()->size >= req
                && subDir.get()->size < res) {
                res = subDir.get()->size;
            }
            res = _minSpaceToDelete(subDir, req, res);
        }
        return res;
    }

public:
    explicit DaySeven(const char *fileName) : Parser(fileName) {}

    using Parser::cacheRes;

    TYPE editState() {
        auto root = make_shared<Directory>();
        weak_ptr<Directory> dir = root;

        auto F = [&](const string &val) {
            dir = _parse(val, dir);
        }; { edit(F); }

        _calcSizes(root);

        return root;
    }

    void firstFragment() override {
        cout << "First Fragment:"
             << endl
             << endl;

        cout << "Result: "
             << _sumSizes(*getCache(), 100000)
             << endl
             << endl;
    }

    void secondFragment() override {
        const auto freeSpace {
            70000000 - getCache()->get()->size
            }, requiredSpace {
            30000000 - freeSpace
        };

        cout << "Second Fragment:"
             << endl
             << endl;

        cout << "Total: "
             << _minSpaceToDelete(*getCache(),
                                  requiredSpace,
                                  getCache()->get()->size)
             << endl;
    }
};

int main() {
    auto main = DaySeven("../inputs/daySeven");
    main.cacheRes(main.editState());
    main.firstFragment();
    main.secondFragment();
    return EXIT_SUCCESS;
}