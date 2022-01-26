/* AUTHOR: 2BKBD, DATE: 2022/1/12 */
#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>
#include <malloc.h>

/**
 * 定义两个分配宏，方便未来写内存管理使用
 */
#define vmalloc malloc
#define vrealloc realloc
#define vfree free

#define verror printf

#endif /*__CORE_H__*/
