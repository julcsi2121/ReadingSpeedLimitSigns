#include "filterSignLimit.h"


FilterSignLimit::FilterSignLimit(int size)
{
    if (size <= 0) {
        throw std::runtime_error("Size must be greater than 0!");
    }
    
    _counter = 0;
    _size = size;
    _results.resize(_size);
    
    for (int i = 0; i < size; ++i) {
        _results.at(i) = 0;
    }
}

int FilterSignLimit::addRecord(int number)
{   
    if (number > 0 && number <= 130 && number % 5 == 0) {
        _results.at(_counter % _size) = number;
        _counter++;
    }

    return processResults();
}

int FilterSignLimit::processResults()
{
    int actualValue = _results.at(0);

    for (int i = 0; i < _results.size(); ++i) {
        if (actualValue != _results.at(i)) {
            return 0;
        }
    }

    return actualValue;
}
