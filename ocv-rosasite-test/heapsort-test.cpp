#include <gtest/gtest.h>
#include "heapsort.hpp"

TEST(HeapsortTest, TestWithEmptyVectorWithoutDescendingFlag)
{
    std::vector<int> emptyVector;
    std::vector<int> sortedVector = heapsort(emptyVector);
    
    EXPECT_EQ(emptyVector, sortedVector);
}

TEST(HeapsortTest, TestWithEmptyVectorWithDescendingFlag)
{
    std::vector<int> emptyVector;
    std::vector<int> sortedVector = heapsort(emptyVector, true);
    
    EXPECT_EQ(emptyVector, sortedVector);
}

TEST(HeapsortTest, TestWithAllreadySortedVectorInAscendingOrderWithNElementsWithoutDescendingFlag)
{
    std::vector<int> ascendingSortedVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> sortedVector = heapsort(ascendingSortedVector);
    
    EXPECT_EQ(ascendingSortedVector, sortedVector);
}

TEST(HeapsortTest, TestWithAllreadySortedVectorInAscendingOrderWithNElementsWithDescendingFlag)
{
    std::vector<int> ascendingSortedVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> manuallySortedVector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> sortedVector = heapsort(ascendingSortedVector, true);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}

TEST(HeapsortTest, TestWithAllreadySortedVectorInDescendingOrderWithoutDescendingFlag)
{
    std::vector<int> descendingSortedVector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> manuallySortedVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> sortedVector = heapsort(descendingSortedVector);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}

TEST(HeapsortTest, TestWithAllreadySortedVectorInDescendingOrderWithDescendingFlag)
{
    std::vector<int> descendingSortedVector = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> sortedVector = heapsort(descendingSortedVector, true);
    
    EXPECT_EQ(descendingSortedVector, sortedVector);
}

TEST(HeapsortTest, TestWithVectorWith10RandomElementsWithoutDescendingFlag)
{
    std::vector<int> randomVector = {89, 4, 18, 6, 7, 10, 99, -5, 1, 0};
    std::vector<int> manuallySortedVector = {-5, 0, 1, 4, 6, 7, 10, 18, 89, 99};
    std::vector<int> sortedVector = heapsort(randomVector);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}

TEST(HeapsortTest, TestWithVectorWith10RandomElementsWithDescendingFlag)
{
    std::vector<int> randomVector = {89, 4, 18, 6, 7, 10, 99, -5, 1, 0};
    std::vector<int> manuallySortedVector = {99, 89, 18, 10, 7, 6, 4, 1, 0, -5};
    std::vector<int> sortedVector = heapsort(randomVector, true);
    
    EXPECT_EQ(manuallySortedVector, sortedVector);
}
