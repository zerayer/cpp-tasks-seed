#include <algorithm>
#include <vector>

#include "gtest/gtest.h"
#include "sorting.h"

TEST(SortingSuite, BubbleSortEmpty)
{
    std::vector<int> data;

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(data.empty());
}

TEST(SortingSuite, HeapSortEmpty)
{
    std::vector<int> data;

    heap_sort(data.begin(), data.end());

    EXPECT_TRUE(data.empty());
}

TEST(SortingSuite, BubbleSortOneElement)
{
    std::vector<int> data = {42};

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, HeapSortOneElement)
{
    std::vector<int> data = {42};

    heap_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, BubbleSortSimple)
{
    std::vector<int> data = {5, 1, 4, 2, 8};

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, HeapSortSimple)
{
    std::vector<int> data = {5, 1, 4, 2, 8};

    heap_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, BubbleSortWithRepeats)
{
    std::vector<int> data = {3, 1, 2, 3, 1, 2};

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, HeapSortWithRepeats)
{
    std::vector<int> data = {3, 1, 2, 3, 1, 2};

    heap_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, BubbleSortAlreadySorted)
{
    std::vector<int> data = {1, 2, 3, 4, 5};

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, HeapSortAlreadySorted)
{
    std::vector<int> data = {1, 2, 3, 4, 5};

    heap_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, BubbleSortReverseOrder)
{
    std::vector<int> data = {5, 4, 3, 2, 1};

    bubble_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}

TEST(SortingSuite, HeapSortReverseOrder)
{
    std::vector<int> data = {5, 4, 3, 2, 1};

    heap_sort(data.begin(), data.end());

    EXPECT_TRUE(std::is_sorted(data.begin(), data.end()));
}
