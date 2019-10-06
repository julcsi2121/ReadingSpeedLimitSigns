#include "selectionSort.h"

std::vector<int> selectionSort(std::vector<int> input, bool descending)
{
    std::vector<int> toSort = input;
    std::vector<int>::iterator it;

    for (int i = 0; i < toSort.size(); ++i) {
        if (descending == true) {
            it = std::max_element(toSort.begin() + i, toSort.end());
        }
        else {
            it = std::min_element(toSort.begin() + i, toSort.end());
        }
        std::iter_swap(toSort.begin() + i, it);
    }

    return toSort;
}
