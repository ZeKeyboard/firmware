#include "../queue.h"
#include <catch_amalgamated.hpp>

TEST_CASE("Test queue", "[FixedSizeQueue]")
{
    core::util::FixedSizeQueue<int, 10> queue;

    SECTION("Test push and pop")
    {
        CHECK(queue.empty());
        CHECK(!queue.full());

        queue.push(1);
        queue.push(2);
        queue.push(4);

        CHECK(queue.size() == 3);
        CHECK(!queue.empty());
        CHECK(!queue.full());

        auto el1 = queue.pop();
        auto el2 = queue.pop();
        auto el3 = queue.pop();

        REQUIRE(el1 == 1);
        REQUIRE(el2 == 2);
        REQUIRE(el3 == 4);
    }
}
