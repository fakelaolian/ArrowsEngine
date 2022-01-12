/* AUTHOR: 2BKBD, DATE: 2022/1/10 */
#pragma once

#include <AnciCore.h>

struct AlslSource {
        String vtxSource;
        String fragSource;
};

/* 读取着色器内容 */
void ReadAlslSource(const char *file, AlslSource *source);