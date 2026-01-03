#ifndef TEST_H
#define TEST_H

// Basic Test Framework for C++ based on Catch2

#include <stdexcept>
#include <string>
#include <print>

// Bassed on https://github.com/eyalroz/cpp-static-block/
#ifndef CONCATENATE
#define CONCATENATE(s1, s2) s1##s2
#define EXPAND_THEN_CONCATENATE(s1, s2) CONCATENATE(s1, s2)
#endif /* CONCATENATE */
#ifndef UNIQUE_IDENTIFIER
/**
 * This macro expands into a different identifier in every expansion.
 * Note that you _can_ clash with an invocation of UNIQUE_IDENTIFIER
 * by manually using the same identifier elsewhere; or by carefully
 * choosing another prefix etc.
 */
#ifdef __COUNTER__
#define UNIQUE_IDENTIFIER(prefix) EXPAND_THEN_CONCATENATE(prefix, __COUNTER__)
#else
#define UNIQUE_IDENTIFIER(prefix) EXPAND_THEN_CONCATENATE(prefix, __LINE__)
#endif /* COUNTER */
#else
#endif /* UNIQUE_IDENTIFIER */

#ifdef TESTMODE

// Test macros
#define REC_EQL(value, target) \
    if (value != target)       \
        throw Test::TestFailure(__FILE__, "==", #value, #target);
#define REC_NEQ(value, target) \
    if (value == target)       \
        throw Test::TestFailure(__FILE__, "!=", #value, #target);
#define REC_TRUE(value) \
    if (!(value))       \
        throw Test::TestFailure(__FILE__, "==", #value, "true");
#define REC_FALSE(value) \
    if (value)           \
        throw Test::TestFailure(__FILE__, "==", #value, "false");
#define REC_NULL(value)   \
    if (value != nullptr) \
        throw Test::TestFailure(__FILE__, "==", #value, "nullptr");
#define REC_NOT_NULL(value) \
    if (value == nullptr)   \
        throw Test::TestFailure(__FILE__, "!=", #value, "nullptr");
#define REC_LEQL(value, target) \
    if (value > target)         \
        throw Test::TestFailure(__FILE__, "<=", #value, #target);
#define REC_GEQL(value, target) \
    if (value < target)         \
        throw Test::TestFailure(__FILE__, ">=", #value, #target);
#define REC_LSS(value, target) \
    if (value >= target)       \
        throw Test::TestFailure(__FILE__, "<", #value, #target);
#define REC_GTR(value, target) \
    if (value <= target)       \
        throw Test::TestFailure(__FILE__, ">", #value, #target);

/**
 * Macro to define a test case.
 * @param test_name Name of the test case.
 * @param test_description Description of the test case.
 */
#define TEST(test_name, test_description) __TEST_IMPL1(UNIQUE_IDENTIFIER(_TEST_), test_name, test_description)
#define __TEST_IMPL1(prefix, test_name, test_description) __TEST_IMPL2(CONCATENATE(prefix, _function), CONCATENATE(prefix, _var), test_name, test_description)
#define __TEST_IMPL2(function_name, var_name, test_name, test_description)                   \
    static void function_name();                                                             \
    static void CONCATENATE(calling_, function_name)()                                       \
    {                                                                                        \
        std::print("Running: {} - {}\n", test_name, test_description);                       \
        try                                                                                  \
        {                                                                                    \
            function_name();                                                                 \
        }                                                                                    \
        catch (const Test::TestFailure &e)                                                   \
        {                                                                                    \
            std::cerr << e.what() << std::endl;                                              \
            throw std::runtime_error("Test case failed.");                                   \
            return;                                                                          \
        }                                                                                    \
    }                                                                                        \
    static int var_name __attribute((unused)) = (CONCATENATE(calling_, function_name)(), 0); \
    static void function_name()
#else // TESTMODE
#define REC_EQL(value, target)
#define REC_NEQ(value, target)
#define REC_TRUE(value)
#define REC_FALSE(value)
#define REC_NULL(value)
#define REC_NOT_NULL(value)
#define REC_LEQL(value, target)
#define REC_GEQL(value, target)
#define REC_LSS(value, target)
#define REC_GTR(value, target)
#define TEST(test_name, test_description) static void inline UNIQUE_IDENTIFIER(_unused_)()

#endif // TESTMODE

namespace Test
{
    class TestFailure : public std::runtime_error
    {
    public:
        TestFailure(const std::string &origin, const std::string &comparator, const std::string &expression, const std::string &value) : std::runtime_error(origin + "| Test failed: " + expression + " must be " + comparator + " to " + value) {}
    };
}

#endif // TEST_H