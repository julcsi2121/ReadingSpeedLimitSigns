#include "insertionSort.h"

bool isSwapNeeded(int x, int y, bool descending)
{
    if (descending) {
        return x < y;
    } else {
        return x > y;
    }
}

std::vector<int> insertionSort(std::vector<int> input, bool descending)
{
    int j;
    int marker;
    for (int i = 1; i < input.size(); i++) {
        marker = input[i];
        j = i - 1;
        while (j >= 0 && isSwapNeeded(input[j], marker, descending)) {
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = marker;
    }
    return input;
}
