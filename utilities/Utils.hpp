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