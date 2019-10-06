#include "heapsort.hpp"

void heapifyMin(std::vector<int> *input, int root)
{
    int lowest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    if (left < input->size() && input->at(left) < input->at(lowest))
        lowest = left;
    
    if (right < input->size() && input->at(right) < input->at(lowest))
        lowest = right;
    
    if (lowest != root) {
        std::swap(input->at(root), input->at(lowest));
        heapifyMin(input, lowest);
    }
}

void heapifyMax(std::vector<int> *input, int root)
{
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    if (left < input->size() && input->at(left) > input->at(largest))
        largest = left;
    
    if (right < input->size() && input->at(right) > input->at(largest))
        largest = right;
    
    if (largest != root) {
        std::swap(input->at(root), input->at(largest));
        heapifyMax(input, largest);
    }
}

std::vector<int> heapsort(std::vector<int> input, bool desc)
{
    std::vector<int> sorted;
    
    if (desc) {
        for (int i = input.size() / 2.0 - 1; i >= 0; i--)
            heapifyMax(&input, i);
    } else {
        for (int i = input.size() / 2.0 - 1; i >= 0; i--)
            heapifyMin(&input, i);
    }
    
    for (int i = input.size() - 1.0; i >= 0; i--) {
        sorted.push_back(input.at(0));
        std::swap(input.at(0), input.at(i));
        input.pop_back();
        
        if (desc) {
            heapifyMax(&input, 0);
        } else
            heapifyMin(&input, 0);
    }
    
    return sorted;
}
