#include "quicksort.hpp"

void quicksort(std::vector<int>* input, int left, int right, bool desc)
{
    int i = left, j = right;
    int mid = (left + right) / 2;
    
    if (desc) {
        if (input->at(left) < input->at(right))
            std::swap(input->at(left), input->at(right));
        if (input->at(mid) > input->at(left))
            std::swap(input->at(mid), input->at(left));
        if (input->at(mid) < input->at(right))
            std::swap(input->at(mid), input->at(right));
    } else {
        if (input->at(left) > input->at(right))
            std::swap(input->at(left), input->at(right));
        if (input->at(mid) < input->at(left))
            std::swap(input->at(mid), input->at(left));
        if (input->at(mid) > input->at(right))
            std::swap(input->at(mid), input->at(right));
    }
    
    int pivot = input->at(mid);
    
    while (i <= j) {
        
        if (desc) {
            while (input->at(i) > pivot)
                i++;
            while (input->at(j) < pivot)
                j--;
        } else {
            while (input->at(i) < pivot)
                i++;
            while (input->at(j) > pivot)
                j--;
        }
        
        if (i <= j) {
            std::swap(input->at(i), input->at(j));
            i++;
            j--;
        }
    }
    
    if (j > left)
        quicksort(input, left, j, desc);
    if (i < right)
        quicksort(input, i, right, desc);
}

std::vector<int> quicksort(std::vector<int> input, bool desc)
{
    std::vector<int> sorted = input;
    if (!input.empty())
        quicksort(&sorted, 0, sorted.size() - 1.0, desc);
    return sorted;
}
