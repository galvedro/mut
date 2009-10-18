/* -------------------------------------------------------------------------- */
/*                                                                            */
/*                         Micro Unit Testing Framework                       */
/*                       Copyright (c) 2009, Anton Gomez                      */
/*                                                                            */
/* 1. LICENSE                                                                 */
/*                                                                            */
/* You are free to use, modify and redistribute this software at will for     */
/* both commercial and non commercial applications. Just be sure to keep the  */
/* copyright notice in place.                                                 */
/*                                                                            */
/*                                                                            */
/* 2. USAGE                                                                   */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*                                                                            */
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
        printf("-- Testsuite FAILED --\n");                                    \
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
