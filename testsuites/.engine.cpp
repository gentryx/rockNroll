/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "./testsuites/engine.h"

static MersenneTestSuite suite_MersenneTestSuite;

static CxxTest::List Tests_MersenneTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MersenneTestSuite( "./testsuites/engine.h", 82, "MersenneTestSuite", suite_MersenneTestSuite, Tests_MersenneTestSuite );

static class TestDescription_MersenneTestSuite_testGetDiceVal : public CxxTest::RealTestDescription {
public:
 TestDescription_MersenneTestSuite_testGetDiceVal() : CxxTest::RealTestDescription( Tests_MersenneTestSuite, suiteDescription_MersenneTestSuite, 103, "testGetDiceVal" ) {}
 void runTest() { suite_MersenneTestSuite.testGetDiceVal(); }
} testDescription_MersenneTestSuite_testGetDiceVal;

static class TestDescription_MersenneTestSuite_testGenrandUInt32 : public CxxTest::RealTestDescription {
public:
 TestDescription_MersenneTestSuite_testGenrandUInt32() : CxxTest::RealTestDescription( Tests_MersenneTestSuite, suiteDescription_MersenneTestSuite, 125, "testGenrandUInt32" ) {}
 void runTest() { suite_MersenneTestSuite.testGenrandUInt32(); }
} testDescription_MersenneTestSuite_testGenrandUInt32;

static class TestDescription_MersenneTestSuite_testInitGenrand : public CxxTest::RealTestDescription {
public:
 TestDescription_MersenneTestSuite_testInitGenrand() : CxxTest::RealTestDescription( Tests_MersenneTestSuite, suiteDescription_MersenneTestSuite, 144, "testInitGenrand" ) {}
 void runTest() { suite_MersenneTestSuite.testInitGenrand(); }
} testDescription_MersenneTestSuite_testInitGenrand;

static MrBlackTestSuite suite_MrBlackTestSuite;

static CxxTest::List Tests_MrBlackTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MrBlackTestSuite( "./testsuites/engine.h", 179, "MrBlackTestSuite", suite_MrBlackTestSuite, Tests_MrBlackTestSuite );

static class TestDescription_MrBlackTestSuite_testRemMoves : public CxxTest::RealTestDescription {
public:
 TestDescription_MrBlackTestSuite_testRemMoves() : CxxTest::RealTestDescription( Tests_MrBlackTestSuite, suiteDescription_MrBlackTestSuite, 198, "testRemMoves" ) {}
 void runTest() { suite_MrBlackTestSuite.testRemMoves(); }
} testDescription_MrBlackTestSuite_testRemMoves;

static BoardTestSuite suite_BoardTestSuite;

static CxxTest::List Tests_BoardTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BoardTestSuite( "./testsuites/engine.h", 300, "BoardTestSuite", suite_BoardTestSuite, Tests_BoardTestSuite );

static class TestDescription_BoardTestSuite_testHashWords : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testHashWords() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 377, "testHashWords" ) {}
 void runTest() { suite_BoardTestSuite.testHashWords(); }
} testDescription_BoardTestSuite_testHashWords;

static class TestDescription_BoardTestSuite_testPopulation : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testPopulation() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 405, "testPopulation" ) {}
 void runTest() { suite_BoardTestSuite.testPopulation(); }
} testDescription_BoardTestSuite_testPopulation;

static class TestDescription_BoardTestSuite_testMove1 : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testMove1() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 444, "testMove1" ) {}
 void runTest() { suite_BoardTestSuite.testMove1(); }
} testDescription_BoardTestSuite_testMove1;

static class TestDescription_BoardTestSuite_testMove2 : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testMove2() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 459, "testMove2" ) {}
 void runTest() { suite_BoardTestSuite.testMove2(); }
} testDescription_BoardTestSuite_testMove2;

static class TestDescription_BoardTestSuite_testInitPos1 : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testInitPos1() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 479, "testInitPos1" ) {}
 void runTest() { suite_BoardTestSuite.testInitPos1(); }
} testDescription_BoardTestSuite_testInitPos1;

static AIPlayerTestSuite suite_AIPlayerTestSuite;

static CxxTest::List Tests_AIPlayerTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AIPlayerTestSuite( "./testsuites/engine.h", 559, "AIPlayerTestSuite", suite_AIPlayerTestSuite, Tests_AIPlayerTestSuite );

static class TestDescription_AIPlayerTestSuite_testBoard2ID : public CxxTest::RealTestDescription {
public:
 TestDescription_AIPlayerTestSuite_testBoard2ID() : CxxTest::RealTestDescription( Tests_AIPlayerTestSuite, suiteDescription_AIPlayerTestSuite, 601, "testBoard2ID" ) {}
 void runTest() { suite_AIPlayerTestSuite.testBoard2ID(); }
} testDescription_AIPlayerTestSuite_testBoard2ID;

static class TestDescription_AIPlayerTestSuite_testMockupAIPlayer : public CxxTest::RealTestDescription {
public:
 TestDescription_AIPlayerTestSuite_testMockupAIPlayer() : CxxTest::RealTestDescription( Tests_AIPlayerTestSuite, suiteDescription_AIPlayerTestSuite, 631, "testMockupAIPlayer" ) {}
 void runTest() { suite_AIPlayerTestSuite.testMockupAIPlayer(); }
} testDescription_AIPlayerTestSuite_testMockupAIPlayer;

static FarmerBoyTestSuite suite_FarmerBoyTestSuite;

static CxxTest::List Tests_FarmerBoyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FarmerBoyTestSuite( "./testsuites/engine.h", 676, "FarmerBoyTestSuite", suite_FarmerBoyTestSuite, Tests_FarmerBoyTestSuite );

static class TestDescription_FarmerBoyTestSuite_testRating : public CxxTest::RealTestDescription {
public:
 TestDescription_FarmerBoyTestSuite_testRating() : CxxTest::RealTestDescription( Tests_FarmerBoyTestSuite, suiteDescription_FarmerBoyTestSuite, 689, "testRating" ) {}
 void runTest() { suite_FarmerBoyTestSuite.testRating(); }
} testDescription_FarmerBoyTestSuite_testRating;

static EmptyTestSuite suite_EmptyTestSuite;

static CxxTest::List Tests_EmptyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EmptyTestSuite( "./testsuites/engine.h", 720, "EmptyTestSuite", suite_EmptyTestSuite, Tests_EmptyTestSuite );

static class TestDescription_EmptyTestSuite_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_EmptyTestSuite_testAddition() : CxxTest::RealTestDescription( Tests_EmptyTestSuite, suiteDescription_EmptyTestSuite, 728, "testAddition" ) {}
 void runTest() { suite_EmptyTestSuite.testAddition(); }
} testDescription_EmptyTestSuite_testAddition;

#include <cxxtest/Root.cpp>
