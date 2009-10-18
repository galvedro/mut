#include <stdio.h>


#ifndef __MUT_H__
#define __MUT_H__


#define TESTSUITE_BEGIN \
    \
    enum veredict { \
        FAILED, \
        UNDEFINED, \
    }; \
    \
    enum veredict __veredict__ = UNDEFINED; \
    int __total_tests__ = 0; \
    int __tests_run__ = 0; \
    \
    int main(void) \
    {



#define TESTSUITE_END \
__testsuite_end__: \
        if(__veredict__ == UNDEFINED) \
        { \
            printf("-- Testsuite PASSED, %d tests run --\n", __tests_run__); \
            return 0; \
        } \
        else \
        { \
            printf("-- Testsuite FAILED, %d tests run --\n", __tests_run__); \
            return 1; \
        } \
    }



#define TEST_BEGIN(__test_name__) \
        __total_tests__++; \
        \
        if (__veredict__ == UNDEFINED) \
        { \
            __tests_run__++;



#define TEST_END \
        }


#define __ASSERTION_FAILED__ \
        __veredict__ = FAILED; \
        printf("ERROR: Assertion failed at line %d\n", __LINE__); \
        goto __testsuite_end__;



#define CHECK(__assertion__) \
    if ( !(__assertion__) ) \
    { \
        __ASSERTION_FAILED__ \
    }
    
    



#endif
