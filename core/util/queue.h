#pragma once


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

    T& peek_at(int index)
    {
        return data[(head + index) % SIZE];
    }

    T& front()
    {
        return data[head];
    }

    void pop()
    {
        if (count == 0)
        {
            return;
        }

        head = (head + 1) % SIZE;
        count--;
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
