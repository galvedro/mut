/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                         Micro Unit Testing Framework                       */
/*                    Copyright (c) 2009, Anton Gomez Alvedro                 */
/*                                                                            */
/* 1. LICENSE                                                                 */
/*                                                                            */
/* Permission is hereby granted, free of charge, to any person obtaining a    */
/* copy of this software and associated documentation files (the "Software"), */
/* to deal in the Software without restriction, including without limitation  */
/* the rights to use, copy, modify, publish and distribute copies of the      */
/* Software, and to permit persons to whom the Software is furnished to do    */
/* so, subject to the following conditions:                                   */
/*                                                                            */
/* The above copyright notice and this permission notice shall be included in */
/* all copies or substantial portions of the Software.                        */
/*                                                                            */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    */
/* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    */
/* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        */
/* DEALINGS IN THE SOFTWARE.                                                  */
/*                                                                            */
/*                                                                            */
/* 2. USAGE                                                                   */
/*                                                                            */
/* In order to use this unit testing framework you just need to include the   */
/* header file. Mut test modules have the following structure:                */
/*                                                                            */
/* +----------------------------------+                                       */
/* |                                  |                                       */
/* | #include <mut.h>                 |                                       */
/* | #include <your_library.h>        |                                       */
/* |                                  |                                       */
/* |                                  |                                       */
/* | TESTSUITE_BEGIN                  |                                       */
/* |                                  |                                       */
/* |                                  |                                       */
/* | TEST_BEGIN("trivial test")       |                                       */
/* | ...                              |                                       */
/* | CHECK( 2 + 2 == 4 );             |                                       */
/* | ...                              |                                       */
/* | TEST_END                         |                                       */
/* |                                  |                                       */
/* |                                  |                                       */
/* | TEST_BEGIN("other test")         |                                       */
/* | TEST_DISABLE                     |                                       */
/* | ...                              |                                       */
/* | FAIL_IF( 2 + 2 != 4 );           |                                       */
/* | ...                              |                                       */
/* | TEST_END                         |                                       */
/* |                                  |                                       */
/* |                                  |                                       */
/* | TESTSUITE_END                    |                                       */
/* |                                  |                                       */
/* +----------------------------------+                                       */
/*                                                                            */
/* First of all: test code is written in regular C.                           */
/*                                                                            */
/* TESTSUITE_BEGIN and TESTSUITE_END macros are required and provide a main   */
/* C function with the necessary structure to execute your tests and report   */
/* results. By compiling this module and linking to the library under test    */
/* you'll get an executable that will run all tests defined from start to     */
/* finish and generate a final report on screen.                              */
/*                                                                            */
/* TEST_BEGIN and TEST_END serve the purpose of delimiting and naming your    */
/* test code. It is recommended that your testsuite is divided into small     */
/* test cases that verify just one thing and that do not depend on preceding  */
/* tests. In order to accomplish these goals, your tests have to be written   */
/* in such a way that it should be possible to reorganize the test cases      */
/* (reordering them) without affecting the final result. If you don't do it   */
/* like this, it will not be possible to disable individual tests for         */
/* debugging, or a failure in one test case will generate cascaded errors in  */
/* subsequent cases. The ultimate goal is that a failure in one test case     */
/* will spot one and only one broken functionality.                           */
/*                                                                            */
/* CHECK() and FAIL_IF() are the assertion macros available in Mut. They      */
/* are used to explicitly state conditions that have to be verified.          */
/*                                                                            */
/* TEST_DISABLE can be used immediately after a TEST_CASE() declaration       */
/* to quickly disable a test case.                                            */
/*                                                                            */
/* -------------------------------------------------------------------------- */



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>



#ifndef __MUT_H__
#define __MUT_H__



#define TESTSUITE_BEGIN                                                        \
                                                                               \
    enum __veredict_t__ {                                                      \
        __V_FAILED__,                                                          \
        __V_UNDEFINED__,                                                       \
    };                                                                         \
                                                                               \
    enum __veredict_t__ __veredict__ = __V_UNDEFINED__;                        \
    int __total_tests__ = 0;                                                   \
    int __tests_run__ = 0;                                                     \
    char * __current_test_name__ = "undefined";                                \
                                                                               \
    void __sig_handler(int sig)                                                \
    {                                                                          \
        __veredict__ = __V_FAILED__;                                           \
        printf("Error: Test \"%s\" caused a Segmentation Fault!\n",            \
            __current_test_name__);                                            \
        printf("-- Testsuite FAILED, %d tests run --\n", __tests_run__);       \
        exit(1);                                                               \
    }                                                                          \
                                                                               \
    int main(void)                                                             \
    {                                                                          \
        signal(SIGSEGV, __sig_handler);                                        \



#define TESTSUITE_END                                                          \
    __testsuite_end__:                                                         \
        if(__veredict__ == __V_UNDEFINED__)                                    \
        {                                                                      \
            printf("-- Testsuite PASSED, %d out of %d tests run --\n",         \
                __tests_run__, __total_tests__);                               \
            return 0;                                                          \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            printf("-- Testsuite FAILED, %d out of %d tests run --\n",         \
                __tests_run__, __total_tests__);                               \
            return 1;                                                          \
        }                                                                      \
    }



#define TEST_DISABLE goto __test_end_disabled__;



#define TEST_BEGIN(__test_name__)                                              \
        {                                                                      \
            __label__ __test_end__;                                            \
            __label__ __test_end_disabled__;                                   \
            __current_test_name__ = __test_name__;                             \
            __total_tests__++;                                                 \
                                                                               \
            if (__veredict__ == __V_UNDEFINED__)                               \
            {                                                                  \



#define TEST_END                                                               \
        __test_end__:                                                          \
            __tests_run__++;                                                   \
        __test_end_disabled__:                                                 \
            ;                                                                  \
            }                                                                  \
        }



#define __ASSERTION_FAILED__                                                   \
        __veredict__ = __V_FAILED__;                                           \
        printf("Error: Test \"%s\" failed at line %d\n",                       \
            __current_test_name__, __LINE__);                                  \
        goto __test_end__;



#define CHECK(__assertion__)                                                   \
    if ( !(__assertion__) )                                                    \
    {                                                                          \
        __ASSERTION_FAILED__                                                   \
    }



#define FAIL_IF(__assertion__)                                                 \
    if (__assertion__)                                                         \
    {                                                                          \
        __ASSERTION_FAILED__                                                   \
    }



#endif
