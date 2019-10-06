#include "shellSort.h"

static bool isSwapNeeded(int a, int b, bool descending)
{
    if (descending) {
        return a < b;
    } else {
        return a > b;
    }
}

std::vector<int> shellSort(std::vector<int> input, bool descending)
{
    for (int gap = input.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < input.size(); i++) {
            int temp = input[i];
            int j;
            for (j = i; j >= gap && isSwapNeeded(input[j - gap], temp, descending); j -= gap) {
                input[j] = input[j - gap];
            }
            input[j] = temp;
        }
    }
    return input;
}