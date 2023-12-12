#pragma once
#include <iostream>


namespace core::util
{

/**
 * A fixed size queue that is implemented as a circular buffer.
 */
template <typename T, int SIZE>
class FixedSizeQueue
{
public:

    void push(const T& item)
    {
        if (count == SIZE)
        {
            return;
        }

        data[tail] = item;
        tail = (tail + 1) % SIZE;
        count++;
    }

    T pop()
    {
        if (count == 0)
        {
            return T();
        }

        T item = data[head];
        head = (head + 1) % SIZE;
        count--;
        return item;
    }

    int size() const
    {
        return count;
    }

    bool empty() const
    {
        return count == 0;
    }

    bool full() const
    {
        return count == SIZE;
    }
private:
    T data[SIZE];
    int head = 0;
    int tail = 0;
    int count = 0;
};

}
