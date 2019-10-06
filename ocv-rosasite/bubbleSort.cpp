#include "bubbleSort.h"
#include <vector>

void swap(int *firstElement, int *secondElement)
{
    int temp = *firstElement;
    *firstElement = *secondElement;
    *secondElement = temp;
}

std::vector<int> bubbleSort(std::vector<int> input, bool descending)
{
    bool swapped;

    if (!descending) {
        for (int i = 0; i < (int)input.size() - 1; ++i) {
            swapped = false;

            for (int j = 0; j < input.size() - i - 1; ++j) {
                if (input[j] > input[j + 1]) {
                    swap(&input[j], &input[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
        return input;
    } else {
        for (int i = 0; i < (int)input.size() - 1; ++i) {
            swapped = false;

            for (int j = 0; j < input.size() - i - 1; ++j) {
                if (input[j] < input[j + 1]) {
                    swap(&input[j + 1], &input[j]);
                    swapped = true;
                }
            }
            if (!swapped) {
                break;
            }
        }
        return input;
    }
}
