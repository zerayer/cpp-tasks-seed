#ifndef SORTING_H
#define SORTING_H

#include "collvalue.h"

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (Iterator i = begin; i != end; ++i)
    {
        bool swapped = false;

        for (Iterator j = begin; j + 1 != end - (i - begin); ++j)
        {
            if (*(j + 1) < *j)
            {
                swap(*j, *(j + 1));
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

template <typename Iterator>
void sift_down(Iterator begin, int size, int index)
{
    while (true)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && *(begin + largest) < *(begin + left))
        {
            largest = left;
        }

        if (right < size && *(begin + largest) < *(begin + right))
        {
            largest = right;
        }

        if (largest == index)
        {
            break;
        }

        swap(*(begin + index), *(begin + largest));
        index = largest;
    }
}

template <typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
    int size = end - begin;

    for (int i = size / 2 - 1; i >= 0; --i)
    {
        sift_down(begin, size, i);
    }

    for (int i = size - 1; i > 0; --i)
    {
        swap(*begin, *(begin + i));
        sift_down(begin, i, 0);
    }
}

#endif // SORTING_H
