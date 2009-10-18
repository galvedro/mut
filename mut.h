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
            printf("-- Testsuite PASSED, %d out of %d tests run --\n", \
                __tests_run__, __total_tests__); \
            return 0; \
        } \
        else \
        { \
            printf("-- Testsuite FAILED, %d out of %d tests run --\n", \
                __tests_run__, __total_tests__); \
            return 1; \
        } \
    }



#define TEST_BEGIN(__test_name__) \
        { \
            __label__ __test_end__; \
            __total_tests__++; \
            \
            if (__veredict__ == UNDEFINED) \
            { \
                __tests_run__++;



#define TEST_END \
        __test_end__: \
            ; \
            } \
        }


#define __ASSERTION_FAILED__ \
        __veredict__ = FAILED; \
        printf("ERROR: Assertion failed at line %d\n", __LINE__); \
        goto __test_end__;



#define CHECK(__assertion__) \
    if ( !(__assertion__) ) \
    { \
        __ASSERTION_FAILED__ \
    }
    
    



#endif
