/* AUTHOR: 2BKBD, DATE: 2022/1/10 */
#include "Alsl.h"

#include <cstring>
#include <iostream>
#include <fstream>

#define RD_NONE    0
#define RD_VTX     1
#define RD_FRAG    2

static bool CheckStatus(std::string &line, int &status)
{
        if (line == "#vtx")
        {
                status = RD_VTX;
                return true;
        }

        if (line == "#frag")
        {
                status = RD_FRAG;
                return true;
        }

        if (line == "#end")
        {
                status = RD_NONE;
                return true;
        }

        return false;
}

void ReadAlslSource(const char *file, AlslSource *source)
{
        int             status;
        String          line;
        String          vstr;
        String          fstr;
        String          version;
        std::ifstream   in(file);

        if (!in.is_open()) {
                String error = "Shader文件读取失败：";
                error = error + file;
                throw std::runtime_error(error.c_str());
        }

        status = RD_NONE;

        while (getline(in, line)) {
                if (strncmp(line.c_str(), "#version", 8) == 0) {
                        version.append(line).append("\n");
                        continue;
                }

                if (CheckStatus(line, status))
                        continue;

                if (status == RD_VTX) {
                        vstr.append(line).append("\n");
                }

                if (status == RD_FRAG) {
                        fstr.append(line).append("\n");
                }
        }

        source->vtxSource.append(version).append(vstr);
        source->fragSource.append(version).append(fstr);

        in.close();
}