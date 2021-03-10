#ifndef TESTS_DETACHED_H
#define TESTS_DETACHED_H

#include <gtest/gtest.h>
#include <exception>

namespace tests
{
/** \brief Class detects thrown exception in co_spawned function
 * Should be used only in tests that use gtest framework
 **/
class Detached
{
public:
    constexpr Detached() = default;
    auto operator()(std::exception_ptr error)
    {
        auto exception_thrown = false;
        try
        {
            if (error)
            {
                exception_thrown = true;
                std::rethrow_exception(error);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "tests::Detached catched: " << e.what() << std::endl;
        }
        EXPECT_FALSE(exception_thrown);
    }
};

}  // namespace tests

#endif