#include <gtest/gtest.h>
#include "quicksort.hpp"

TEST(QuicksortTest, TestWithEmptyVectorWithoutDescendingFlag)
{
    std::vector<int> emptyVector;
    std::vector<int> sortedVector = quicksort(emptyVector);
    
    EXPECT_EQ(emptyVector, sortedVector);
}

TEST(QuicksortTest, TestWithEmptyVectorWithDescendingFlag)
{
    std::vector<int> emptyVector;
    std::vector<int> sortedVector = quicksort(emptyVector, true);
    
    EXPECT_EQ(emptyVector, sortedVector);
}

TEST(QuicksortTest, TestWithAllreadySortedVectorInAscendingOrderWithNElementsWithoutDescendingFlag)
{
    std::vector<int> ascendingSortedVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> sortedVector = quicksort(ascendingSortedVector);
    
    EXPECT_EQ(ascendingSortedVector, sortedVector);
}

TEST(QuicksortTest, TestWithAllreadySortedVectorInAscendingOrderWithNElementsWithDescendingFlag)
{
    std::vector<int> ascendingSortedVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> manuallySortedVector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> sortedVector = quicksort(ascendingSortedVector, true);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}

TEST(QuicksortTest, TestWithAllreadySortedVectorInDescendingOrderWithoutDescendingFlag)
{
    std::vector<int> descendingSortedVector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> manuallySortedVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> sortedVector = quicksort(descendingSortedVector);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}

TEST(QuicksortTest, TestWithAllreadySortedVectorInDescendingOrderWithDescendingFlag)
{
    std::vector<int> descendingSortedVector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> sortedVector = quicksort(descendingSortedVector, true);
    
    EXPECT_EQ(descendingSortedVector, sortedVector);
}

TEST(QuicksortTest, TestWithVectorWith10RandomElementsWithoutDescendingFlag)
{
    std::vector<int> randomVector = {89, 4, 18, 6, 7, 10, 99, -5, 1, 0};
    std::vector<int> manuallySortedVector = {-5, 0, 1, 4, 6, 7, 10, 18, 89, 99};
    std::vector<int> sortedVector = quicksort(randomVector);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}

TEST(QuicksortTest, TestWithVectorWith10RandomElementsWithDescendingFlag)
{
    std::vector<int> randomVector = {89, 4, 18, 6, 7, 10, 99, -5, 1, 0};
    std::vector<int> manuallySortedVector = {99, 89, 18, 10, 7, 6, 4, 1, 0, -5};
    std::vector<int> sortedVector = quicksort(randomVector, true);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}
