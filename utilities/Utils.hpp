#include <regex>

namespace Hash {
    constexpr static int64_t getHash(const char* cp) {
        int64_t hash = 0;
        while (*cp) {
            hash = (hash * 10) + *cp++ - '0';
        }
        return hash;
    }

    constexpr inline int64_t operator "" _(
            char const *p, size_t
    ) {
        return getHash(p);
    }

    auto hashStr(string const &s) {
        return getHash(s.data());
    }
}

namespace Regex {
    static auto split(const string &str,
                       const regex &reg) -> vector<string> {
        sregex_token_iterator iter(str.begin(),
                                   str.end(),
                                   reg,-1);
        sregex_token_iterator end;
        return {iter, end};
    }
}

namespace Trim {
    string trim(const string& str,
                 const string& whitespace = " ") {
        auto strBegin{str
            .find_first_not_of(whitespace)};
        if (strBegin == string::npos) {
            return "";
        }
        auto strEnd{str
                .find_last_not_of(whitespace)};
        auto strRange {
            strEnd - strBegin + 1
        };
        return str.substr(strBegin, strRange);
    }

    string reduce(const string& str,
                  const string& fill = " ",
                  const string& whitespace = " ") {
        auto result{trim(str, whitespace)};
        auto beginSpace{result
                .find_first_of(whitespace)};

        while (beginSpace != string::npos) {
            auto endSpace = result
                    .find_first_not_of(whitespace, beginSpace);
            auto range = endSpace - beginSpace;
            result.replace(beginSpace,
                           range,
                           fill);
            auto newStart{beginSpace + fill.length()};
            beginSpace = result
                    .find_first_of(whitespace, newStart);
        }

        return result;
    }
}