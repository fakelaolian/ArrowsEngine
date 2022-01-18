/* AUTHOR: 2BKBD, DATE: 2022/1/18 */
#pragma once

#include <vector>
#include <cstring>

namespace StringUtils {
        void split(const std::string& str, const char *delim, std::vector<std::string> &result)
        {
                char *buf;
                char *tok;

                buf = new char[str.size() + 1];
                std::copy(str.begin(), str.end(), buf);

                tok = strtok(buf, delim);

                do {
                        result.push_back(tok);
                } while ((tok = strtok(NULL, delim)));
        }
}