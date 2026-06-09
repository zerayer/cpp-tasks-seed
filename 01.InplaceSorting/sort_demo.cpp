#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#include "collvalue.h"
#include "sorting.h"

using CollInt = CollectingValue<int>;

std::vector<CollInt> generate_data(size_t n)
{
    std::vector<CollInt> data(n);
    std::iota(data.begin(), data.end(), CollInt(0));
    return data;
}

void shuffle_data(std::vector<CollInt>& data)
{
    std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()});
}

void print_stats(size_t n, const char* name)
{
    std::cout << n << "\t" << name << "\t\t" << CollInt::comps << "\t\t"
              << CollInt::swaps << "\t\t" << CollInt::moves << "\n";
}

int main()
{
    std::vector<size_t> sizes = {100, 500, 1000, 2000};

    std::cout << "N\tAlgo\t\tComps\t\tSwaps\t\tMoves\n";
    std::cout << "----------------------------------------------------------------\n";

    for (size_t n : sizes)
    {
        auto number_data = generate_data(n);

        shuffle_data(number_data);
        CollInt::reset_stats();
        std::sort(number_data.begin(), number_data.end());
        print_stats(n, "std::sort");

        shuffle_data(number_data);
        CollInt::reset_stats();
        bubble_sort(number_data.begin(), number_data.end());
        print_stats(n, "Bubble");

        shuffle_data(number_data);
        CollInt::reset_stats();
        heap_sort(number_data.begin(), number_data.end());
        print_stats(n, "Heap");

        std::cout << "--------------------------------------------------------------\n";
    }

    return 0;
}
