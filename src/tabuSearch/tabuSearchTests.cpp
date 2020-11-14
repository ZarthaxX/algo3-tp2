
#include <vector>
#include "../tests/littletest.hpp"
#include "tabuSearch.h"
#include "../types.h"

// Tests Ejercicio 1

LT_BEGIN_SUITE(TabuSearchStructuresTests)

Color aColor = 1;
Color aDifferentColor = 2;
Color aThirdColor = 3;
Coloring colors = Coloring(5,aColor);
TabuSearch::Solution solution = TabuSearch::Solution(colors);
TabuSearch::Change firstNodeADifferentColor = TabuSearch::Change(0,aColor,aDifferentColor);
TabuSearch::Swap swapFirstAndSecond = TabuSearch::Swap(0,1);

TabuSearch::Change anElement = firstNodeADifferentColor; 
TabuSearch::Swap anotherElement = swapFirstAndSecond; 
TabuSearch::Change aThirdElement = TabuSearch::Change(0,aDifferentColor,aThirdColor);

void set_up()
{
    solution = TabuSearch::Solution(colors);
}

void tear_down()
{
}

LT_END_SUITE(TabuSearchStructuresTests)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, SolutionDoesNotModifyInitialColoring)
    for(int i = 0;i < colors.size();i++){
        LT_CHECK_EQ(colors[i],solution.colorOfNode(i));
    }
LT_END_AUTO_TEST(SolutionDoesNotModifyInitialColoring)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, ChangeModifiesColorsOfSolutionsForward)
    firstNodeADifferentColor.applyToSolution(solution);
    LT_CHECK_EQ(aDifferentColor,solution.colorOfNode(0));
    for(int i = 1;i < colors.size();i++){
        LT_CHECK_EQ(colors[i],solution.colorOfNode(i));
    }
LT_END_AUTO_TEST(ChangeModifiesColorsOfSolutionsForward)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, ChangeModifiesColorsOfSolutionsBackwards)
    firstNodeADifferentColor.applyToSolution(solution);
    firstNodeADifferentColor.reverseOnSolution(solution);
    for(int i = 0;i < colors.size();i++){
        LT_CHECK_EQ(colors[i],solution.colorOfNode(i));
    }
LT_END_AUTO_TEST(ChangeModifiesColorsOfSolutionsBackwards)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, SwapModifiesColorsOfSolutionsForward)
    firstNodeADifferentColor.applyToSolution(solution);
    swapFirstAndSecond.applyToSolution(solution);
    LT_CHECK_EQ(aColor,solution.colorOfNode(0));
    LT_CHECK_EQ(aDifferentColor,solution.colorOfNode(1));
    for(int i = 2;i < colors.size();i++){
        LT_CHECK_EQ(colors[i],solution.colorOfNode(i));
    }
LT_END_AUTO_TEST(SwapModifiesColorsOfSolutionsForward)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, SwapModifiesColorsOfSolutionsBackwards)
    firstNodeADifferentColor.applyToSolution(solution);
    swapFirstAndSecond.applyToSolution(solution);
    swapFirstAndSecond.reverseOnSolution(solution);
    LT_CHECK_EQ(aColor,solution.colorOfNode(1));
    LT_CHECK_EQ(aDifferentColor,solution.colorOfNode(0));
    for(int i = 2;i < colors.size();i++){
        LT_CHECK_EQ(colors[i],solution.colorOfNode(i));
    }
LT_END_AUTO_TEST(SwapModifiesColorsOfSolutionsBackwards)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, IsomorphicSolutionsAreEqual)
    firstNodeADifferentColor.applyToSolution(solution);
    Coloring aDifferentColoring = Coloring(5,aDifferentColor);
    TabuSearch::Change firstDifferentToThirdColor = TabuSearch::Change(0,aDifferentColor,aThirdColor);
    TabuSearch::Solution aDifferentSolution = TabuSearch::Solution(aDifferentColoring);
    firstDifferentToThirdColor.applyToSolution(aDifferentSolution);
    LT_CHECK_EQ(solution,aDifferentSolution);
LT_END_AUTO_TEST(IsomorphicSolutionsAreEqual)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, SwapsOfNodesInDifferentOrderAreEqual)
    TabuSearch::Swap swapSecondAndFirst = TabuSearch::Swap(1,0);
    LT_CHECK_EQ(swapFirstAndSecond,swapSecondAndFirst);
LT_END_AUTO_TEST(SwapsOfNodesInDifferentOrderAreEqual)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, MemoryContainsStoredElements)
    auto memory = TabuSearch::Memory<TabuSearch::Modificator>(1);
    memory.add(anElement);
    cout << typeid(anElement).name() << endl;
    LT_CHECK(memory.contains(anElement))
    // memory.print_type_of_position(0);
    LT_CHECK(not memory.contains(anotherElement))
LT_END_AUTO_TEST(MemoryContainsStoredElements)

LT_BEGIN_AUTO_TEST(TabuSearchStructuresTests, MemoryBehavesFIFO)
    auto memory = TabuSearch::Memory<TabuSearch::Modificator>(2);
    memory.add(anElement);
    memory.add(anotherElement);
    LT_CHECK(memory.contains(anElement));
    LT_CHECK(memory.contains(anotherElement));
    LT_CHECK(not memory.contains(aThirdElement));
    memory.add(aThirdElement);
    LT_CHECK(not memory.contains(anElement));
    LT_CHECK(memory.contains(anotherElement));
    LT_CHECK(memory.contains(aThirdElement));
    memory.add(anElement);
    LT_CHECK(memory.contains(anElement));
    LT_CHECK(not memory.contains(anotherElement));
    LT_CHECK(memory.contains(aThirdElement));
LT_END_AUTO_TEST(MemoryBehavesFIFO)


// Ejecutar tests
LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()