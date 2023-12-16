#pragma once

namespace core::util
{

/**
 * Checks if the given array contains the given item.
 */
template <typename T>
bool array_contains(const T array[], int size, const T& item)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == item)
        {
            return true;
        }
    }

    return false;
}


/**
 * Copies the given array to the destination array.
 */
template <typename T>
void array_copy(const T source[], T destination[], int size)
{
    for (int i = 0; i < size; i++)
    {
        destination[i] = source[i];
    }
}


/**
 * Computes the intersection of the given arrays.
 */
template <typename T>
void array_intersection(const T a[], int a_size, const T b[], int b_size, T result[], int& result_size)
{
    result_size = 0;
    for (int i = 0; i < a_size; i++)
    {
        if (array_contains(b, b_size, a[i]))
        {
            result[result_size++] = a[i];
        }
    }
}

template <typename T>
void array_union(const T a[], int a_size, const T b[], int b_size, T result[], int& result_size)
{
    result_size = 0;
    for (int i = 0; i < a_size; i++)
    {
        result[result_size++] = a[i];
    }

    for (int i = 0; i < b_size; i++)
    {
        if (!array_contains(a, a_size, b[i]))
        {
            result[result_size++] = b[i];
        }
    }
}

/**
 * Subtracts the given arrays, that is, computes the array containing all
 * elements of a that are not in b.
 */
template <typename T>
void array_subtract(const T a[], int a_size, const T b[], int b_size, T result[], int& result_size)
{
    result_size = 0;
    for (int i = 0; i < a_size; i++)
    {
        if (!array_contains(b, b_size, a[i]))
        {
            result[result_size++] = a[i];
        }
    }

}

}
