#include "../queue.h"
#include <catch_amalgamated.hpp>


struct TestStruct
{
    int a;
    int b;
    int c;
};


TEST_CASE("Test queue push and pop", "[FixedSizeQueue]")
{

    SECTION("Test int queue")
    {
        core::util::FixedSizeQueue<int, 10> queue;

        CHECK(queue.empty());
        CHECK(!queue.full());

        queue.push(1);
        queue.push(2);
        queue.push(4);

        CHECK(queue.size() == 3);
        CHECK(!queue.empty());
        CHECK(!queue.full());

        auto el1 = queue.front();
        REQUIRE(el1 == 1);
        queue.pop();
        auto el2 = queue.front();
        REQUIRE(el2 == 2);
        queue.pop();
        auto el3 = queue.front();
        REQUIRE(el3 == 4);
        queue.pop();

    }

    SECTION("Test struct queue")
    {
        core::util::FixedSizeQueue<TestStruct, 10> queue;

        CHECK(queue.empty());
        CHECK(!queue.full());

        queue.push({1, 2, 3});
        queue.push({4, 5, 6});
        queue.push({7, 8, 9});

        CHECK(queue.size() == 3);
        CHECK(!queue.empty());
        CHECK(!queue.full());

        auto el1 = queue.front();
        REQUIRE(el1.a == 1);
        REQUIRE(el1.b == 2);
        REQUIRE(el1.c == 3);
        queue.pop();

        auto el2 = queue.front();
        REQUIRE(el2.a == 4);
        REQUIRE(el2.b == 5);
        REQUIRE(el2.c == 6);
        queue.pop();

        auto el3 = queue.front();
        REQUIRE(el3.a == 7);
        REQUIRE(el3.b == 8);
        REQUIRE(el3.c == 9);
        queue.pop();
    }
}

TEST_CASE("Test queue bounds")
{
    SECTION("Test int queue")
    {
        core::util::FixedSizeQueue<int, 10> queue;

        for (int i = 0; i < 10; ++i)
        {
            queue.push(i);
        }

        CHECK(queue.size() == 10);
        CHECK(queue.full());
        CHECK(!queue.empty());

        queue.push(111);
        CHECK(queue.size() == 10);

        for (int i = 0; i < 10; ++i)
        {
            auto el = queue.front();
            REQUIRE(el == i);
            queue.pop();
        }

        CHECK(queue.empty());
        CHECK(!queue.full());
    }

    SECTION("Test struct queue")
    {
        core::util::FixedSizeQueue<TestStruct, 10> queue;

        for (int i = 0; i < 10; ++i)
        {
            queue.push({i, i, i});
        }

        CHECK(queue.size() == 10);
        CHECK(queue.full());
        CHECK(!queue.empty());

        for (int i = 0; i < 10; ++i)
        {
            auto el = queue.front();
            REQUIRE(el.a == i);
            REQUIRE(el.b == i);
            REQUIRE(el.c == i);
            queue.pop();
        }

        CHECK(queue.empty());
        CHECK(!queue.full());
    }
}
