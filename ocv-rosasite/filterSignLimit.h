#pragma once
#include <iostream>
#include <vector>


class FilterSignLimit
{
public:
    FilterSignLimit(int size);
    int addRecord(int number);
private:
    int processResults();
    std::vector<int> _results;
    int _size;
    int _counter;
};

