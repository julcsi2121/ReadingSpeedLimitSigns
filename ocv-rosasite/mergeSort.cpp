#include "mergeSort.h"

bool compare(int left, int right, bool desc) {
    if (desc == true) {
        return right < left;
    } else {
        return left < right;
    }
}

std::vector<int> merge(const std::vector<int> &left, const std::vector<int> &right, bool desc)
{
    std::vector<int> result;    
    int indexL = 0;
    int indexR = 0;

    while (indexL < left.size() && indexR < right.size()) {
        if (compare(left.at(indexL), right.at(indexR), desc)) {
            result.push_back(left.at(indexL));
            indexL++;
        } else {
            result.push_back(right.at(indexR));
            indexR++;
        }
    }
    
    for (indexL; indexL < left.size(); ++indexL) {
        result.push_back(left.at(indexL));
    }

    for (indexR; indexR < right.size(); ++indexR) {
        result.push_back(right.at(indexR));
    }
    return result;
}

std::vector<int> mergeSort(std::vector<int> &input, bool desc)
{
    if (input.empty()) {
        return input;
    }

    std::vector<int> result;

    if (input.size() == 1) {
        return input;
    } else {
        int middle = input.size() / 2;
        std::vector<int> left(input.begin(), input.begin() + middle);
        std::vector<int> right(input.begin() + middle, input.end());

        std::vector<int> newLeft = mergeSort(left, desc);
        std::vector<int> newRight = mergeSort(right, desc);

        result = merge(newLeft, newRight, desc);
    }

    return result;
}
